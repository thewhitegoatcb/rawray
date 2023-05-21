local _lfs = lfs
local sg = {}
local overrides_path = rr.root_dir .."overrides/"

local lua_loader
local c_loader
local croot_loader

local lua_dofile
local lua_loadfile
local lua_load
local lua_require
local sg_loader

--copied this to remove dependencies
local function table_shallow_copy(t, skip_metatable)
	local copy = {}

	assert(skip_metatable or getmetatable(t) == nil, "Metatables will be sliced off")

	for key, value in pairs(t) do
		copy[key] = value
	end

	return copy
end

local function isfileexists(path)
	local attr = _lfs.attributes(path)
	return attr and attr.mode == "file"
end

local function extract_path(path)
	local sign = ""
	if #path > 1 then
		sign = path:sub(1,1)
		if sign == "@" or sign == "#" then
			path = path:sub(2)
		end
	end
	return sign, path
end

local function proxy_lua_loader(path)
  local override = package.overrides[path]
  
  if override == nil then
	rr.log_error("require:lua_loader: Override is nil for: " ..path)
	override = {}
  end
  
  if override.load_original then
	override.load_original = false
	return sg_loader(path)
  elseif override.load_override then
    rr.log_info("Overriding require: " .. path)
	override.load_override = false
	return lua_loader(path)
  else
	rr.log_error("require:lua_loader: No load directive for: " ..path .." resorting to default")
	return sg_loader(path)
  end
end

local function proxy_require(path)
	local sign, path = extract_path(path)
	local is_override = sign == "#" or (sign ~= "@" and package.searchpath(path, package.path))
	local loaded = package.loaded[path]
	local override
	
	if loaded == nil then
		--reset overrides too incase there was a forced reload
		override = {}
		package.overrides[path] = override
	else
		override = package.overrides[path]
		if override == nil then
			override = { original = loaded }
			package.overrides[path] = override
		end
	end
	
	if is_override then
		if override.override then
			--return existing override
			--TODO add preload support
			return override.override
		else
			if loaded then
				package.loaded[path] = nil
			end
			override.load_override = true
			local res = lua_require(path) or true
			override.override = res
			return res
		end
	else --use original
		if override.original then
			return override.original
		else
			if loaded then
				package.loaded[path] = nil
			end
			override.load_original = true
			local res = lua_require(path) or true
			override.original = res
			return res
		end
	end
end

local function proxy_dofile(path)
	local sign, path = extract_path(path)
	local system_path = overrides_path ..path ..".lua"
	
	local is_override = sign == "#" or (sign ~= "@" and isfileexists(system_path))
  
	if is_override then
		rr.log_info("Overriding dofile: " ..path .." with: " ..system_path)
		return lua_dofile(system_path)
	else
		return sg.dofile(path)
	end
	
end

local function proxy_loadfile(path)
	local sign, path = extract_path(path)
	local system_path = overrides_path ..path ..".lua"
	
	local is_override = sign == "#" or (sign ~= "@" and isfileexists(system_path))
	
	if is_override then
		rr.log_info("Overriding loadfile: " ..path .." with: " ..system_path)
		return lua_loadfile(system_path)
	else
		return sg.loadfile(path)
	end
end

local function copy_stingray_overloads()
	sg.package = table_shallow_copy(package, true)
	sg.package.loaders = table_shallow_copy(package.loaders, true)
	sg.require = require
	sg.dofile = dofile
	sg.loadfile = loadfile
	sg.load = load
	sg.tostring = tostring
	sg_loader = package.loaders[2]
end

local function reloadlibs()
	rr.openlibs()
	rr.openlibs = nil
end

local function repath()
	package.path = overrides_path .."?.lua;"
end

local function copy_std_lua_funcs()
	lua_loader = package.loaders[2]
	c_loader = package.loaders[3]
	croot_loader = package.loaders[4]
	lua_dofile = dofile
	lua_loadfile = loadfile
	lua_load = load
	lua_require = require
end

local function restore_stingray_overloads()
	require = sg.require
	load = sg.load
	--tostring = sg.tostring
	package.loaders[3] = sg.package.loaders[3]
	package.loaders[4] = sg.package.loaders[4]
	
end

local function place_proxies()
	package.overrides = {}
	require = proxy_require
	dofile = proxy_dofile
	loadfile = proxy_loadfile
	package.loaders[2] = proxy_lua_loader
end

copy_stingray_overloads()
reloadlibs()
repath()
copy_std_lua_funcs()
restore_stingray_overloads()
place_proxies()
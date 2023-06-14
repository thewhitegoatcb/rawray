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
 --local  table_shallow_copy = package.preload["table.clone"] or function(t)
local table_shallow_copy = function(t)
	local copy = {}

	for key, value in pairs(t) do
		copy[key] = value
	end

	return copy
end

local function isfileexists(path)
	return package.searchpath(path, package.path) ~= nil

	--local attr = _lfs.attributes(path)
	--return attr and attr.mode == "file"
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

local function should_override(path)
	local sign, path = extract_path(path)
	
	if sign == "@" then
		return false, path
	elseif sign == "#" then
		return true, package.searchpath(path, package.path)
	else
		local system_path = package.searchpath(path, package.path)
		if system_path then
			return true, system_path
		end
		return false, path
	end
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
		rr.log_warning("require:lua_loader: No load directive for: " ..path .." resorting to default")
		return sg_loader(path)
	end
end

local function proxy_require(path)
	local sign, path = extract_path(path)
	local is_override = sign == "#" or (sign ~= "@" and package.searchpath(path, package.path))
	local loaded = package.loaded[path]
	local override
	
	if loaded ~= nil then
		override = package.overrides[path]
		if override == nil then
			override = { original = loaded }
			package.overrides[path] = override
		end
	else
		-- reset overrides too incase there was a forced reload
		override = {}
		package.overrides[path] = override
	end
	
	if is_override then
		if override.override ~= nil then
			-- return existing override
			-- TODO add preload support
			return override.override
		else
			package.loaded[path] = nil
			override.load_override = true
			override.override = lua_require(path)
			return override.override
		end
	else --use original
		if override.original ~= nil then
			return override.original
		else
			package.loaded[path] = nil
			override.load_original = true
			override.original = lua_require(path)
			return override.original
		end
	end
end

local function proxy_dofile(path)
	local is_override, system_path = should_override(path)
	
	if is_override then
		rr.log_info("Overriding dofile: " ..path .." with: " ..system_path)
		return lua_dofile(system_path)
	else
		return sg.dofile(system_path)
	end
	
end

local function proxy_loadfile(path)
	local is_override, system_path = should_override(path)
	
	if is_override then
		rr.log_info("Overriding loadfile: " ..path .." with: " ..system_path)
		return lua_loadfile(system_path)
	else
		return sg.loadfile(system_path)
	end
end



local function copy_stingray_overloads()
	sg.package = table_shallow_copy(package)
	sg.package.loaders = table_shallow_copy(package.loaders)
	--sg.package.preload = table_shallow_copy(package.preload, true)
	sg.require = require
	sg.dofile = dofile
	sg.loadfile = loadfile
	sg.load = load
	sg.tostring = tostring
	sg_loader = package.loaders[2]
end

local function reloadlibs()
	rr.openlibs()
end

local function repath()
	local paths
	if rr.config and rr.config.overrider and rr.config.overrider.paths then
		paths = rr.config.overrider.paths
		package.path = ""
	else
		package.path = rr.root_dir .."overrides/?.lua;"
		return
	end
	
	for _, path in ipairs(paths) do
		package.path = package.path ..path ..";"
	end
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
	tostring = sg.tostring
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
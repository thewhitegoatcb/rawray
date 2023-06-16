local lfs = lfs
local raw_dofile = rr.raw_dofile

local function scrub_library(lib)
	rawset(_G, lib, nil)

	package.loaded[lib] = nil
	package.preload[lib] = nil
end
	
local function get_rawray_root_dir()
  return lfs.currentdir():match("(.*)[/\\][^/\\]+[/\\]?$") .."/rawray/"
end

local function load_config()
	local res, config = pcall(rr.dofile, "config.lua")
	if res then
		if type(config) == "table" then
			rr.config = config
			rr.log_info("Loaded config")
		else
			rr.log_error("Failed to load config, isn't a table it's:" ..type(config))
		end
	else
		rr.log_error("Failed to load config: " ..config)
	end
end

local function process_config()
	if type(rr.config) ~= "table" then
		rr.log_error("Failed to process config it doesn't exist or not loaded correctly")
		return
	end
	
	if not rr.config["keep_lfs"] then
		scrub_library("lfs")
	end
	if not rr.config["keep_msgbox"] then
		rr.msgbox = nil
	end
	if not rr.config["keep_raw_dofile"] then
		rr.raw_dofile = nil
	end
	if not rr.config["keep_openlibs"] then
		rr.openlibs = nil
	end
	rr.log_info("Finished processing config")
end

local function addons_load(path)
	local res, addon = pcall(rr.raw_dofile, path.."/init.lua")
	if not res then
		rr.log_error("Failed loading addon at:" ..path .. " , with error: " ..addon)
		return
	end
	if type(addon) ~= "table" then
		rr.log_error("Failed loading addon at:" ..path .. " , is not a table: " ..type(addon))
		return
	end
	if type(addon.name) ~= "string" then
		rr.log_error("Failed loading addon at:" ..path .. " name is not a string: " ..type(addon.name))
		return
	end
	rr.addons[addon.name] = addon

	if type(addon.onload) == "function" then
		local res, error_str = pcall(addon.onload)
		if not res then
			rr.log_error("Failed loading addon: "..addon.name .." onload: " ..error_str)
			rr.addons[addon.name] = nil
			return
		end
		rr.log_info("Loaded addon: "..addon.name)
	end
end

local function addons_load_all()
	local path = rr.root_dir .."addons"
	for file in lfs.dir(path) do
        if file ~= "." and file ~= ".." and file ~= "disabled" then
			local f = path..'/'..file
			local attr = lfs.attributes (f)
			if type(attr) == "table" and attr.mode == "directory" then
				rr.log_info("Found addon: " ..file .." trying to load...")
				addons_load(f)
			end

		end
	end
	rr.log_info("Finished loading addons")
	for k,addon in pairs(rr.addons) do
		if type(addon.all_loaded) == "function" then
			local res, error_str = pcall(addon.all_loaded)
			if not res then
				rr.log_error( k ..": all_loaded failed with: " ..error_str)
			end
		end
	end
end

local function addons_update(dt)
	for k,addon in pairs(rr.addons) do
		if type(addon.update) == "function" then
			local res, error_str = pcall(addon.update)
			if not res then
				rr.log_error( k ..": update failed with: " ..error_str)
				addon.update = nil
			end
		end
	end
end

local function addons_unload()
	rr.log_info("Unloading addons")
	for k,addon in pairs(rr.addons) do
		if type(addon.unload) == "function" then
			local res, error_str = pcall(addon.unload)
			if not res then
				rr.log_error( k ..": unload failed with: " ..error_str)
			end
		end
	end
	rr.addons = {}
	rr.log_info("Finished unloading addons")
end

rr.addons = {}
rr.root_dir = get_rawray_root_dir()
rr.dofile = function(filename)
	return raw_dofile(rr.root_dir ..filename)
end

load_config()
addons_load_all()
process_config()

return addons_update, addons_unload
rr.log_info("Overriding boot_init")

local _ffi = ffi
local _io = io
local _os = os
local _loadlib = package.loadlib

dofile("@scripts/boot_init") -- prefixing with @ makes sure we are not calling the override again

if rr.config["keep_io"] then
	io = _io
	package.loaded["io"] = io or true
end

if rr.config["keep_os"] then
	os = _os
end

if rr.config["keep_ffi"] then
	ffi = _ffi
	package.loaded["ffi"] = ffi or true
end

if rr.config["keep_loadlib"] then
	package.loadlib = _loadlib
end
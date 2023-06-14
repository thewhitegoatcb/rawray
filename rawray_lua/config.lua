return {
	keep_lfs = false,
	keep_msgbox = false,
	keep_raw_dofile = false,
	keep_openlibs = false,
	
	overrider = {
		enable = false,
		keep_io = false, -- restores io module
		keep_os = false, -- restores os module
		keep_ffi = false, -- restores ffi module
		keep_loadlib = false, -- restores package.loadlib
		paths = {
			"../rawray/overrides/?.lua",
		}
	},
	
	debugger = {
		enable = true, -- does nothing if not installed
		address = "127.0.0.1:12302",
	}
}
rr.config = {
	keep_lfs = false,
	keep_msgbox = false,
	keep_raw_dofile = false,
	keep_openlibs = false,
	
	overrider = {
		enable = true,
		keep_io = false, -- restores io module
		keep_os = false, -- restores os module
		keep_ffi = false, -- restores ffi module
		keep_loadlib = false, -- restores package.loadlib
		keep_tostring = false, -- needed for the debugger, version check, its a hack need a better solution
	},
	
	debugger = {
		enable = false,
		apply_new_overrides = false, -- applies some overrides for a new version of luajit to work(depended on overrider)
		address = "127.0.0.1:12302",
	}
}
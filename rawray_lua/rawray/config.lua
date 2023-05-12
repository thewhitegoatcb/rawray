rr.config = {

	keep_lfs = false, -- scrubs the lfs library. it doesn't unload it, if you are using it one of the addons make sure you copy it before it gets scrubbed
	keep_msgbox = false, --removes msgbox from rr
	keep_raw_dofile = false, --removes raw_dofile from rr
	keep_openlibs = false, --removes openlibs from rr
	
	--overrider--
	keep_io = false, --restores io module
	keep_os = false, --restores os module
	keep_ffi = false, --restores ffi module
	keep_loadlib = false, --restores package.loadlib
	-------------
}
local _main
local is_set = false

local debugger = {
	name = "debugger",
	
	onload = function() 


	end,
	all_loaded = function()
		if not rr.config or not rr.config.debugger or not rr.config.debugger.enable then
			is_set = true -- don't disable deadlock
			return
		end
		local address = "127.0.0.1:12302"
		if rr.config and rr.config.debugger then
			address = rr.config.debugger["address"] or address
		end
		
		_main = rr.dofile("addons/debugger/debugger.lua")
		_main:start(address):event("wait")

	end,
	
	update = function(dt)
		if not is_set then --disable deadlock detector
			s3d.Deadlock.pause()
			s3d.Deadlock.pause = function() end
			s3d.Deadlock.unpause = function() end
			is_set = true
		end
	end,
	
	unload = function()
	
	end,
}

return debugger
local _main
local overrider = {
	name = "overrider",
	
	onload = function() 
		_main = rr.dofile("addons/overrider/overrider.lua")
	end,
	
	all_loaded = function()
	
	end,
	
	update = function(dt)
		
	end,
	
	unload = function()
	
	end,
}

return overrider
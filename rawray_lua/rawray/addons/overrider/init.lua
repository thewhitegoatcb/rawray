local _main
local overrider = {
	name = "overrider",
	
	onload = function()
		if rr.config and rr.config.overrider and rr.config.overrider.enable then
			_main = rr.dofile("addons/overrider/overrider.lua")
		end
	end,
	
	all_loaded = function()
	
	end,
	
	update = function(dt)
		
	end,
	
	unload = function()
	
	end,
}

return overrider
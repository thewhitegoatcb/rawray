local jitter = {
	name = "jitter",
	
	onload = function() 


	end,
	all_loaded = function()
		jit.on()
		jit.off = function (...) end
		jit.on = function (...) end
		jit.flush = function (...) end
	end,
	
	update = function(dt)
		
	end,
	
	unload = function()
	
	end,
}

return jitter
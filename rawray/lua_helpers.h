#pragma once
#include "PluginApi128.h"

namespace rawray::lua
{
	struct G
	{
		inline static const LuaApi128* _lua = nullptr;
		inline static int update_ref = -2;
		inline static int unload_ref = -2;
	};

	void update(float dt);
	void start_env(LuaApi128* lua);
	void unload();
}
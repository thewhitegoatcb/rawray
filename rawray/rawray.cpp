#include "lua.h"
#include "PluginApi128.h"
#include "lua_helpers.h"

#ifdef _DEBUG
#include <Windows.h>
#endif

#include "clue.hpp"

static void setup_game(GetApiFunction get_engine_api)
{
	auto lua = (LuaApi128*)get_engine_api(LUA_API_ID);
	rawray::lua::start_env(lua);
}

static const char* get_name()
{
	return "rawray";
}

static void loaded(GetApiFunction get_engine_api)
{
	LOG_INFO("------Loaded RawRay-------");
#ifdef _DEBUG
	MessageBoxA(NULL, "Loaded", "Loaded", 0);
#endif
}

static void update(float dt)
{
	rawray::lua::update(dt);
}

static void shutdown()
{
#ifdef _DEBUG
	MessageBoxA(NULL, "shutdown", "shutdown", 0);
#endif
	rawray::lua::unload();
}

extern "C" {
	void* get_dynamic_plugin_api(unsigned api)
	{
		if (api == PLUGIN_API_ID) {
			static PluginApi128 api{};
			api.get_name = get_name;
			api.setup_game = setup_game;
			api.loaded = loaded;
			api.update_game = update;
			api.shutdown_game = shutdown;
			return &api;
		}
		return nullptr;
	}

#if !defined STATIC_PLUGIN_LINKING
	PLUGIN_DLLEXPORT void* get_plugin_api(unsigned api)
	{
		return get_dynamic_plugin_api(api);
	}
#endif
}

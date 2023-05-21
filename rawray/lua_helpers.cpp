#include "lua.hpp"
#include "lua_helpers.h"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include "lfs/lfs.h"
#include "clue.hpp"


namespace rawray::lua
{
	static int _openlibs(lua_State* L)
	{
		LOG_INFO("Reloading libs");
		G::_lua->lib_openlibs(L);
		return 0;
	}

#ifdef _WIN32
	static int _msgbox(lua_State* L)
	{
		const char* msg = luaL_checklstring(L, 1, nullptr);
		const char* title = luaL_checklstring(L, 2, nullptr);
		::MessageBoxA(nullptr, msg, title, 0);
		return 0;
	}
#endif // _WIN32

	static int _raw_dofile(lua_State* L)
	{
		const char* fname = luaL_optstring(L, 1, NULL);
		lua_settop(L, 1);
		if (luaL_loadfile(L, fname) != LUA_OK)
			return lua_error(L);
		lua_call(L, 0, LUA_MULTRET);
		return lua_gettop(L) - 1;
	}

	static int _log_info(lua_State* L)
	{
		auto msg = luaL_checklstring(L, 1, nullptr);
		if(msg != nullptr)
			LOG_INFO(msg);
		return 0;
	}

	static int _log_error(lua_State* L)
	{
		auto msg = luaL_checklstring(L, 1, nullptr);
		if (msg != nullptr)
			LOG_ERROR(msg);
		return 0;
	}

	static int _log_debug(lua_State* L)
	{
		auto msg = luaL_checklstring(L, 1, nullptr);
		if (msg != nullptr)
			LOG_DEBUG(msg);
		return 0;
	}

	static int _log_warning(lua_State* L)
	{
		auto msg = luaL_checklstring(L, 1, nullptr);
		if (msg != nullptr)
			LOG_WARNING(msg);
		return 0;
	}

	static int get_ref_top_function(lua_State* L)
	{
		if (lua_isfunction(L, -1))
		{
			return luaL_ref(L, LUA_REGISTRYINDEX);
		}
		lua_pop(L, 1);
		return LUA_NOREF;
	}

	static void unref(lua_State* L)
	{
		if (G::unload_ref != LUA_NOREF && G::unload_ref != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, G::unload_ref);
		if (G::update_ref != LUA_NOREF && G::update_ref != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, G::update_ref);
		G::update_ref = LUA_NOREF;
		G::unload_ref = LUA_NOREF;
	}

	void update(float dt)
	{
		if (G::update_ref != LUA_NOREF && G::update_ref != LUA_REFNIL)
		{
			auto L = G::_lua->getscriptenvironmentstate();
			lua_rawgeti(L, LUA_REGISTRYINDEX, G::update_ref);
			lua_pushnumber(L, static_cast<lua_Number>(dt));
			if (lua_pcall(L, 1, LUA_MULTRET, 0) != LUA_OK)
			{
				auto error = lua_tolstring(L, -1, nullptr);
				LOG_DEBUG("Error in update function: " << error);
			}
		}
	}

	void unload()
	{
		auto L = G::_lua->getscriptenvironmentstate();
		if (G::unload_ref != LUA_NOREF && G::unload_ref != LUA_REFNIL)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, G::unload_ref);
			if (lua_pcall(L, 0, LUA_MULTRET, 0) != LUA_OK)
			{
				auto error = lua_tolstring(L, -1, nullptr);
				LOG_DEBUG("Error in unload function: " << error);
			}
		}
		unref(L);
	}

	void start_env(LuaApi128* lua)
	{
		LOG_INFO("Registering lua env");
		G::_lua = lua;
		lua_State* L = lua->getscriptenvironmentstate();
		
		const luaL_Reg reg[]{
			{"raw_dofile", _raw_dofile},
			{"openlibs", _openlibs},
			{"log_info", _log_info},
			{"log_error", _log_error},
			{"log_debug", _log_debug},
			{"log_warning", _log_warning},
			#ifdef _WIN32
			{"msgbox", _msgbox},
			#endif // _WIN32
			{nullptr, nullptr} 
		};
		luaL_register(L, "rr", reg);

		luaopen_lfs(L);

		auto error_code = luaL_loadfile(L, "../rawray/pre_boot.lua");
		if (error_code != LUA_OK)
		{
			LOG_ERROR("Error loading pre_load.lua: " << error_code);
			return;
		}
		if (lua_pcall(L, 0, LUA_MULTRET, 0) == LUA_OK)
		{
			if (auto top = lua_gettop(L); top >= 2)
			{
				G::unload_ref = get_ref_top_function(L);
				G::update_ref = get_ref_top_function(L);
				lua_settop(L, 1);
			}
			LOG_INFO("Finished executing pre_load.lua successfully");
		}
		else
		{
			auto error = lua_tolstring(L, -1, nullptr);
			LOG_ERROR("Error in pre_load.lua : " << error);
#ifdef _WIN32
			::MessageBoxA(nullptr, error, "RawRay Lua Error!", 0);
#endif // _WIN32
		}
	}
}
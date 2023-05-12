#include "lua.hpp"
#include "lua_helpers.h"

#define LA rawray::lua::G::_lua

lua_State* lua_newstate(lua_Alloc f, void* ud) { return LA->newstate(f, ud); }
void  lua_close(lua_State* L) { LA->close(L); }
lua_State* lua_newthread(lua_State* L) { return LA->newthread(L); }

lua_CFunction lua_atpanic(lua_State* L, lua_CFunction panicf) { return LA->atpanic(L, panicf); }

int   lua_gettop(lua_State* L) { return LA->gettop(L); }
void  lua_settop(lua_State* L, int idx) { LA->settop(L, idx); }
void  lua_pushvalue(lua_State* L, int idx) { LA->pushvalue(L, idx); }
void  lua_remove(lua_State* L, int idx) { LA->remove(L, idx); }
void  lua_insert(lua_State* L, int idx) { LA->insert(L, idx); }
void  lua_replace(lua_State* L, int idx) { LA->replace(L, idx); }
int   lua_checkstack(lua_State* L, int sz) { return LA->checkstack(L, sz); }

void  lua_xmove(lua_State* from, lua_State* to, int n) { LA->xmove(from, to, n); }

int             lua_isnumber(lua_State* L, int idx) { return LA->isnumber(L, idx); }
int             lua_isstring(lua_State* L, int idx) { return LA->isstring(L, idx); }
int             lua_iscfunction(lua_State* L, int idx) { return LA->iscfunction(L, idx); }
int             lua_isuserdata(lua_State* L, int idx) { return LA->isuserdata(L, idx); }
int             lua_type(lua_State* L, int idx) { return LA->type(L, idx); }
const char* lua_typename(lua_State* L, int tp) { return LA->lua_typename(L, tp); }

int            lua_equal(lua_State* L, int idx1, int idx2) { return LA->equal(L, idx1, idx2); }
int            lua_rawequal(lua_State* L, int idx1, int idx2) { return LA->rawequal(L, idx1, idx2); }
int            lua_lessthan(lua_State* L, int idx1, int idx2) { return LA->lessthan(L, idx1, idx2); }

lua_Number  lua_tonumber (lua_State* L, int idx) { return LA->tonumber(L, idx); }
lua_Integer lua_tointeger (lua_State* L, int idx) { return LA->tointeger(L, idx); }
int         lua_toboolean(lua_State* L, int idx) { return LA->toboolean(L, idx); }
const char* lua_tolstring(lua_State* L, int idx, size_t* len) { return LA->tolstring(L, idx, len); }
size_t      lua_objlen (lua_State* L, int idx) { return LA->objlen(L, idx); }
lua_CFunction lua_tocfunction (lua_State* L, int idx) { return LA->tocfunction(L, idx); }
void* lua_touserdata(lua_State* L, int idx) { return LA->touserdata(L, idx); }
lua_State* lua_tothread(lua_State* L, int idx) { return LA->tothread(L, idx); }
const void* lua_topointer(lua_State* L, int idx) { return LA->topointer(L, idx); }


void  lua_pushnil(lua_State* L) { LA->pushnil(L); }
void  lua_pushnumber(lua_State* L, lua_Number n) { LA->pushnumber(L, n); }
void  lua_pushinteger(lua_State* L, lua_Integer n) { LA->pushinteger(L, n); }
void  lua_pushlstring(lua_State* L, const char* s, size_t l) { LA->pushlstring(L, s, l); }
void  lua_pushstring(lua_State* L, const char* s) { LA->pushstring(L, s); }
const char* lua_pushvfstring(lua_State* L, const char* fmt, va_list argp) { return LA->pushvfstring(L, fmt, argp); }

const char* lua_pushfstring(lua_State* L, const char* fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	auto res = lua_pushvfstring(L, fmt, argptr);
	va_end(argptr);
	return res;
}

void   lua_pushcclosure(lua_State* L, lua_CFunction fn, int n) { LA->pushcclosure(L, fn, n); }
void   lua_pushboolean(lua_State* L, int b) { LA->pushboolean(L, b); }
void   lua_pushlightuserdata(lua_State* L, void* p) { LA->pushlightuserdata(L, p); }
int    lua_pushthread(lua_State* L) { return LA->pushthread(L); }
	   
	   
	   
	   
void   lua_gettable(lua_State* L, int idx) { LA->gettable(L, idx); }
void   lua_getfield(lua_State* L, int idx, const char* k) { LA->getfield(L, idx, k); }
void   lua_rawget(lua_State* L, int idx) { LA->rawget(L, idx); }
void   lua_rawgeti(lua_State* L, int idx, int n) { LA->rawgeti(L, idx, n); }
void   lua_createtable(lua_State* L, int narr, int nrec) { LA->createtable(L, narr, nrec); }
void*  lua_newuserdata(lua_State* L, size_t sz) { return LA->newuserdata(L, sz); }
int    lua_getmetatable(lua_State* L, int objindex) { return LA->getmetatable(L, objindex); }
void   lua_getfenv(lua_State* L, int idx) { LA->getfenv(L, idx); }
	   
	   
	   
	   
void   lua_settable(lua_State* L, int idx) { LA->settable(L, idx); }
void   lua_setfield(lua_State* L, int idx, const char* k) { LA->setfield(L, idx, k); }
void   lua_rawset(lua_State* L, int idx) { LA->rawset(L, idx); }
void   lua_rawseti(lua_State* L, int idx, int n) { LA->rawseti(L, idx, n); }
int    lua_setmetatable(lua_State* L, int objindex) { return LA->setmetatable(L, objindex); }
int    lua_setfenv(lua_State* L, int idx) { return LA->setfenv(L, idx); }
	   
	   
	   
	   
void   lua_call(lua_State* L, int nargs, int nresults) { return LA->call(L, nargs, nresults); }
int    lua_pcall(lua_State* L, int nargs, int nresults, int errfunc) { return LA->pcall(L, nargs, nresults, errfunc); }
int    lua_cpcall(lua_State* L, lua_CFunction func, void* ud) { return LA->cpcall(L, func, ud); }
int    lua_load(lua_State* L, lua_Reader reader, void* dt, const char* chunkname) { return LA->load(L, reader, dt, chunkname); }
int    lua_dump(lua_State* L, lua_Writer writer, void* data) { return LA->dump(L, writer, data); }



int  lua_yield(lua_State* L, int nresults) { return LA->yield(L, nresults); }
int  lua_resume(lua_State* L, int narg) { return LA->resume(L, narg); }
int  lua_status(lua_State* L) { return LA->status(L); }

int  lua_gc(lua_State* L, int what, int data) { return LA->gc(L, what, data); }


int   lua_error(lua_State* L) { return LA->error(L); }

int   lua_next(lua_State* L, int idx) { return LA->next(L, idx); }

void  lua_concat(lua_State* L, int n) { LA->concat(L, n); }

//lua_Alloc(lua_getallocf) (lua_State* L, void** ud);
//void lua_setallocf(lua_State* L, lua_Alloc f, void* ud);

//void lua_setlevel(lua_State* from, lua_State* to);

int lua_getstack(lua_State* L, int level, lua_Debug* ar) { return LA->getstack(L, level, ar); }
int lua_getinfo(lua_State* L, const char* what, lua_Debug* ar) { return LA->getinfo(L, what, ar); }
const char* lua_getlocal(lua_State* L, const lua_Debug* ar, int n) { return LA->getlocal(L, ar, n); }
const char* lua_setlocal(lua_State* L, const lua_Debug* ar, int n) { return LA->setlocal(L, ar, n); }
const char* lua_getupvalue(lua_State* L, int funcindex, int n) { return LA->getupvalue(L, funcindex, n); }
const char* lua_setupvalue(lua_State* L, int funcindex, int n) { return LA->setupvalue(L, funcindex, n); }
int lua_sethook(lua_State* L, lua_Hook func, int mask, int count) { return LA->sethook(L, func, mask, count); }
lua_Hook lua_gethook(lua_State* L) { return LA->gethook(L); }
int lua_gethookmask(lua_State* L) { return LA->gethookmask(L); }
int lua_gethookcount(lua_State* L) { return LA->gethookcount(L); }

//void* lua_upvalueid(lua_State* L, int idx, int n);
//void lua_upvaluejoin(lua_State* L, int idx1, int n1, int idx2, int n2);
//int lua_loadx(lua_State* L, lua_Reader reader, void* dt, const char* chunkname, const char* mode);
//const lua_Number* lua_version(lua_State* L);
//void lua_copy(lua_State* L, int fromidx, int toidx);
//lua_Number lua_tonumberx(lua_State* L, int idx, int* isnum);
//lua_Integer lua_tointegerx(lua_State* L, int idx, int* isnum);

//int lua_isyieldable(lua_State* L);


//////LUA LIB


void (luaL_openlib)(lua_State* L, const char* libname, const luaL_Reg* l, int nup) { LA->lib_openlib(L, libname, l, nup); }
void (luaL_register)(lua_State* L, const char* libname, const luaL_Reg* l) { LA->lib_register(L, libname, l); }
int (luaL_getmetafield)(lua_State* L, int obj, const char* e) { return LA->lib_getmetafield(L, obj, e); }
int (luaL_callmeta)(lua_State* L, int obj, const char* e) { return LA->lib_callmeta(L, obj, e); }
int (luaL_typerror)(lua_State* L, int narg, const char* tname) { return LA->lib_typerror(L, narg, tname); }
int (luaL_argerror)(lua_State* L, int numarg, const char* extramsg) { return LA->lib_argerror(L, numarg, extramsg); }
const char* (luaL_checklstring)(lua_State* L, int numArg, size_t* l) { return LA->lib_checklstring(L, numArg, l); }
const char* (luaL_optlstring)(lua_State* L, int numArg, const char* def, size_t* l) { return LA->lib_optlstring(L, numArg, def, l); }
lua_Number(luaL_checknumber) (lua_State* L, int numArg) { return LA->lib_checknumber(L, numArg); }
lua_Number(luaL_optnumber) (lua_State* L, int nArg, lua_Number def) { return LA->lib_optnumber(L, nArg, def); }

lua_Integer(luaL_checkinteger) (lua_State* L, int numArg) { return LA->lib_checkinteger(L, numArg); }
lua_Integer(luaL_optinteger) (lua_State* L, int nArg, lua_Integer def) { return LA->lib_optinteger(L, nArg, def); }

void (luaL_checkstack)(lua_State* L, int sz, const char* msg) { LA->lib_checkstack(L, sz, msg); }
void (luaL_checktype)(lua_State* L, int narg, int t) { LA->lib_checktype(L, narg, t); }
void (luaL_checkany)(lua_State* L, int narg) { LA->lib_checkany(L, narg); }

int   (luaL_newmetatable)(lua_State* L, const char* tname) { return LA->lib_newmetatable(L, tname); }
void* (luaL_checkudata)(lua_State* L, int ud, const char* tname) { return LA->lib_checkudata(L, ud, tname); }

void (luaL_where)(lua_State* L, int lvl) { LA->lib_where(L, lvl); }
int (luaL_error)(lua_State* L, const char* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	luaL_where(L, 1);
	lua_pushvfstring(L, fmt, argp);
	va_end(argp);
	lua_concat(L, 2);
	return lua_error(L);
}

int (luaL_checkoption)(lua_State* L, int narg, const char* def, const char* const lst[]) { return LA->lib_checkoption(L, narg, def, lst); }


int (luaL_ref)(lua_State* L, int t) { return LA->lib_ref(L, t); }
void (luaL_unref)(lua_State* L, int t, int ref) { LA->lib_unref(L, t, ref); }

int (luaL_loadfile)(lua_State* L, const char* filename) { return LA->lib_loadfile(L, filename); }
int (luaL_loadbuffer)(lua_State* L, const char* buff, size_t sz, const char* name) { return LA->lib_loadbuffer(L, buff, sz, name); }
int (luaL_loadstring)(lua_State* L, const char* s) { return LA->lib_loadstring(L, s); }

lua_State* (luaL_newstate)(void) { return LA->lib_newstate(); }


const char* (luaL_gsub)(lua_State* L, const char* s, const char* p, const char* r) { return LA->lib_gsub(L, s, p, r); }

const char* (luaL_findtable)(lua_State* L, int idx, const char* fname, int szhint) { return LA->lib_findtable(L, idx, fname, szhint); }

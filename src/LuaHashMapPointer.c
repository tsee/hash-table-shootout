#include "LuaHashMap.h"
#define SETUP \
	LuaHashMap* hash = LuaHashMap_Create();
#define INSERT_INT_INTO_HASH(key, value) do { \
		LuaHashMap_SetValuePointerForKeyPointer(hash, (void*)value, (void*)key); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
		LuaHashMap_RemoveKeyPointer(hash, (void*)key); \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
		LuaHashMap_SetValuePointerForKeyPointer(hash, (void*)value, (void*)key); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
		LuaHashMap_RemoveKeyPointer(hash, (void*)key); \
    } while(0)
#include "template.c"

#include "LuaHashMap.h"
LuaHashMap* hash = NULL;
#define SETUP \
	hash = LuaHashMap_Create();
#define INSERT_INT_INTO_HASH(key, value) do { \
		LuaHashMap_SetValueIntegerForKeyInteger(hash, value, key); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
		LuaHashMap_RemoveKeyInteger(hash, key); \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
		LuaHashMap_SetValueIntegerForKeyString(hash, value, key); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
		LuaHashMap_RemoveKeyString(hash, key); \
    } while(0)


int ExistsInIntHash(int key)
{
	return LuaHashMap_ExistsKeyInteger(hash, key);
}

int ExistsInStrHash(const char* key)
{
	return LuaHashMap_ExistsKeyString(hash, key);
}
#include "template.c"

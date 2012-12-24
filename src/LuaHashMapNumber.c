#include "LuaHashMap.h"
	LuaHashMap* hash = NULL;
#define SETUP \
	hash = LuaHashMap_Create();
#define INSERT_INT_INTO_HASH(key, value) do { \
		LuaHashMap_SetValueNumberForKeyNumber(hash, value, key); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
		LuaHashMap_RemoveKeyNumber(hash, key); \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
		LuaHashMap_SetValueNumberForKeyString(hash, value, key); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
		LuaHashMap_RemoveKeyString(hash, key); \
    } while(0)


int ExistsInIntHash(int key)
{
	return LuaHashMap_ExistsKeyNumber(hash, key);
}

int ExistsInStrHash(const char* key)
{
	return LuaHashMap_ExistsKeyNumber(hash, (size_t)((void*)key));
}

#include "template.c"


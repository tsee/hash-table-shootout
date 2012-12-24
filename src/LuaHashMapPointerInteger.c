#include "LuaHashMap.h"
LuaHashMap* hash = NULL;
#define SETUP \
	 hash = LuaHashMap_Create();
#define INSERT_INT_INTO_HASH(key, value) do { \
		LuaHashMap_SetValueIntegerForKeyPointer(hash, value, (void*)key); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
		LuaHashMap_RemoveKeyPointer(hash, (void*)key); \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
		LuaHashMap_SetValueIntegerForKeyPointer(hash, value, (void*)key); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
		LuaHashMap_RemoveKeyPointer(hash, (void*)key); \
    } while(0)

int ExistsInIntHash(int key)
{
	return LuaHashMap_ExistsKeyPointer(hash, (void*)key);
}

int ExistsInStrHash(const char* key)
{
	return LuaHashMap_ExistsKeyPointer(hash, (void*)key);
}

#include "template.c"

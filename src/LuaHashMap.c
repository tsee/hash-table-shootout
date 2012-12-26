#include "LuaHashMap.h"
LuaHashMap* hash = NULL;
#define SETUP(num_keys) do { \
	hash = LuaHashMap_CreateWithSizeHints(0,num_keys); \
	} while(0)

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

static inline const char* InsertStrIntoHash(const char* key, int value)
{
	return LuaHashMap_SetValueIntegerForKeyString(hash, value, key);

}

int ExistsInIntHash(int key)
{
	return LuaHashMap_ExistsKeyInteger(hash, key);
}

int ExistsInStrHash(const char* key)
{
	return LuaHashMap_ExistsKeyString(hash, key);
}
#include "template.c"

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

static inline int ExistsInIntHash(int key)
{
	return LuaHashMap_ExistsKeyInteger(hash, key);
}

static inline int ExistsInStrHash(const char* key)
{
	return LuaHashMap_ExistsKeyString(hash, key);
}

static inline int ExistsInStrHashWithLength(const char* key, size_t length)
{
	return LuaHashMap_ExistsKeyStringWithLength(hash, key, length);
}

static inline void SetIntIntoHash(int key, int value)
{
	LuaHashMap_SetValueIntegerForKeyInteger(hash, value, key);	
}

static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
	LuaHashMap_SetValueIntegerForKeyStringWithLength(hash, value, key, length);		
}


#include "template.c"

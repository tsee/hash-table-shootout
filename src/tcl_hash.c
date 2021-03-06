#include <Tcl/tcl.h>
	Tcl_HashTable hash_int; 
	Tcl_HashTable hash_str; 
#define SETUP(num_keys) do { \
	Tcl_InitHashTable(&hash_int, TCL_ONE_WORD_KEYS); \
	Tcl_InitHashTable(&hash_str, TCL_STRING_KEYS); \
	} while(0)
	
#define INSERT_INT_INTO_HASH(key, value) do { \
		Tcl_HashEntry* hash_entry; \
		int new_val; \
		hash_entry = Tcl_FindHashEntry(&hash_int, (const char*)key); \
		if(NULL == hash_entry) \
		{ \
			hash_entry = Tcl_CreateHashEntry(&hash_int, (const char*)key, &new_val); \
		} \
		Tcl_SetHashValue(hash_entry, (ClientData)value); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
		Tcl_HashEntry* hash_entry; \
		hash_entry = Tcl_FindHashEntry(&hash_int, (const char*)key); \
		if(NULL != hash_entry) \
		{ \
			Tcl_DeleteHashEntry(hash_entry); \
		} \
	} while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
		Tcl_HashEntry* hash_entry; \
		int new_val; \
		hash_entry = Tcl_FindHashEntry(&hash_str, (const char*)key); \
		if(NULL == hash_entry) \
		{ \
			hash_entry = Tcl_CreateHashEntry(&hash_str, (const char*)key, &new_val); \
		} \
		Tcl_SetHashValue(hash_entry, (ClientData)value); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
		Tcl_HashEntry* hash_entry; \
		hash_entry = Tcl_FindHashEntry(&hash_str, (const char*)key); \
		if(NULL != hash_entry) \
		{ \
			Tcl_DeleteHashEntry(hash_entry); \
		} \
    } while(0)

	
static inline const char* InsertStrIntoHash(const char* key, int value)
{
	INSERT_STR_INTO_HASH(key, value);
	return key;
}

static inline int ExistsInIntHash(int key)
{
	Tcl_HashEntry* hash_entry;
	hash_entry = Tcl_FindHashEntry(&hash_int, (const char*)key); 

	if(hash_entry == NULL)
	{
		return 0;
	}
	else
	{
		/*
		int ret_val = (int)Tcl_GetHashValue(hash_entry);
		int ret_key = (int)Tcl_GetHashKey(&hash_int, hash_entry);
	//	fprintf(stderr, "Got value:%d for key:%d\n", ret_val, ret_key);
*/
		return 1;
	}


}
static inline int ExistsInStrHash(const char* key)
{
	Tcl_HashEntry* hash_entry;
	hash_entry = Tcl_FindHashEntry(&hash_str, (const char*)key); 

	if(hash_entry == NULL)
	{
		return 0;
	}
	else
	{
		/*
		int ret_val = (int)Tcl_GetHashValue(hash_entry);
		const char* ret_key = Tcl_GetHashKey(&hash_str, hash_entry);	
//		fprintf(stderr, "Got value:%d for key:%s / origkeyaddr:%x tclkeyaddr:%x\n", ret_val, ret_key, key, ret_key);
	*/
		return 1;
	}

}

static inline int ExistsInStrHashWithLength(const char* key, size_t length)
{
	Tcl_HashEntry* hash_entry;
	hash_entry = Tcl_FindHashEntry(&hash_str, (const char*)key); 

	if(hash_entry == NULL)
	{
		return 0;
	}
	else
	{
		/*
		int ret_val = (int)Tcl_GetHashValue(hash_entry);
		const char* ret_key = Tcl_GetHashKey(&hash_str, hash_entry);	
//		fprintf(stderr, "Got value:%d for key:%s / origkeyaddr:%x tclkeyaddr:%x\n", ret_val, ret_key, key, ret_key);
	*/
		return 1;
	}

}

static inline void SetIntIntoHash(int key, int value)
{
	Tcl_HashEntry* hash_entry;
	int new_val;
	hash_entry = Tcl_FindHashEntry(&hash_int, (const char*)key);
	if(NULL == hash_entry)
	{
		fprintf(stderr, "Error: didn't find expected key in hash to set: %d\n", key);
		return; 
	}
	Tcl_SetHashValue(hash_entry, (ClientData)value);
}

static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
	Tcl_HashEntry* hash_entry;
	int new_val;
	hash_entry = Tcl_FindHashEntry(&hash_str, (const char*)key);
	if(NULL == hash_entry)
	{
		fprintf(stderr, "Error: didn't find expected key in hash to set: %s\n", key);
		return;
	}
	Tcl_SetHashValue(hash_entry, (ClientData)value);
}


#include "template.c"


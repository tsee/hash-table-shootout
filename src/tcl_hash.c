#include <Tcl/tcl.h>
	Tcl_HashTable hash_int; 
	Tcl_HashTable hash_str; 
#define SETUP \
	Tcl_InitHashTable(&hash_int, TCL_ONE_WORD_KEYS); \
	Tcl_InitHashTable(&hash_str, TCL_STRING_KEYS);
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

int ExistsInIntHash(int key)
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
int ExistsInStrHash(const char* key)
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
#include "template.c"


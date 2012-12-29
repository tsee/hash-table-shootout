#include <CoreFoundation/CoreFoundation.h>
CFMutableDictionaryRef dict = NULL;
CFMutableDictionaryRef str_dict = NULL;

Boolean intEqual(const void *ptr1, const void *ptr2) {
    return (int)ptr1 == (int)ptr2;
}
 
CFHashCode intHash(const void *ptr) {
    return (CFHashCode)((int)ptr);
}
 
CFStringRef intCopyDescription(const void *ptr) {
    return CFStringCreateWithFormat(NULL, NULL, CFSTR("%d"), (int)ptr);
}
 
#define SETUP(num_keys) do { \
	CFDictionaryKeyCallBacks intKeyCallBacks = {0, NULL, NULL, intCopyDescription, intEqual, intHash}; \
	CFDictionaryValueCallBacks intValueCallBacks = {0, NULL, NULL, intCopyDescription, intEqual}; \
	/* Bad: I'm creating two dictionaries with a pre-size. This will eat twice as much memory as it should. */ \
    dict = CFDictionaryCreateMutable(NULL, num_keys, &intKeyCallBacks, &intValueCallBacks); \
    str_dict = CFDictionaryCreateMutable(NULL, num_keys, &kCFTypeDictionaryKeyCallBacks, &intValueCallBacks); \
	} while(0)

#define INSERT_INT_INTO_HASH(key, value) do { \
		CFDictionaryAddValue(dict, (const void*)key, (const void*)value); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
		CFDictionaryRemoveValue(dict, (const void*)key); \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
		CFStringRef cfstr_key = CFStringCreateWithCString(NULL, key, kCFStringEncodingUTF8); \
		CFDictionaryAddValue(str_dict, cfstr_key, (const void*)value); \
		CFRelease(cfstr_key); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
		CFStringRef cfstr_key = CFStringCreateWithCString(NULL, key, kCFStringEncodingUTF8); \
		CFDictionaryRemoveValue(str_dict, cfstr_key); \
		CFRelease(cfstr_key); \
    } while(0)

static inline const char* InsertStrIntoHash(const char* key, int value)
{
	INSERT_STR_INTO_HASH(key, value);
	return key;
}

static inline int ExistsInIntHash(int key)
{
	return CFDictionaryContainsKey(dict, (const void*)key);
}

static inline int ExistsInStrHash(const char* key)
{
	CFStringRef cfstr_key = CFStringCreateWithCString(NULL, key, kCFStringEncodingUTF8);
	int ret_val = CFDictionaryContainsKey(str_dict, cfstr_key);
	CFRelease(cfstr_key);
	return ret_val;
}

static inline int ExistsInStrHashWithLength(const char* key, size_t length)
{
	return ExistsInStrHash(key);
}

static inline void SetIntIntoHash(int key, int value)
{
	CFDictionaryReplaceValue(dict, (const void*)key, (const void*)value);	
}

static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
	CFStringRef cfstr_key = CFStringCreateWithCString(NULL, key, kCFStringEncodingUTF8);		
	CFDictionaryReplaceValue(str_dict, cfstr_key, (const void*)value);
	CFRelease(cfstr_key);	
}


#include "template.c"

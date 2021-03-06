#include <inttypes.h>
#include <tr1/unordered_map>
typedef std::tr1::unordered_map<int64_t, int64_t> hash_t;
typedef std::tr1::unordered_map<const char *, int64_t> str_hash_t;
str_hash_t str_hash;
hash_t hash;
#define SETUP  
#define INSERT_INT_INTO_HASH(key, value) hash.insert(hash_t::value_type(key, value))
#define DELETE_INT_FROM_HASH(key) hash.erase(key);
#define INSERT_STR_INTO_HASH(key, value) str_hash.insert(str_hash_t::value_type(key, value))
#define DELETE_STR_FROM_HASH(key) str_hash.erase(key);
#define EXISTS_IN_STR_HASH(key) 

int ExistsInIntHash(int key)
{
		std::tr1::unordered_map<int64_t, int64_t>::const_iterator iter = hash.find((int64_t)key); 
		if ( iter == hash.end() ) 
		{ 
			return 0; 
		} 
		else 
		{ 
		//	fprintf(stderr, "found: %s, %d", iter->first, iter->second);
			return 1; 
		} 

}


int ExistsInStrHash(const char* key)
{
		std::tr1::unordered_map<const char *, int64_t>::const_iterator iter = str_hash.find(key); 
		if ( iter == str_hash.end() ) 
		{ 
			return 0; 
		} 
		else 
		{ 
		//	fprintf(stderr, "found: %s, %d", iter->first, iter->second);
			return 1; 
		} 

}

#include "template.c"

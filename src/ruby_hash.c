#include <ruby.h>
VALUE hash;
#define SETUP(num_keys) do { \
    ruby_init(); \
    hash = rb_hash_new(); \
	} while(0)

#define INSERT_INT_INTO_HASH(key, value) do { \
        VALUE rb_int_key = INT2NUM(key); /* leak */ \
        VALUE rb_int_value = INT2NUM(value); /* leak */ \
        rb_hash_aset(hash, rb_int_key, rb_int_value); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
        VALUE rb_int_key = INT2NUM(key); /* leak */ \
        rb_hash_delete(hash, rb_int_key); \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
        VALUE rb_str_key = rb_str_new2(key); /* leak */ \
        VALUE rb_int_value = INT2NUM(value); /* leak */ \
        rb_hash_aset(hash, rb_str_key, rb_int_value); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
        VALUE rb_str_key = rb_str_new2(key); /* leak */ \
        rb_hash_delete(hash, rb_str_key); \
    } while(0)

static inline const char* InsertStrIntoHash(const char* key, int value)
{
	INSERT_STR_INTO_HASH(key, value);
	return key;
}

static inline int ExistsInIntHash(int key)
{
	VALUE rb_int_key = INT2NUM(key); /* leak??? */
	VALUE ret_val = rb_hash_aref(hash, rb_int_key);
	
	if(ret_val != Qnil)
	{
		
//		fprintf(stderr, "found key: %d\n", key);
//		fprintf(stderr, " ret_val NUM2INT: %d\n", NUM2INT(ret_val));
		return 1;
	}
	else
	{
//		fprintf(stderr, "not found key: %d\n", key);
		return 0;
	}
}

static inline int ExistsInStrHash(const char* key)
{
	VALUE rb_str_key = rb_str_new2(key); /* leak??? */
		VALUE ret_val = rb_hash_aref(hash, rb_str_key);
	
	if(ret_val != Qnil)
	{
//		fprintf(stderr, "found key: %s", key);
//		fprintf(stderr, " ret_val NUM2INT: %d\n", NUM2INT(ret_val));

		
		return 1;
	}
	else
	{
//		fprintf(stderr, "not found key: %s", key);
		
		return 0;
	}
}

static inline int ExistsInStrHashWithLength(const char* key, size_t length)
{
	VALUE rb_str_key = rb_str_new2(key); /* leak??? */
		VALUE ret_val = rb_hash_aref(hash, rb_str_key);
	
	if(ret_val != Qnil)
	{
//		fprintf(stderr, "found key: %s", key);
//		fprintf(stderr, " ret_val NUM2INT: %d\n", NUM2INT(ret_val));

		
		return 1;
	}
	else
	{
//		fprintf(stderr, "not found key: %s", key);
		
		return 0;
	}
}

static inline void SetIntIntoHash(int key, int value)
{
	INSERT_INT_INTO_HASH(key, value);
}

static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
	INSERT_STR_INTO_HASH(key, value);
}



#include "template.c"

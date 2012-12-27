#include <EXTERN.h>
#include <perl.h>
HV* hash = NULL;
static PerlInterpreter *my_perl;
#define SETUP(num_keys) do { \
    PERL_SYS_INIT3(NULL,NULL,NULL); \
    /*PerlInterpreter *my_perl = perl_alloc();*/ \
    my_perl = perl_alloc(); \
    perl_construct(my_perl); \
    hash = newHV(); \
    SV* ival = newSViv(0); \
    SV* ikey = newSViv(0); \
    SV* skey = newSVpv("", 0); \
	} while(0)	
#define INSERT_INT_INTO_HASH(key, value) do { \
		SV* sv_key = newSViv(key); \
		SV* sv_val = newSViv(value); \
        /* sv_setiv(ikey, key); */ \
        /* SvREFCNT_inc(ival); */ \
	/*		fprintf(stderr, "insert %d, %d\n", key, value); */ \
/*        SvREFCNT_inc(sv_key); */ \
    /*    SvREFCNT_inc(sv_val); */ \
        hv_store_ent(hash, sv_key, sv_val, 0); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
       /* sv_setiv(ikey, key); */ \
       /* SvREFCNT_dec(ival); */ \
        /* hv_delete_ent(hash, ikey, G_DISCARD, 0); */ \
		SV* sv_key = newSViv(key); \
		SV* sv = hv_delete_ent(hash, sv_key, 0, 0); \
		if(NULL == sv) \
		{ \
		/*	fprintf(stderr, "sv is null\n"); */ \
		} \
		else \
		{ \
		/*	fprintf(stderr, "sv is not null\n"); */ \
			SvREFCNT_dec(sv); \
		} \
		SvREFCNT_dec(sv_key); \
/*		hv_delete(hash, new_string_from_integer(key), strlen(new_string_from_integer(key)), 0); */ \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
      /*  sv_setpv(skey, key);  */ \
       /* SvREFCNT_inc(ival); */ \
       /* hv_store_ent(hash, skey, ival, 0); */ \
		SV* sv_val = newSViv(value); \
		hv_store(hash, key, strlen(key), sv_val, 0); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
       /* sv_setpv(skey, key); */ \
       /* SvREFCNT_dec(ival); */ \
        /* hv_delete_ent(hash, skey, G_DISCARD, 0); */ \
		SV* sv = hv_delete(hash, key, strlen(key), 0); \
		if(NULL == sv) \
		{ \
		/*	fprintf(stderr, "sv is null\n"); */ \
		} \
		else \
		{ \
		/*	fprintf(stderr, "sv is not null\n"); */ \
			SvREFCNT_dec(sv); \
		} \
    } while(0)

static inline const char* InsertStrIntoHash(const char* key, int value)
{
	INSERT_STR_INTO_HASH(key, value);
	return key;
}

static inline int ExistsInIntHash(int key)
{
	int ret_val;	
	SV* sv_key = newSViv(key);
	ret_val = hv_exists_ent(hash, sv_key, 0);
	SvREFCNT_dec(sv_key);
	return ret_val;
}
static inline int ExistsInStrHash(const char* key)
{
	return hv_exists(hash, key, strlen(key));

}

static inline int ExistsInStrHashWithLength(const char* key, size_t length)
{
	return hv_exists(hash, key, length);

}

static inline void SetIntIntoHash(int key, int value)
{
	SV* sv_key = newSViv(key);
	SV* sv_val = newSViv(value);
	hv_store_ent(hash, sv_key, sv_val, 0);
}

static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
	SV* sv_val = newSViv(value);
	hv_store(hash, key, length, sv_val, 0);
}



#include "template.c"


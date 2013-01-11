#define PERL_NO_GET_CONTEXT
#include <EXTERN.h>
#include <perl.h>
#define PERL_CORE
#include "XSUB.h"
#undef PERL_CORE
HV* hash = NULL;
static PerlInterpreter *my_perl;
SV *int_key_for_exists;
#define SETUP(num_keys) do { \
       PERL_SYS_INIT3(NULL,NULL,NULL); \
       my_perl = perl_alloc(); \
       perl_construct(my_perl); \
       hash = newHV(); \
       hv_ksplit((HV *)hash, num_keys); \
       int_key_for_exists = newSViv(0); \
    } while(0)
#define INSERT_INT_INTO_HASH(key, value) do { \
        SV* sv_key = newSViv(key); \
        hv_store_ent(hash, sv_key, newSViv(value), 0); \
        SvREFCNT_dec(sv_key); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
        SV* sv_key = newSViv(key); \
        SV* sv = hv_delete_ent(hash, sv_key, 0, 0); \
        SvREFCNT_dec(sv); \
        SvREFCNT_dec(sv_key); \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
        SV* sv_val = newSViv(value); \
        hv_store(hash, key, strlen(key), sv_val, 0); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
        SV* sv = hv_delete(hash, key, strlen(key), 0); \
        SvREFCNT_dec(sv); \
    } while(0)

static inline const char* InsertStrIntoHash(const char* key, int value)
{
    hv_store(hash, key, strlen(key), newSViv(value), 0);
    return key;
}

static inline int ExistsInIntHash(int key)
{
    sv_setiv(int_key_for_exists, key);
    return hv_exists_ent(hash, int_key_for_exists, 0);
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
    hv_store_ent(hash, sv_key, newSViv(value), 0);
}

static inline void SetStringIntoHash(const char* key, int value, size_t length)
{
    hv_store(hash, key, length, newSViv(value), 0);
}



#include "template.c"


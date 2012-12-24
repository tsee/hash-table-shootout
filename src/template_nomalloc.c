/* I don't think the original test is 'fair' in the sense that it malloc's the strings and leaks. 
 * The puts additional memory pressure on libraries that make copies of their own strings.
 * It is also not clear if memory ownership needs to be part of the rules for the test.
 * (For example, should STL unordered_map use std::string instead of char* to take ownership.)
 * This modifies the test to not malloc the memory. However, this may cause certain tests to break.
 */

#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

double get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

char * new_string_from_integer(int num)
{
    int ndigits = num == 0 ? 1 : (int)log10(num) + 1;
    char * str = (char *)malloc(ndigits + 1);
    sprintf(str, "%d", num);
    return str;
}


#define CONVERT_INT_AND_INSERT_STR_INTO_HASH(key, value) do { \
    int ndigits = key == 0 ? 1 : (int)log10(key) + 1; \
	int buffer_size = ndigits+1; \
	char str[buffer_size]; \
    snprintf(str, buffer_size, "%d", key); \
	INSERT_STR_INTO_HASH(str, value); \
	} while(0)


#define CONVERT_INT_AND_DELETE_STR_FROM_HASH(key) do { \
    int ndigits = key == 0 ? 1 : (int)log10(key) + 1; \
	int buffer_size = ndigits+1; \
	char str[buffer_size]; \
    snprintf(str, buffer_size, "%d", key); \
	DELETE_STR_FROM_HASH(str); \
	} while(0)

int main(int argc, char ** argv)
{
    int num_keys = atoi(argv[1]);
    int i, value = 0;

    if(argc <= 2)
        return 1;

    SETUP

    double before = get_time();

    if(!strcmp(argv[2], "sequential"))
    {
        for(i = 0; i < num_keys; i++)
            INSERT_INT_INTO_HASH(i, value);
    }

    else if(!strcmp(argv[2], "random"))
    {
        srandom(1); // for a fair/deterministic comparison
        for(i = 0; i < num_keys; i++)
            INSERT_INT_INTO_HASH((int)random(), value);
    }

    else if(!strcmp(argv[2], "delete"))
    {
        for(i = 0; i < num_keys; i++)
            INSERT_INT_INTO_HASH(i, value);
        before = get_time();
        for(i = 0; i < num_keys; i++)
        //for(i = num_keys; i > 0; i--)
            DELETE_INT_FROM_HASH(i-1);
    }

    else if(!strcmp(argv[2], "sequentialstring"))
    {
        for(i = 0; i < num_keys; i++)
		{
            //INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
            CONVERT_INT_AND_INSERT_STR_INTO_HASH(i, value);
		}
    }

    else if(!strcmp(argv[2], "randomstring"))
    {
        srandom(1); // for a fair/deterministic comparison
        for(i = 0; i < num_keys; i++)
		{
            // INSERT_STR_INTO_HASH(new_string_from_integer((int)random()), value);
            CONVERT_INT_AND_INSERT_STR_INTO_HASH(i, value);			
		}
    }

    else if(!strcmp(argv[2], "deletestring"))
    {
        for(i = 0; i < num_keys; i++)
		{
//			INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
            CONVERT_INT_AND_INSERT_STR_INTO_HASH(i, value);
		}
        before = get_time();
        for(i = 0; i < num_keys; i++)
		{
//            DELETE_STR_FROM_HASH(new_string_from_integer(i));
            CONVERT_INT_AND_DELETE_STR_FROM_HASH(i);

		}
    }

    double after = get_time();
    printf("%f\n", after-before);
    fflush(stdout);
    sleep(1000000);
}

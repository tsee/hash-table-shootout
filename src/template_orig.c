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

const char * new_string_from_integer(int num)
{
    int ndigits = num == 0 ? 1 : (int)log10(num) + 1;
    char * str = (char *)malloc(ndigits + 1);
    sprintf(str, "%d", num);
    return str;
}

// http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
void gen_random_string(char *s, const int len) {
    static const char alphanum[] =
	"0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";
	
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
	
    s[len] = 0;
}

int main(int argc, char ** argv)
{
    int num_keys = atoi(argv[1]);
    int i, value = 0;
//	fprintf(stderr, "num_keys = %d\n", num_keys);

    if(argc <= 2)
        return 1;

    SETUP

    double before = get_time();

    if(!strcmp(argv[2], "sequential"))
    {
        for(i = 0; i < num_keys; i++)
		{
            INSERT_INT_INTO_HASH(i, value);
		}
	//	fprintf(stderr, "verifying insert\n");
	    for(i = 0; i < num_keys; i++)
		{
            if( 0 == ExistsInIntHash(i+1) )
			{
				fprintf(stderr, "Assertion failure: Did not find int key: %d\n", i);
			}
			else
			{
			fprintf(stderr, "found int key: %d\n", i);
			}
		}

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
            DELETE_INT_FROM_HASH(i-1); // test one bad key
    }

    else if(!strcmp(argv[2], "sequentialstring"))
    {
		/*
		for(i = 0; i < num_keys; i++)
		{
            INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
		}
		*/
        for(i = 0; i < num_keys; i++)
		{
			const char* new_str = new_string_from_integer(i);
			fprintf(stderr, "inserting string / addr: %s / %x\n", new_str, new_str);
            INSERT_STR_INTO_HASH(new_str, i);
			if( 0 == ExistsInStrHash(new_str) )
			{
				fprintf(stderr, "Assertion failure: Did not find string key: %d\n", i);
			}
			else
			{
				fprintf(stderr, "found string key: %d\n", i);
			}
		}
		fprintf(stderr, "testing existence with string key with different address\n");
        for(i = 0; i < num_keys; i++)
		{
            if( 0 == ExistsInStrHash(new_string_from_integer(i+1)) )
			{
				fprintf(stderr, "Assertion failure: Did not find string key: %d\n", i+1);
			}
			else
			{
				fprintf(stderr, "found string key: %d\n", i+1);
			}
		}

    }

    else if(!strcmp(argv[2], "randomstring"))
    {
        srandom(1); // for a fair/deterministic comparison


        for(i = 0; i < num_keys; i++)
		{

            INSERT_STR_INTO_HASH(new_string_from_integer((int)random()), value);
		}
    }

    else if(!strcmp(argv[2], "deletestring"))
    {
        for(i = 0; i < num_keys; i++)
            INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
        before = get_time();
        for(i = 0; i < num_keys; i++)
            DELETE_STR_FROM_HASH(new_string_from_integer(i));
    }

    double after = get_time();
    printf("%f\n", after-before);
    fflush(stdout);
    sleep(1000000);
}

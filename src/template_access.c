/* I don't think the original test is 'fair' in the sense that it malloc's the strings and leaks. 
 * The puts additional memory pressure on libraries that make copies of their own strings.
 * It is also not clear if memory ownership needs to be part of the rules for the test.
 * (For example, should STL unordered_map use std::string instead of char* to take ownership.)
 * This modifies the test to not malloc the memory. However, this may cause certain tests to break.
 */

/* Original benchmark misses the most common/fundemental operations to a hash table: accessing.
 * Insert and deletion are not nearly as important.
 * The access test should include:
 * - Getting a value that exists in the hash
 * - Trying to get a value that doesn't exist in the hash.
 * - Changing a value that already exists in the hash.
 *
 * Additionally, I would like to see a test that compares using an external string pointer vs. using Lua's internalized pointer.
 * Also of potential interest would be iteration performance (though it would require me to understand how to iterate well in all the libraries).
 */

/* Set test needs to cover:
 * - Changing a value that already exists in the hash.
 * This includes several variations
 * - Integer
 * - String
 *   	- Basic
 * 		- Use string length
 * 		- Use string internalization
 * 		- Use string internalization and string length
 * Another interesting string test would be as a value. In Lua, string internalization might
 * make a big difference depending if the value is already internalized in Lua or if it is a new string value.
 */
 

#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

/* Some libraries provide APIs that take string lengths, presumably as an optimization.
 * std::string (C++ STL), Perl, and Lua seem to be among these.
 * Also, Lua returns the internalized string which presumably allows other optimizations.
 */
typedef struct StringContainer
{
	size_t stringLength;
	const char* keyOriginal;
	const char* keyInternalized;
} StringContainer;

int* g_intKeyArray = NULL;
int* g_intBadKeyArray = NULL;
StringContainer* g_charKeyArray = NULL;
// array of bad keys
StringContainer* g_charBadKeyArray = NULL;

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

// http://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range-c
/* Would like a semi-open interval [min, max) */
int random_in_range (unsigned int min, unsigned int max)
{
//  int base_random = random(); /* in [0, RAND_MAX] */
  int base_random = rand(); /* in [0, RAND_MAX] */
  if (RAND_MAX == base_random) return random_in_range(min, max);
  /* now guaranteed to be in [0, RAND_MAX) */
  int range       = max - min,
      remainder   = RAND_MAX % range,
      bucket      = RAND_MAX / range;
  /* There are range buckets, plus one smaller interval
     within remainder of RAND_MAX */
  if (base_random < RAND_MAX - remainder) {
    return min + base_random/bucket;
  } else {
    return random_in_range (min, max);
  }
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


void InitInts(int num_keys)
{
	int i;
	
	g_intKeyArray = (int*)calloc(num_keys,sizeof(int));
	g_intBadKeyArray = (int*)calloc(num_keys,sizeof(int));
	// Create the key strings and save them so we can refer to them later.
	size_t current_key_index = 0;
	size_t current_badkey_index = 0;
	// multiply by 2 because I'm creating a second set of bad keys to go with the good keys.
	for(i = 0; i < num_keys*2; i++)
	{
		int key;
		// Breaking into four cases just to shuffle up the ranges a little more.
		// the 1st and 3rd set are good, the 2nd and 4th set are bad.
		int which_case = i % 4;
		int should_insert;
		switch(which_case)
		{
			case 0:
			{
				key = random_in_range(0,INT_MAX/4);
				should_insert = 1;
				break;
			}
			case 1:
			{
				key = random_in_range(INT_MAX/4+1,INT_MAX/4*2); 
				should_insert = 0;
				break;
			}
			case 2:
			{
				key = random_in_range(INT_MAX/4*2+1,INT_MAX/4*3); 
				should_insert = 1;
				break;
			}
			case 3:
			{
				key = random_in_range(INT_MAX/4*3+1,INT_MAX); 
				should_insert = 0;
				break;
			}

		}
		if(should_insert)
		{
			g_intKeyArray[current_key_index] = key; // creates new copy of the string to store
			current_key_index++;
		}
		else
		{
			g_intBadKeyArray[current_badkey_index] = key; // creates new copy of the string to store
			current_badkey_index++;
		}

	}


	// Now insert them in the hash
	for(i = 0; i < num_keys; i++)
	{
		// I don't really care what the value is.
		INSERT_INT_INTO_HASH(g_intKeyArray[i], 1);
	}
}

void InitStrings(int num_keys)
{
	int i;
	g_charKeyArray = (StringContainer*)malloc(num_keys*sizeof(StringContainer));
	g_charBadKeyArray = (StringContainer*)malloc(num_keys*sizeof(StringContainer));

	// Create the key strings and save them so we can refer to them later.
	size_t current_key_index = 0;
	size_t current_badkey_index = 0;
	// multiply by 2 because I'm creating a second set of bad keys to go with the good keys.
	for(i = 0; i < num_keys*2; i++)
	{
		int key;
		// Breaking into four cases just to shuffle up the ranges a little more.
		// the 1st and 3rd set are good, the 2nd and 4th set are bad.
		int which_case = i % 4;
		int should_insert;
		switch(which_case)
		{
			case 0:
			{
				key = random_in_range(0,INT_MAX/4);
				should_insert = 1;
				break;
			}
			case 1:
			{
				key = random_in_range(INT_MAX/4+1,INT_MAX/4*2); 
				should_insert = 0;
				break;
			}
			case 2:
			{
				key = random_in_range(INT_MAX/4*2+1,INT_MAX/4*3); 
				should_insert = 1;
				break;
			}
			case 3:
			{
				key = random_in_range(INT_MAX/4*3+1,INT_MAX); 
				should_insert = 0;
				break;
			}
			default:
			{
				fprintf(stderr, "Unexpected case\n");
				break;
			}

		}

		int ndigits = key == 0 ? 1 : (int)log10(key) + 1;
		int buffer_size = ndigits+1;
		char str[buffer_size];
		snprintf(str, buffer_size, "%d", key);

//		fprintf(stderr, "string is %s\n", str);
		if(should_insert)
		{
			g_charKeyArray[current_key_index].keyOriginal = strdup(str); // creates new copy of the string to store
			g_charKeyArray[current_key_index].stringLength = strlen(str);
			current_key_index++;
		}
		else
		{
			g_charBadKeyArray[current_badkey_index].keyOriginal = strdup(str); // creates new copy of the string to store
			g_charBadKeyArray[current_badkey_index].stringLength = strlen(str);
			current_badkey_index++;
		}

	}
//	fprintf(stderr, "Done key gen, now insert\n");
	// Now insert them in the hash
	for(i = 0; i < num_keys; i++)
	{
		// I don't really care what the value is.
		// Save the return pointer. For Lua, this is the internalized pointer which may yield some benefits.
		// A better way of doing this would be to free the original string and just reuse the old pointer.
		// But since none of the other libraries do anything like this, I don't want to make the code too difficult to manage.
		g_charKeyArray[i].keyInternalized = InsertStrIntoHash(g_charKeyArray[i].keyOriginal, 1);
	}
}

#define NUM_ITERATIONS_MULTIPLE 1

int main(int argc, char ** argv)
{
    int num_keys = atoi(argv[1]);
    int i, value = 0;

    if(argc <= 2)
        return 1;

    SETUP(num_keys);



	//srandom(1); // for a fair/deterministic comparison
	srand(1); // for a fair/deterministic comparison

    if(!strcmp(argv[2], "randomgetgood"))
    {
		InitInts(num_keys);
    }
    else if(!strcmp(argv[2], "randomstringgetgood"))
    {
//		fprintf(stderr, "InitStrings\n");
		InitStrings(num_keys);
//		fprintf(stderr, "end InitStrings\n");
    }
    else if(!strcmp(argv[2], "randomstringgetgoodinternalized"))
    {
		InitStrings(num_keys);		
	}
	else if(!strcmp(argv[2], "randomgetbad"))
    {
		InitInts(num_keys);		
	}
	else if(!strcmp(argv[2], "randomstringgetbad"))
    {
		InitStrings(num_keys);		
	}
	else if(!strcmp(argv[2], "randomstringlengthgetgood"))
    {
		InitStrings(num_keys);		
	}
	else if(!strcmp(argv[2], "randomstringlengthgetgoodinternalized"))
    {
		InitStrings(num_keys);		
	}
	else if(!strcmp(argv[2], "randomstringlengthgetbad"))
    {
		InitStrings(num_keys);		
	}
    else if(!strcmp(argv[2], "randomset"))
	{
		InitInts(num_keys);		
	}
    else if(!strcmp(argv[2], "randomstringsetbest"))
	{
		InitStrings(num_keys);		
	}

	else
    {
		fprintf(stderr, "Test name not implemented. Bailing...\n");
		return 1;
	}
    double before = get_time();


	if(!strcmp(argv[2], "randomgetgood"))
    {
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			int key = g_intKeyArray[random_index];

			int exists = ExistsInIntHash(key);
			if(!exists)
			{
				fprintf(stderr, "Warning: expected to find value for key: %d\n", key);
			}
		}
    }
    else if(!strcmp(argv[2], "randomstringgetgood"))
    {
//		fprintf(stderr, "ExistsInStrHash\n");
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			const char* key = g_charKeyArray[random_index].keyOriginal;

			int exists = ExistsInStrHash(key);
			if(!exists)
			{
				fprintf(stderr, "Warning: expected to find value for key: %s\n", key);
			}
		}
    }
    else if(!strcmp(argv[2], "randomstringgetgoodinternalized"))
    {
//		fprintf(stderr, "ExistsInStrHash\n");
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			const char* key = g_charKeyArray[random_index].keyInternalized;

			int exists = ExistsInStrHash(key);
			if(!exists)
			{
				fprintf(stderr, "Warning: expected to find value for key: %s\n", key);
			}
		}
    }
    else if(!strcmp(argv[2], "randomstringlengthgetgood"))
    {
//		fprintf(stderr, "ExistsInStrHash\n");
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			const char* key = g_charKeyArray[random_index].keyOriginal;
			size_t length = g_charKeyArray[random_index].stringLength;

			int exists = ExistsInStrHashWithLength(key, length);
			if(!exists)
			{
				fprintf(stderr, "Warning: expected to find value for key: %s\n", key);
			}
		}
    }
    else if(!strcmp(argv[2], "randomstringlengthgetgoodinternalized"))
    {
//		fprintf(stderr, "ExistsInStrHash\n");
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			const char* key = g_charKeyArray[random_index].keyInternalized;
			size_t length = g_charKeyArray[random_index].stringLength;

			int exists = ExistsInStrHashWithLength(key, length);
			if(!exists)
			{
				fprintf(stderr, "Warning: expected to find value for key: %s\n", key);
			}
		}
    }

	else if(!strcmp(argv[2], "randomgetbad"))
    {
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			int key = g_intBadKeyArray[random_index];

			int exists = ExistsInIntHash(key);
			if(exists)
			{
				fprintf(stderr, "Warning: didn't expect to find value for key: %d\n", key);
			}
		}
    }
    else if(!strcmp(argv[2], "randomstringgetbad"))
    {
//		fprintf(stderr, "ExistsInStrHash\n");
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			const char* key = g_charBadKeyArray[random_index].keyOriginal;

			int exists = ExistsInStrHash(key);
			if(exists)
			{
				fprintf(stderr, "Warning: didn't expect to find value for key: %s\n", key);
			}
		}
    }
    else if(!strcmp(argv[2], "randomstringlengthgetbad"))
    {
//		fprintf(stderr, "ExistsInStrHash\n");
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			const char* key = g_charBadKeyArray[random_index].keyOriginal;
			size_t length = g_charBadKeyArray[random_index].stringLength;

			int exists = ExistsInStrHashWithLength(key, length);
			if(exists)
			{
				fprintf(stderr, "Warning: didn't expect to find value for key: %s\n", key);
			}
		}
    }


    else if(!strcmp(argv[2], "randomset"))
	{
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			int key = g_intKeyArray[random_index];

			SetIntIntoHash(key, i);
		}
	}
    else if(!strcmp(argv[2], "randomstringsetbest"))
    {
//		fprintf(stderr, "ExistsInStrHash\n");
		for(i = 0; i < num_keys * NUM_ITERATIONS_MULTIPLE; i++)
		{
			int random_index = random_in_range(0, num_keys-1);
			const char* key = g_charKeyArray[random_index].keyInternalized;
			size_t length = g_charKeyArray[random_index].stringLength;

			SetStringIntoHash(key, i, length);

		}
    }




    double after = get_time();
    printf("%f\n", after-before);
    fflush(stdout);
    sleep(1000000);
}

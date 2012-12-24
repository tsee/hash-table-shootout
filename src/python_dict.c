#include <Python.h>
typedef PyObject * hash_t;
hash_t hash = NULL;
#define SETUP \
    Py_Initialize(); \
    hash = PyDict_New(); \
    PyObject * py_int_value = PyInt_FromLong(0);
#define INSERT_INT_INTO_HASH(key, value) do { \
        PyObject * py_int_key = PyInt_FromLong(key); /* leak */ \
        PyDict_SetItem(hash, py_int_key, py_int_value); \
        Py_DECREF(py_int_key); \
    } while(0)
#define DELETE_INT_FROM_HASH(key) do { \
        PyObject * py_int_key = PyInt_FromLong(key); /* leak */ \
        int error = PyDict_DelItem(hash, py_int_key); \
	    if (error != 0) { \
		fprintf(stderr, "item not found for key %d\n", key); \
			if (PyErr_ExceptionMatches(PyExc_KeyError)) \
			{ \
		        PyErr_Clear(); \
			} \
		} \
        Py_DECREF(py_int_key); \
    } while(0)
#define INSERT_STR_INTO_HASH(key, value) do { \
        PyDict_SetItemString(hash, key, py_int_value); \
    } while(0)
#define DELETE_STR_FROM_HASH(key) do { \
        PyDict_DelItemString(hash, key); \
    } while(0)


int ExistsInIntHash(int key)
{
	PyObject * py_int_key = PyInt_FromLong(key); /* leak */
//	PyObject* value = PyDict_GetItem(hash, py_int_key);
	int value = PyDict_Contains(hash, py_int_key);
	Py_DECREF(py_int_key);	
//	if(value == NULL)
	if(value == 0)
	{
	//	fprintf(stderr, "item not found for key %d\n", key);
		return 0;
	}
	else
	{
//		fprintf(stderr, "item foun for key %d\n", key);
		return 1;		
	}

}
int ExistsInStrHash(const char* key)
{
	PyObject* value = PyDict_GetItemString(hash, key);
	if(value == NULL)
	{
//		fprintf(stderr, "item not found for key %s\n", key);
		return 0;
	}
	else
	{
//		fprintf(stderr, "item foun for key %s\n", key);
		return 1;		
	}
}


#include "template.c"

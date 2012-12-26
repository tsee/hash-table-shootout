#!/bin/sh
#python bench_get_int.py
#mv output output_get_int

#python bench_get_string.py
#mv output output_get_string

#python bench_get_stringinternalized.py
#mv output output_get_stringinternalized

python bench_get_stringinternalizedLuaonly.py
mv output output_get_stringinternalized_luaonly

python bench_get_bad.py
mv output output_get_bad

python bench_get_string_bad.py
mv output output_get_string_bad



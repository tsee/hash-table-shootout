all: build/glib_hash_table build/stl_unordered_map build/boost_unordered_map build/google_sparse_hash_map build/google_dense_hash_map build/qt_qhash build/python_dict build/ruby_hash

build/glib_hash_table: src/glib_hash_table.c Makefile src/template.c
	gcc -ggdb -O3 -lm `pkg-config --cflags --libs glib-2.0` src/glib_hash_table.c -o build/glib_hash_table

build/stl_unordered_map: src/stl_unordered_map.cc Makefile src/template.c
#	g++ -O3 -lm src/stl_unordered_map.cc -o build/stl_unordered_map -std=c++0x
# 	clang++ -O3  src/stl_unordered_map.cc -o build/stl_unordered_map 
#	clang++ -O3 src/stl_unordered_map_string.cc -o build/stl_unordered_map_string 

build/boost_unordered_map: src/boost_unordered_map.cc Makefile src/template.c
	g++ -O3 -lm src/boost_unordered_map.cc -o build/boost_unordered_map

build/google_sparse_hash_map: src/google_sparse_hash_map.cc Makefile src/template.c
	g++ -O3 -lm src/google_sparse_hash_map.cc -o build/google_sparse_hash_map

build/google_dense_hash_map: src/google_dense_hash_map.cc Makefile src/template.c
	g++ -O3 -lm src/google_dense_hash_map.cc -o build/google_dense_hash_map

build/qt_qhash: src/qt_qhash.cc Makefile src/template.c
	g++ -O3 -lm `pkg-config --cflags --libs QtCore` src/qt_qhash.cc -o build/qt_qhash

build/python_dict: src/python_dict.c Makefile src/template.c
	gcc -O3 -lm -I/usr/include/python2.6 -lpython2.6 src/python_dict.c -o build/python_dict
#	clang -O3  -I/System/Library/Frameworks/Python.framework/Headers src/python_dict.c -o build/python_dict -framework Python

build/ruby_hash: src/ruby_hash.c Makefile src/template.c
#	gcc -O3 -lm -I/usr/include/ruby-1.9.0 -I /usr/include/ruby-1.9.0/x86_64-linux -lruby1.9 src/ruby_hash.c -o build/ruby_hash
	clang -O3 -I/System/Library/Frameworks/Ruby.framework/Headers -framework Ruby src/ruby_hash.c -o build/ruby_hash

build/perl_hash: src/perl_hash.c Makefile src/template.c
	gcc -O3 -lm `perl -MExtUtils::Embed -e ccopts` src/perl_hash.c -o build/perl_hash `perl -MExtUtils::Embed -e ldopts` 
#	clang  -O3 -lm `perl -MExtUtils::Embed -e ccopts` src/perl_hash.c -o build/perl_hash `perl -MExtUtils::Embed -e ldopts` 

build/LuaHashMap: src/LuaHashMap.c Makefile src/template.c
#	gcc -O3 -I/usr/local/include/lua -ltcl src/tcl_hash.c -o build/tcl_hash
	clang -O3 -framework Tcl src/tcl_hash.c -o build/tcl_hash
	

build/LuaHashMap: src/LuaHashMap.c Makefile src/template.c
	gcc -O3 -I/usr/local/include/lua -lLuaHashMap51 src/LuaHashMap.c -o build/LuaHashMap
#	clang -O3 -I/usr/local/include -I/Library/Frameworks/lua.framework/Headers -lLuaHashMap -framework lua src/LuaHashMap.c -o build/LuaHashMap
#	clang -O3 -I/usr/local/include -I/Library/Frameworks/lua.framework/Versions/5.1/Headers/ -lLuaHashMap51 src/LuaHashMap.c -o build/LuaHashMap51
#	clang -O3 -I/usr/local/include -I/Library/Frameworks/lua.framework/Versions/5.2/Headers/ -lLuaHashMap52 src/LuaHashMap.c -o build/LuaHashMap52
#	clang -O3 -I/usr/local/include -I/usr/local/include/luajit-2.0 -lLuaHashMapJIT -lluajit-51 src/LuaHashMap.c -o build/LuaHashMapJIT -pagezero_size 10000 -image_base 100000000
#
# clang -O3 -I/Library/Frameworks/lua.framework/Versions/5.2/Headers/ -I/Users/ewing/Source/HG/LuaHashMapShared /Users/ewing/Source/HG/LuaHashMapShared/LuaHashMap.c src/LuaHashMap.c -framework lua -o build/LuaHashMap52
#
#	clang -O3 -I/usr/local/include/lua52 -lLuaHashMap52 -llua52 src/LuaHashMap.c -o build/LuaHashMap52
#	clang -O3 -I/usr/local/include/lua51 -lLuaHashMap51 -llua51 src/LuaHashMap.c -o build/LuaHashMap51


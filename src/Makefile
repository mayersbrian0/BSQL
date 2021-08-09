BSQL: database.o arg_buffer.o compiler.o
	clang database.o arg_buffer.o compiler.o -o BSQL

database.o: database.c
	clang -c database.c 

arg_buffer.o: arg_buffer.c arg_buffer.h
	clang -c arg_buffer.c

compiler.o: compiler.c compiler.h
	clang -c compiler.c

clean: 
	rm *.o BSQL

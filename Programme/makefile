all:demo

myfree.o: myfree.c myfree.h
	gcc -c myfree.c

allocate.o: allocate.c allocate.h
	gcc -c allocate.c

initializer.o: initializer.c initializer.h
	gcc -c initializer.c

demo.o: demo.c myfree.h allocate.h
	gcc -c demo.c

demo: demo.o myfree.o allocate.o initializer.o
	gcc demo.o myfree.o allocate.o initializer.o -o demo

test.o: test.c test.h
	gcc -c test.c

test: test.o myfree.o allocate.o initializer.o
	gcc test.o myfree.o allocate.o initializer.o -o test
	
doc:
	@doxygen ./Doxyfile

clean:
	rm -f myfree.o allocate.o initializer.o demo.o demo test.o test
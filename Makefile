CFLAGS=-Wall -g -Ideps/yodawg/src

yodawgmodule.o: yodawg.o
	$(CC) $(CFLAGS) -c src/yodawgmodule.c -o build/yodawgmodule.o build/yodawg.o

yodawg.o:
	$(CC) $(CFLAGS) -c deps/yodawg/src/yodawg.c -o build/yodawg.o

clean:
	rm -rf build/*

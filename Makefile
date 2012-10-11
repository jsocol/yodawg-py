CFLAGS=-Wall -g -Ideps/yodawg/src -I/usr/include/python2.7

all: yodawgmodule.o

yodawgmodule.o: yodawg.o
	$(CC) $(CFLAGS) -c src/yodawgmodule.c -o build/yodawgmodule.o

yodawg.o:
	$(CC) $(CFLAGS) -c deps/yodawg/src/yodawg.c -o build/yodawg.o

install: clean
	python setup.py clean
	python setup.py build
	python setup.py install

uninstall:
	pip uninstall -yq yodawg

clean:
	rm -rf build/*

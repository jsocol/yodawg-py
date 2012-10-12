CFLAGS=-Wall -g -Ideps/yodawg/src -I/usr/include/python2.7

all: dawgs.o

dawgs.o: yodawg.o
	$(CC) $(CFLAGS) -c src/dawgs.c -o build/dawgs.o

yodawg.o:
	$(CC) $(CFLAGS) -c deps/yodawg/src/yodawg.c -o build/yodawg.o

install: uninstall clean
	python setup.py clean
	python setup.py build
	python setup.py install

uninstall:
	pip uninstall -yq yodawg

upload:
	python setup.py sdist upload

clean:
	rm -rf build/*
	rm -rf dist/*

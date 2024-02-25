PY=python3

all: lib

lib:
	cd ./clib && $(PY) setup.py build_ext -i

clean:
	rm -rf ./clib/build  
	rm -rf ./clib/*.so
	rm -rf *.so

.PHONY: all clean
PY=python3

all: lib run

lib:
	cd ./clib && $(PY) setup.py build_ext -i

run:
	$(PY) testing.py

venv:
	$(info $(PY) -m venv myenv)
	$(info source myenv/bin/activate)
	$(info pip3 install -r requirements.txt)

clean:
	rm -rf ./clib/build  
	rm -rf ./clib/*.so
	rm -rf *.so

.PHONY: all clean
import pybind11
from setuptools import setup, Extension

extension_mod = Extension('matrix_lib',
                          sources=['plusmatrix.cc', 'main.cc'],
                          language="c++",
                          include_dirs=[pybind11.get_include()],
                          extra_compile_args=["-std=c++17",'-I/usr/local/Cellar/python@3.10/3.10.2/Frameworks/Python.framework/Versions/3.10/include/python3.10']
                          )

setup(name='matrix_lib',
      version='1.0',
      author='Saraeva Kristina',
      description='Matrix extension',
      ext_modules=[extension_mod])
# SPEED TEST

## Description

A Python3 that binds a C++ matrix library with pybind11, so that you can use it to see which is faster:
_numpy_ or _cplusplus_. 
The programm compares:
- matrix multiplication
- multiplication by a number (a random float)
- matrix addition
- matrix transposing
- determinant

## How to use

You give the program the size of the matrix (it is square to allow all operations).
Then you give the number of iterations.
... and see the result which methods were faster.
What for? Just for fun. C++ is not always faster. It depends on the size and iterations. Moreover, you can bet with your friends on the result.

### Dependencies

- Python3
- gcc

### Installing

1. Clone this repository to your local machine.
2. Create the environment, activate it and install the requirements (`make venv` will show you the commands)
3. Then run `make`, give the size of the matrix and number of iterations.

## Author

[Kristina Saraeva](https://github.com/KristinaSaraeva)


© 2024 KristinaSaraeva

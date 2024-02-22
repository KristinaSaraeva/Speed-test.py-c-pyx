import ctypes
import numpy as np
import timeit

import random

def generate_random_matrix(rows, cols):
    return [[random.uniform(0.0, 1.0) for _ in range(cols)] for _ in range(rows)]

def create_matrix(rows, cols):
    return np.random.rand(rows, cols)


def mul_matrix_speed(matrix_a, matrix_b):
    py = timeit.timeit("np.matmul(matrix_a, matrix_b)", setup="import numpy as np",globals=globals(), number=100)
    print("Python: ", py)

def mul_matrix_number_speed(matrix_a, number):
    py = timeit.timeit("np.multiply(matrix_a, number)", setup="import numpy as np",globals=globals(), number=100)
    print("Python: ", py)

def sum_matrix_speed(matrix_a, matrix_b):
    py = timeit.timeit("np.add(matrix_a, matrix_b)", setup="import numpy as np",globals=globals(), number=100)
    print("Python: ", py)




if __name__ == "__main__":
    rows = 10
    cols = 10
    matrix_a = create_matrix(rows, cols)
    matrix_b = create_matrix(rows, cols)
    mul_matrix_speed(matrix_a, matrix_b)
    sum_matrix_speed(matrix_a, matrix_b)
    number = 2.0
    mul_matrix_number_speed(matrix_a, number)



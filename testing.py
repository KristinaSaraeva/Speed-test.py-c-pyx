import numpy as np
import timeit
import random
from clib import matrix_lib

# path = os.getcwd()
# clib = ctypes.CDLL(os.path.join(path, 'cmatrixlib.so'))

# print(dir(matrix_lib))

def generate_random_matrix(rows, cols):
    python_matrix = [[random.uniform(0.0, 1.0) for _ in range(cols)] for _ in range(rows)]
    cc_matrix = matrix_lib.Matrix(rows, cols)
    for i in range(rows):
        for j in range(cols):
            cc_matrix.SetElement(i, j, python_matrix[i][j])

    return python_matrix, cc_matrix



def set_repetitions(n):
    global repetitions
    repetitions = n

def mul_matrix_speed(matrix_apy, matrix_bpy, matrix_acc, matrix_bcc):
    py = timeit.timeit("np.matmul(matrix_apy, matrix_bpy)", setup="import numpy as np",globals=globals(), number=repetitions)
    print("Python matrix multiplication: ", py)
    cc = timeit.timeit("matrix_acc.MulMatrix(matrix_bcc)", setup="from clib import matrix_lib",globals=globals(), number=repetitions)
    print("C++ matrix multiplication:    ", cc)
    print("-----------------------------------------------------------------")

def mul_matrix_number_speed(matrix_apy, matrix_acc, number):
    py = timeit.timeit("np.multiply(matrix_apy, number)", setup="import numpy as np",globals=globals(), number=100)
    print("Python matrix multiplication by number: ", py)
    cc = timeit.timeit("matrix_acc.MulNumber(number)", setup="from clib import matrix_lib",globals=globals(), number=repetitions)
    print("C++ matrix multiplication by number:    ", cc)
    print("-----------------------------------------------------------------")

def sum_matrix_speed(matrix_apy, matrix_bpy, matrix_acc, matrix_bcc):
    py = timeit.timeit("np.add(matrix_apy, matrix_bpy)", setup="import numpy as np",globals=globals(), number=100)
    print("Python matrix addition: ", py)
    cc = timeit.timeit("matrix_acc.SumMatrix(matrix_bcc)", setup="from clib import matrix_lib",globals=globals(), number=repetitions)
    print("C++ matrix addition:    ", cc)
    print("-----------------------------------------------------------------")


def transpose_speed(matrix_apy, matrix_acc):
    py = timeit.timeit("np.transpose(matrix_apy)", setup="import numpy as np",globals=globals(), number=repetitions)
    print("Python matrix transpose: ", py)
    cc = timeit.timeit("matrix_acc.Transpose()", setup="from clib import matrix_lib",globals=globals(), number=repetitions)
    print("C++ matrix transpose:    ", cc)
    print("-----------------------------------------------------------------")

def determinant_speed(matrix_apy, matrix_acc):
    py = timeit.timeit("np.linalg.det(matrix_apy)", setup="import numpy as np",globals=globals(), number=repetitions)
    print("Python matrix determinant: ", py)
    cc = timeit.timeit("matrix_acc.Determinant()", setup="from clib import matrix_lib",globals=globals(), number=repetitions)
    print("C++ matrix determinant:    ", cc)
    print("-----------------------------------------------------------------")



if __name__ == "__main__":
    rows = 500
    cols = 500
    repetitions = 1

    set_repetitions(repetitions)
    matrix_apy,matrix_acc= generate_random_matrix(rows, cols)
    matrix_bpy, matrix_bcc = generate_random_matrix(rows, cols)
    
    mul_matrix_speed(matrix_apy, matrix_bpy, matrix_acc, matrix_bcc)
    number = random.random()
    mul_matrix_number_speed(matrix_apy, matrix_acc, number)
    sum_matrix_speed(matrix_apy, matrix_bpy, matrix_acc, matrix_bcc)
    transpose_speed(matrix_apy, matrix_acc)
    determinant_speed(matrix_apy, matrix_acc)




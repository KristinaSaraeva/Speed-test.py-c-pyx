#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// структура матрицы
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

//Коды ошибок
#define OK 0
#define WRONG_MATRIX 1
#define CALCULATION_ERROR 2

// Создание матриц
int create_matrix(int rows, int columns, matrix_t *result);
// Очистка матриц
void remove_matrix(matrix_t *A);
// Сравнение матриц
#define SUCCESS 1
#define FAILURE 0
#define ACCURACY 1e-7

int eq_matrix(matrix_t *A, matrix_t *B);

//Сложение матриц
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
//Вычитание матриц
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Умножение матрицы на число
int mult_number(matrix_t *A, double number, matrix_t *result);
// Умножение двух матриц
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Транспонирование матрицы
int transpose(matrix_t *A, matrix_t *result);
// Матрица алгебраических дополнений
int calc_complements(matrix_t *A, matrix_t *result);
//Определитель матрицы (только для квадратной!)
int determinant(matrix_t *A, double *result);
//Обратная матрица
int inverse_matrix(matrix_t *A, matrix_t *result);

//------------------------------------------------------
void empty_matrix(matrix_t *A);
int normal_matrix(matrix_t *matrix);
void copy_matrix(matrix_t *A, matrix_t *new);
void change_first_row(matrix_t *A);
void eliminate(matrix_t *A, int row, int column, matrix_t *eliminated);
int check_zero_row(matrix_t *A);
int check_zero_column(matrix_t *A);

#endif  // MATRIX_H_

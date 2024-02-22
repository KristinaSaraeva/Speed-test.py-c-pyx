#include "matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int err = OK;
  empty_matrix(result);
  if (rows > 0 && columns > 0) {
    double **matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      matrix[i] = (double *)calloc(columns, sizeof(double));
    }
    result->rows = rows;
    result->columns = columns;
    result->matrix = matrix;
  } else {
    err = WRONG_MATRIX;
  }
  return err;
}

void empty_matrix(matrix_t *A) {
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

void remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
      }
      free(A->matrix);
      empty_matrix(A);
    }
  }
}

int eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (normal_matrix(A) && normal_matrix(B)) {
    if ((A->columns != B->columns) || (A->rows != B->rows)) {
      result = FAILURE;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs((A->matrix[i][j] - B->matrix[i][j])) >= ACCURACY) {
            result = FAILURE;
          }
        }
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}

int normal_matrix(matrix_t *matrix) {
  int result = SUCCESS;
  if (matrix == NULL) {
    result = FAILURE;
  } else {
    if (matrix->columns <= 0) result = FAILURE;
    if (matrix->rows <= 0) result = FAILURE;
    if (matrix->matrix == NULL) result = FAILURE;
  }
  return result;
}

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  empty_matrix(result);
  if (normal_matrix(A) && normal_matrix(B)) {
    if ((A->columns != B->columns) || (A->rows != B->rows)) {
      error = CALCULATION_ERROR;
    } else {
      create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else {
    error = WRONG_MATRIX;
  }
  return error;
}

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  empty_matrix(result);
  if (normal_matrix(A) && normal_matrix(B)) {
    if ((A->columns != B->columns) || (A->rows != B->rows)) {
      error = CALCULATION_ERROR;
    } else {
      create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  } else {
    error = WRONG_MATRIX;
  }
  return error;
}

int mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  empty_matrix(result);
  if (isnan(number) || isinf(number)) {
    error = CALCULATION_ERROR;
  } else {
    empty_matrix(result);
    if (normal_matrix(A)) {
      create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      error = WRONG_MATRIX;
    }
  }

  return error;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  empty_matrix(result);
  if (normal_matrix(A) && normal_matrix(B)) {
    if (A->columns == B->rows) {
      create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = WRONG_MATRIX;
  }
  return error;
}

int transpose(matrix_t *A, matrix_t *result) {
  int error = OK;
  empty_matrix(result);
  if (normal_matrix(A)) {
    create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  } else {
    error = WRONG_MATRIX;
  }
  return error;
}

//метод Гаусса - ступенчатая матрица
int determinant(matrix_t *A, double *result) {
  int error = OK;
  if (normal_matrix(A)) {
    if (A->rows == A->columns) {
      int det_sign = 1;
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else {
        if (check_zero_row(A) == 1 || check_zero_column(A) == 1) {
          *result = 0.0;
        } else {
          matrix_t copy;
          copy_matrix(A, &copy);

          if (copy.matrix[0][0] == 0.0) {
            change_first_row(&copy);
            det_sign = -1;
          }
          double P = 0.0;
          P = copy.matrix[0]
                         [0];  // типа как опорный эл-т по т.Барейса(Монтанте)
          matrix_t NewA;
          matrix_t Add;
          while (copy.rows > 1) {
            create_matrix((copy.columns - 1), (copy.rows - 1), &Add);
            create_matrix((copy.columns - 1), (copy.rows - 1), &NewA);

            int m = 1;
            int i = 0;
            while (m < copy.rows) {
              double line_multiplier =
                  (copy.matrix[m][0] / copy.matrix[0][0]) * (-1);
              for (int j = 0; j < Add.columns; j++) {
                Add.matrix[i][j] = copy.matrix[0][j + 1] * line_multiplier;
              }
              i++;
              m++;
            }
            for (i = 0; i < NewA.rows; i++) {
              for (int j = 0; j < NewA.columns; j++) {
                NewA.matrix[i][j] =
                    copy.matrix[i + 1][j + 1] + Add.matrix[i][j];
              }
            }
            P *= NewA.matrix[0][0];
            *result = P * det_sign;
            remove_matrix(&copy);
            copy_matrix(&NewA, &copy);
            remove_matrix(&NewA);
            remove_matrix(&Add);
          }

          remove_matrix(&copy);
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = WRONG_MATRIX;
  }
  return error;
}

void copy_matrix(matrix_t *A, matrix_t *new) {
  create_matrix(A->rows, A->columns, new);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      new->matrix[i][j] = A->matrix[i][j];
    }
  }
}

void change_first_row(matrix_t *A) {
  int i = 0;
  while (A->matrix[i][0] == 0.0) {
    i++;
  }
  double *tmp_row = (double *)calloc(A->rows, sizeof(double));
  for (int j = 0; j < A->columns; j++) {
    tmp_row[j] = A->matrix[i][j];
    A->matrix[i][j] = A->matrix[0][j];
    A->matrix[0][j] = tmp_row[j];
  }
  free(tmp_row);
}

int check_zero_row(matrix_t *A) {
  int zero = 0;
  int i = 0;
  while (i < A->rows) {
    int count = 0;
    for (int j = 0; j < A->columns; j++) {
      if (A->matrix[i][j] == 0.0) {
        count++;
      }
      if (count == A->columns) {
        zero = 1;
      }
    }
    i++;
  }
  return zero;
}

int check_zero_column(matrix_t *A) {
  int zero = 0;
  int j = 0;
  while (j < A->columns) {
    int count = 0;
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i][j] == 0.0) {
        count++;
      }
      if (count == A->rows) {
        zero = 1;
      }
    }
    j++;
  }
  return zero;
}

int calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  empty_matrix(result);
  if (normal_matrix(A)) {
    double det = 0.0;
    determinant(A, &det);
    if (det != 0.0) {
      create_matrix(A->columns, A->rows, result);
      matrix_t eliminated;
      create_matrix(A->rows - 1, A->columns - 1, &eliminated);
      double minor;
      if (eliminated.rows > 1) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            eliminate(A, i, j, &eliminated);
            determinant(&eliminated, &minor);
            result->matrix[i][j] = pow((-1), (i + j + 2)) * minor;
          }
        }
      } else {
        for (int i = 0; i <= eliminated.rows; i++) {
          for (int j = 0; j <= eliminated.columns; j++) {
            minor = A->matrix[!i][!j];
            result->matrix[i][j] = pow((-1), (i + j + 2)) * minor;
          }
        }
      }
      remove_matrix(&eliminated);
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = WRONG_MATRIX;
  }
  return error;
}

void eliminate(matrix_t *A, int row, int column, matrix_t *eliminated) {
  int n = 0;
  for (int i = 0; i < A->rows; i++) {
    if (row != i) {
      int m = 0;
      for (int j = 0; j < A->columns; j++) {
        if (column != j) {
          eliminated->matrix[n][m] = A->matrix[i][j];
          m++;
        }
      }
      n++;
    }
  }
}

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  empty_matrix(result);
  if (normal_matrix(A)) {
    double det = 0.0;
    determinant(A, &det);
    if (det != 0.0) {
      matrix_t tmp_compl;
      matrix_t tmp_transpose;
      calc_complements(A, &tmp_compl);
      transpose(&tmp_compl, &tmp_transpose);
      mult_number(&tmp_transpose, (1 / det), result);
      remove_matrix(&tmp_compl);
      remove_matrix(&tmp_transpose);
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = WRONG_MATRIX;
  }
  return error;
}
#include "plusmatrix.h"

#include <fstream>
#include <stdexcept>

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) { ; }

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::runtime_error("Impossible to create matrix");
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  this->matrix_ = new double*[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    this->matrix_[i] = new double[cols_];
  }
  for (int k = 0; k < other.rows_; k++)
    for (int j = 0; j < other.cols_; j++)
      this->matrix_[k][j] = other.matrix_[k][j];
}

Matrix::Matrix(Matrix&& other) noexcept : rows_(0), cols_(0), matrix_(nullptr) {
  if (this != &other) {
    std::swap(this->rows_, other.rows_);
    std::swap(this->cols_, other.cols_);
    std::swap(this->matrix_, other.matrix_);
  }
}

Matrix::~Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

int Matrix::GetRows() { return this->rows_; }
int Matrix::GetCols() { return this->cols_; }

void Matrix::SetRows(int value) {
  if (value < 0) throw std::runtime_error("Impossible to create matrix");
  Matrix tmp(value, this->cols_);
  int local_rows = 0;
  if (value > this->rows_) local_rows = this->rows_;
  if (value < this->rows_) local_rows = tmp.rows_;
  for (int i = 0; i < local_rows; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      tmp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  for (int i = this->rows_; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      tmp.matrix_[i][j] = 0.0;
    }
  }
  *this = tmp;
}

void Matrix::SetCols(int value) {
  if (value < 0) throw std::runtime_error("Impossible to create matrix");
  Matrix tmp(this->rows_, value);
  int local_cols = 0;
  if (value > this->cols_) local_cols = this->cols_;
  if (value < this->cols_) local_cols = tmp.cols_;
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < local_cols; j++) {
      tmp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = this->cols_; j < tmp.cols_; j++) {
      tmp.matrix_[i][j] = 0.0;
    }
  }
  *this = tmp;
}

double Matrix::GetElement(int row, int col) {
  if ((row >= 0) && (col >= 0))
    return this->matrix_[row][col];
  else
    return 0.0;
}

void Matrix::SetElement(int row, int col, double value) {
  if ((row < 0) || (row >= this->rows_)) return;
  if ((col < 0) || (col >= this->cols_)) return;
  this->matrix_[row][col] = value;
}

//----------------------------------------------------------------

bool Matrix::EqMatrix(const Matrix& other) {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Impossible to make calculations");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs((this->matrix_[i][j] - other.matrix_[i][j]) >= ACCURACY)) {
        res = false;
      }
    }
  }

  return res;
}

Matrix Matrix::SumMatrix(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::runtime_error("Impossible to make calculations");

  Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return result;
}

Matrix Matrix::SubMatrix(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::runtime_error("Impossible to make calculations");

  Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return result;
}

Matrix Matrix::MulNumber(const double num) const {
  Matrix result(rows_, cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[i][j] = this->matrix_[i][j] * num;
    }
  }
  return result;
}

Matrix Matrix::MulMatrix(const Matrix& other) const {
  if (this->cols_ != other.rows_)
    throw std::runtime_error("Impossible to make calculations");

  Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return result;
}

Matrix Matrix::Transpose() {
  Matrix tmp(this->cols_, this->rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      tmp.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return tmp;
}

double Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::runtime_error("Impossible to make calculations");
  }
  double result = 0.0;
  int det_sign = 1;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    if (CheckZeroCol(*this) || CheckZeroRow(*this)) {
      result = 0.0;
    } else {
      Matrix copy_matrix(*this);
      if (matrix_[0][0] == 0.0) {
        copy_matrix.ChangeFirstRow();
        det_sign = -1;
      }
      double p = copy_matrix.matrix_[0][0];
      while (copy_matrix.rows_ > 1) {
        Matrix new_this((copy_matrix.cols_ - 1), (copy_matrix.rows_ - 1));
        Matrix add_matrix((copy_matrix.cols_ - 1), (copy_matrix.rows_ - 1));
        int m = 1;
        int i = 0;
        while (m < copy_matrix.rows_) {
          double line_multiplier =
              (copy_matrix.matrix_[m][0] / copy_matrix.matrix_[0][0]) * (-1);
          for (int j = 0; j < add_matrix.cols_; j++) {
            add_matrix.matrix_[i][j] =
                copy_matrix.matrix_[0][j + 1] * line_multiplier;
          }
          i++;
          m++;
        }
        for (i = 0; i < new_this.rows_; i++) {
          for (int j = 0; j < new_this.cols_; j++) {
            new_this.matrix_[i][j] =
                copy_matrix.matrix_[i + 1][j + 1] + add_matrix.matrix_[i][j];
          }
        }
        p *= new_this.matrix_[0][0];
        result = p * det_sign;
        copy_matrix = new_this;
      }
    }
  }
  return result;
}

void Matrix::ChangeFirstRow() {
  int i = 0;
  while (matrix_[i][0] == 0.0) {
    i++;
  }
  double* tmp_row = new double[rows_];
  for (int j = 0; j < cols_; j++) {
    tmp_row[j] = matrix_[i][j];
    matrix_[i][j] = matrix_[0][j];
    matrix_[0][j] = tmp_row[j];
  }
  delete[] tmp_row;
}

bool Matrix::CheckZeroRow(const Matrix& a) {
  bool zero = false;
  int i = 0;
  while (i < a.rows_) {
    int counter = 0;
    for (int j = 0; j < a.cols_; j++) {
      if (a.matrix_[i][j] == 0.0) {
        counter++;
      }
      if (counter == a.cols_) {
        zero = true;
      }
    }
    i++;
  }
  return zero;
}

bool Matrix::CheckZeroCol(const Matrix& a) {
  bool zero = false;
  int j = 0;
  while (j < a.cols_) {
    int counter = 0;
    for (int i = 0; i < a.rows_; i++) {
      if (a.matrix_[i][j] == 0.0) {
        counter++;
      }
      if (counter == a.rows_) {
        zero = true;
      }
    }
    j++;
  }
  return zero;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::runtime_error(
        "Matrix is not square, cannot calculate complements");
  } else {
    Matrix temp(*this);
    Matrix result(*this);
    Matrix minors(temp.rows_ - 1, temp.cols_ - 1);
    double minor = 0.0;
    if (minors.rows_ > 1) {
      for (int i = 0; i < temp.rows_; i++) {
        for (int j = 0; j < temp.cols_; j++) {
          minors.CalcMinors(i, j, temp);
          minor = minors.Determinant();
          result.matrix_[i][j] = pow((-1), (i + j)) * minor;
        }
      }
    } else {
      for (int i = 0; i <= minors.rows_; i++) {
        for (int j = 0; j <= minors.cols_; j++) {
          minor = temp.matrix_[!i][!j];
          result.matrix_[i][j] = pow((-1), (i + j + 2)) * minor;
        }
      }
    }
    return result;
  }
}

Matrix Matrix::CalcMinors(int row, int col, const Matrix& other) {
  int n = 0;
  for (int i = 0; i < other.rows_; i++) {
    if (row != i) {
      int m = 0;
      for (int j = 0; j < other.cols_; j++) {
        if (col != j) {
          this->matrix_[n][m] = other.matrix_[i][j];
          m++;
        }
      }
      n++;
    }
  }
  return *this;
}

Matrix Matrix::InverseMatrix() {
  Matrix temp(*this);
  double det = temp.Determinant();
  if (det == 0.0) {
    throw std::runtime_error("Matrix is singular, cannot invert");
  }
  temp = temp.CalcComplements();
  temp = temp.Transpose();
  temp.MulNumber(1.0 / det);

  return temp;
}
//----------------------------------------------------------------
// перегрузка операторов  // operator overload

bool Matrix::operator==(const Matrix& other) { return Matrix::EqMatrix(other); }

Matrix& Matrix::operator=(Matrix other) {
  if (this == &other) return *this;
  Matrix tmp(other);
  std::swap(this->rows_, tmp.rows_);
  std::swap(this->cols_, tmp.cols_);
  std::swap(this->matrix_, tmp.matrix_);
  return *this;
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) {
  Matrix result(*this);
  result.MulNumber(num);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

double Matrix::operator()(int row, int col) {
  if (row > rows_ || col > cols_)
    throw std::runtime_error("Impossible to make calculations");
  return GetElement(row, col);
}
//---------------------------------------------
void Matrix::PrintMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      printf("%f ", matrix_[i][j]);
    }
    printf("\n");
  }
}
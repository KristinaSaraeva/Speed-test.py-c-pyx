#ifndef PLUSMATRIX_H_
#define PLUSMATRIX_H_

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <math.h>

#include <cstdio>
#include <exception>

#define ACCURACY 1e-6

class Matrix {
 public:
  Matrix();                         // Default constructor
  Matrix(int rows, int cols);       // constructor
  Matrix(const Matrix& other);      // copy constructor
  Matrix(Matrix&& other) noexcept;  // noexcept faster, move constructor
  ~Matrix();                        // Destructor

  int GetRows();
  int GetCols();
  void SetRows(int value);
  void SetCols(int value);
  double GetElement(int row, int col);
  void SetElement(int row, int col, double value);

  bool EqMatrix(const Matrix& other);
  Matrix SumMatrix(const Matrix& other) const;
  Matrix SubMatrix(const Matrix& other) const;
  Matrix MulNumber(const double num) const;
  Matrix MulMatrix(const Matrix& other) const;
  Matrix Transpose();
  Matrix CalcComplements();
  Matrix CalcMinors(int row, int col, const Matrix& other);
  double Determinant();

  Matrix InverseMatrix();

  // перегрузка операторов  // index operator overload
  Matrix operator+(const Matrix& a);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const double num);
  bool operator==(const Matrix& other);
  Matrix& operator=(Matrix other);  //  (copy + move)
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(const double num);
  double operator()(int row, int col);

  void PrintMatrix();

 private:
  void ChangeFirstRow();
  bool CheckZeroRow(const Matrix& a);
  bool CheckZeroCol(const Matrix& a);
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
};

#endif  // PLUSMATRIX_H_
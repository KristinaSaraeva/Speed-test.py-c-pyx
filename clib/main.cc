#include <pybind11/pybind11.h>

#include "plusmatrix.h"

namespace py = pybind11;

PYBIND11_MODULE(matrix_lib, m) {
    m.doc() = "plusmatrix library";
    py::class_<Matrix>(m, "Matrix")
    .def(py::init<>())
    .def(py::init<int, int>())
    .def("GetRows", &Matrix::GetRows)
    .def("GetCols", &Matrix::GetCols)
    .def("SetRows", &Matrix::SetRows)
    .def("SetCols", &Matrix::SetCols)
    .def("GetElement", &Matrix::GetElement)
    .def("SetElement", &Matrix::SetElement)
    .def("EqMatrix", &Matrix::EqMatrix)
    .def("SumMatrix", &Matrix::SumMatrix)
    .def("SubMatrix", &Matrix::SubMatrix)
    .def("MulNumber", &Matrix::MulNumber)
    .def("MulMatrix", &Matrix::MulMatrix)
    .def("Transpose", &Matrix::Transpose)
    .def("CalcComplements", &Matrix::CalcComplements)
    .def("CalcMinors", &Matrix::CalcMinors)
    .def("Determinant", &Matrix::Determinant)
    .def("InverseMatrix", &Matrix::InverseMatrix);
}
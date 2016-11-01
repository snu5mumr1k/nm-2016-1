#include <matrix.h>
#include <cstring>

Matrix::Matrix(int n) :
    n_(n)
{
    elements_ = new double[n];

    memset(elements_, 0, n * sizeof *elements_);
    for (int i = 0; i < n; ++i) {
        elements_[n * i + i] = 1.0;
    }
}

Matrix::Matrix(int n, const double *elements) :
    n_(n)
{
    elements_ = new double[n];

    memcpy(elements_, elements, n * sizeof *elements_);
}

Matrix::~Matrix() {
    delete elements_;
}

double Matrix::Determinant() const
{}

Matrix Matrix::Inverse() const
{}

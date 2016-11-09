#include <cstring>
#include <matrix.h>
#include <stdexcept>
#include <utils.h>
#include <iostream>

Matrix::Matrix(int n) :
    n_(n)
{
    elements_ = new double[n * n];

    memset(elements_, 0, n * n * sizeof *elements_);
    for (int i = 0; i < n; ++i) {
        elements_[n * i + i] = 1.0;
    }
}

Matrix::Matrix(int n, const double *elements) :
    n_(n)
{
    elements_ = new double[n * n];

    memcpy(elements_, elements, n * n * sizeof *elements_);
}

Matrix::~Matrix() {
    delete [] elements_;
}

void Matrix::Print() const {
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            std::cout << elements_[i * n_ + j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Matrix::SwapRows(int i, int j) {
    if (OutOfBounds(i) || OutOfBounds(j)) {
        throw std::runtime_error("Matrix index is out of bounds");
    }
    if (i == j) {
        return;
    }

    double *tmp = new double[n_];

    memcpy(tmp, &elements_[i * n_], n_ * sizeof *elements_);
    memcpy(&elements_[i * n_], &elements_[j * n_], n_ * sizeof *elements_);
    memcpy(&elements_[j * n_], tmp, n_ * sizeof *elements_);

    delete [] tmp;
}

void Matrix::AddRow(int dest, int src, double multiplier) {
    for (int i = 0; i < n_; ++i) {
        elements_[dest * n_ + i] += multiplier * elements_[src * n_ + i];
    }
}

double Matrix::Determinant() const
{}

Matrix Matrix::Inverse() const
{}

const double *Matrix::operator [](int i) const {
    if (OutOfBounds(i)) {
        throw std::runtime_error("Matrix index is out of range");
    }

    return &elements_[i * n_];
}

Vector Matrix::GaussianElimination(Vector v) {
    if (v.Size() != n_) {
        throw std::runtime_error("Matrix and vector sizes dont match");
    }

    Vector result(n_);

    for (int i = 0; i < n_; ++i) {
        for (int j = i; j < n_; ++j) {
            if (!Zero(elements_[j * n_ + i])) {
                SwapRows(i, j);
                break;
            }
        }

        if (Zero(elements_[i * n_ + i])) {
            throw std::runtime_error("Matrix is singular");
        }

        for (int j = i + 1; j < n_; ++j) {
            double coef = -elements_[j * n_ + i] / elements_[i * n_ + i];
            AddRow(j, i, coef);
            v[j] += v[i] * coef;
        }
    }

    for (int i = n_ - 1; i >= 0; --i) {
        result[i] = v[i];
        for (int j = i + 1; j < n_; ++j) {
            result[i] -= result[j] * elements_[i * n_ + j];
        }
        result[i] /= elements_[i * n_ + i];
    }
    return result;
}

bool Matrix::OutOfBounds(int i) const {
    return i < 0 || i >= n_;
}

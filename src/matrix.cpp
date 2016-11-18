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

Matrix::Matrix(int n, filling_function get_element) :
    Matrix(n)
{
    elements_ = new double[n * n];

    for (int i = 0; i < n; ++i) {
        elements_[n * i + j] = get_element(i, j);
    }
}

Matrix::Matrix(const Matrix &other) :
    Matrix(other.n_, other.elements_)
{}

Matrix::~Matrix() {
    delete [] elements_;
}

Matrix &Matrix::operator =(const Matrix &other) {
    if (this != &other) {
        delete [] elements_;

        n_ = other.n_;
        elements_ = new double[n_ * n_];
        memcpy(elements_, other.elements_, n_ * n_ * sizeof *elements_);
    }

    return *this;
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

int Matrix::Size() const {
    return n_;
}

void Matrix::SwapRows(int i, int j) {
    if (OutOfRange(i) || OutOfRange(j)) {
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

void Matrix::MultiplyRow(int i, double multiplier) {
    for (int j = 0; j < n_; ++j) {
        elements_[i * n_ + j] *= multiplier;
    }
}

void Matrix::AddRow(int dest, int src, double multiplier) {
    for (int i = 0; i < n_; ++i) {
        elements_[dest * n_ + i] += multiplier * elements_[src * n_ + i];
    }
}

double Matrix::Determinant() {
    Vector tmp(n_);
    return GaussianElimination(tmp);
}

Vector Matrix::Solve(Vector v) {
    GaussianElimination(v);

    return v;
}

Matrix Matrix::Inverse() {
    Matrix result(n_);

    GaussianElimination(result);

    return result;
}

const double *Matrix::operator [](int i) const {
    if (OutOfRange(i)) {
        throw std::runtime_error("Matrix index is out of range");
    }

    return &elements_[i * n_];
}

template <typename T>
double Matrix::GaussianElimination(T &right_part) {
    if (right_part.Size() != n_) {
        throw std::runtime_error("Parts sizes dont match");
    }

    double determinant = 1.0;
    for (int i = 0; i < n_; ++i) {
        for (int j = i; j < n_; ++j) {
            if (!Zero(elements_[j * n_ + i])) {
                SwapRows(i, j);
                right_part.SwapRows(i, j);
                if (i != j) {
                    determinant = -determinant;
                }
                break;
            }
        }

        if (Zero(elements_[i * n_ + i])) {
            throw std::runtime_error("Matrix is singular");
        }

        double coef = 1.0 / elements_[i * n_ + i];
        MultiplyRow(i, coef);
        right_part.MultiplyRow(i, coef);
        determinant /= coef;
        for (int j = 0; j < n_; ++j) {
            if (i == j) {
                continue;
            }
            double coef = -elements_[j * n_ + i];
            AddRow(j, i, coef);
            right_part.AddRow(j, i, coef);
        }
    }

    return determinant;
}

bool Matrix::OutOfRange(int i) const {
    return i < 0 || i >= n_;
}

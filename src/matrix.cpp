#include <cmath>
#include <cstring>
#include <matrix.h>
#include <stdexcept>
#include <utils.h>

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

Matrix::Matrix(int n, const BaseElementGenerator &element_generator) :
    n_(n)
{
    elements_ = new double[n * n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            elements_[n * i + j] = element_generator.GetElem(i, j);
        }
    }
}

Matrix::Matrix(const Matrix &other) :
    Matrix(other.n_, other.elements_)
{}

Matrix::~Matrix() {
    delete [] elements_;
}

void Matrix::Print(std::ofstream &fout) const {
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            fout << elements_[i * n_ + j] << ' ';
        }
        fout << std::endl;
    }
}

bool Matrix::OutOfRange(int i) const {
    return i < 0 || i >= n_;
}

int Matrix::Size() const {
    return n_;
}

void Matrix::SetNaN() {
    for (int i = 0; i < n_ * n_; ++i) {
        elements_[i] = std::nan("");
    }
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

Matrix Matrix::Transpose() const {
    Matrix tmp(n_);

    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            tmp.elements_[i * n_ + j] = elements_[j * n_ + i];
        }
    }

    return tmp;
}

double Matrix::Determinant(Pivoting use_pivoting) {
    Vector tmp(n_);

    return GaussianElimination(tmp, use_pivoting);
}

Vector Matrix::Solve(const Vector &v, Pivoting use_pivoting) {
    Vector result(v);
    GaussianElimination(result, use_pivoting);

    return result;
}

Matrix Matrix::Inverse(Pivoting use_pivoting) {
    Matrix result(n_);

    GaussianElimination(result, use_pivoting);

    return result;
}

Vector Matrix::SuccessiveOverRelaxation(const Vector &f, double rel_factor) const {
    static const double CONVERGENCY_TRESHOLD = 1e-3;
    static const int MAX_ITERATIONS_COUNT = 1e6;

    if (n_ != f.Size()) {
        throw std::runtime_error("Matrix and vector sizes dont match");
    }

    Vector result(n_);
    double residual = 0.0;
    int iterations_count = 0;
    do {
        for (int i = 0; i < n_; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n_; ++j) {
                sum += elements_[i * n_ + j] * result[j];
            }
            result[i] = result[i] + rel_factor * (f[i] - sum) / elements_[i * n_ + i];
        }
        residual = (*this * result - f).EuclideanNorm();
        iterations_count++;
    } while (residual > CONVERGENCY_TRESHOLD && iterations_count < MAX_ITERATIONS_COUNT);

    return result;
}

int Matrix::ChooseRow(int curr_row, Pivoting use_pivoting) {
    if (use_pivoting) {
        int max_index = curr_row;
        for (int j = curr_row; j < n_; ++j) {
            if (fabs(elements_[max_index * n_ + curr_row]) < fabs(elements_[j * n_ + curr_row])) {
                max_index = j;
            }
        }
        return max_index;
    } else {
        for (int j = curr_row; j < n_; ++j) {
            if (!Zero(elements_[j * n_ + curr_row])) {
                return j;
            }
        }
    }

    return curr_row;
}

double Matrix::GaussianElimination(BaseRightEquationsSystemPart &right_part, Pivoting use_pivoting) {
    if (right_part.Size() != n_) {
        throw std::runtime_error("Parts sizes dont match");
    }

    double determinant = 1.0;
    for (int i = 0; i < n_; ++i) {
        int row = ChooseRow(i, use_pivoting);
        if (i != row) {
            determinant = -determinant;
            SwapRows(i, row);
            right_part.SwapRows(i, row);
        }

        if (Zero(elements_[i * n_ + i])) {
            right_part.SetNaN();
            return 0.0;
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

const double *Matrix::operator [](int i) const {
    if (OutOfRange(i)) {
        throw std::runtime_error("Matrix index is out of range");
    }

    return &elements_[i * n_];
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

Matrix Matrix::operator +=(const Matrix &other) {
    if (n_ != other.n_) {
        throw std::runtime_error("Matrices sizes dont match");
    }

    for (int i = 0; i < n_ * n_; ++i) {
        elements_[i] += other.elements_[i];
    }

    return *this;
}

Matrix Matrix::operator -=(const Matrix &other) {
    if (n_ != other.n_) {
        throw std::runtime_error("Matrices sizes dont match");
    }

    for (int i = 0; i < n_ * n_; ++i) {
        elements_[i] -= other.elements_[i];
    }

    return *this;
}

Matrix Matrix::operator *=(const Matrix &other) {
    if (n_ != other.n_) {
        throw std::runtime_error("Matrices sizes dont match");
    }

    *this = *this * other;

    return *this;
}

Matrix Matrix::operator +(const Matrix &other) const {
    Matrix tmp(*this);

    tmp += other;
    return tmp;
}

Matrix Matrix::operator -(const Matrix &other) const {
    Matrix tmp(*this);

    tmp -= other;
    return tmp;
}

Matrix Matrix::operator *(const Matrix &other) const {
    if (n_ != other.n_) {
        throw std::runtime_error("Matrices sizes dont match");
    }

    Matrix tmp(n_);
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            tmp.elements_[i * n_ + j] = 0.0;
            for (int k = 0; k < n_; ++k) {
                tmp.elements_[i * n_ + j] += elements_[i * n_ + k] * other.elements_[k * n_ + j];
            }
        }
    }

    return tmp;
}

Vector Matrix::operator *(const Vector &other) const {
    if (n_ != other.Size()) {
        throw std::runtime_error("Matrix and vector sizes dont match");
    }

    Vector tmp(n_);
    for (int i = 0; i < n_; ++i) {
        tmp[i] = 0.0;
        for (int j = 0; j < n_; ++j) {
            tmp[i] += elements_[i * n_ + j] * other[j];
        }
    }
    return tmp;
}

Matrix Matrix::operator +() const {
    return *this;
}

Matrix Matrix::operator -() const {
    Matrix tmp(n_);

    for (int i = 0; i < n_; ++i) {
        tmp.elements_[i] = -elements_[i];
    }

    return tmp;
}

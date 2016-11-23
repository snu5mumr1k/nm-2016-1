#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector.h>

Vector::Vector(int n) :
    n_(n)
{
    elements_ = new double[n];
    memset(elements_, 0, n * sizeof *elements_);
}

Vector::Vector(int n, const double *elements) :
    n_(n)
{
    elements_ = new double[n];
    memcpy(elements_, elements, n * sizeof *elements_);
}

Vector::Vector(int n, const BaseElementGenerator &element_generator) :
    n_(n)
{
    elements_ = new double[n];

    for (int i = 0; i < n; ++i) {
        elements_[i] = element_generator.GetElem(i);
    }
}

Vector::Vector(const Vector &v) :
    Vector(v.n_, v.elements_)
{}

Vector::~Vector() {
    delete [] elements_;
}

void Vector::Print() const {
    for (int i = 0; i < n_; ++i) {
        std::cout << elements_[i] << ' ';
    }
    std::cout << std::endl;
}

int Vector::Size() const {
    return n_;
}

void Vector::SetNaN() {
    for (int i = 0; i < n_; ++i) {
        elements_[i] = std::nan("");
    }
}

void Vector::MultiplyRow(int i, double multiplier) {
    if (OutOfRange(i)) {
        throw std::runtime_error("Vector index is out of range");
    }

    elements_[i] *= multiplier;
}

void Vector::SwapRows(int i, int j) {
    if (OutOfRange(i) || OutOfRange(j)) {
        throw std::runtime_error("Vector index is out of range");
    }

    std::swap(elements_[i], elements_[j]);
}

void Vector::AddRow(int dest, int src, double coef) {
    if (OutOfRange(dest) || OutOfRange(src)) {
        throw std::runtime_error("Vector index is out of range");
    }

    elements_[dest] += coef * elements_[src];
}

double Vector::operator [](int i) const {
    if (OutOfRange(i)) {
        throw std::runtime_error("Vector index is out of range");
    }

    return elements_[i];
}

double &Vector::operator [](int i) {
    if (OutOfRange(i)) {
        throw std::runtime_error("Vector index is out of range");
    }

    return elements_[i];
}

bool Vector::OutOfRange(int i) const {
    return i < 0 || i >= n_;
}

Vector Vector::operator +()
{}

Vector Vector::operator -() {
    for (int i = 0; i < n_; ++i) {
        elements_[i] = -elements_[i];
    }
}

Vector Vector::operator +=(const Vector &other) {
    if (n_ != other.n_) {
        throw std::runtime_error("Vector sizes dont match");
    }

    for (int i = 0; i < n_; ++i) {
        elements_[i] += other.elements_[i];
    }

    return *this;
}

Vector Vector::operator -=(const Vector &other) {
    if (n_ != other.n_) {
        throw std::runtime_error("Vector sizes dont match");
    }

    for (int i = 0; i < n_; ++i) {
        elements_[i] -= other.elements_[i];
    }

    return *this;
}

Vector Vector::operator +(const Vector &other) {
    Vector tmp(*this);

    tmp += other;

    return tmp;
}

Vector Vector::operator -(const Vector &other) {
    Vector tmp(*this);

    tmp -= other;

    return tmp;
}

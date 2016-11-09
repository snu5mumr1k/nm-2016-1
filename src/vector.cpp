#include <vector.h>
#include <stdexcept>
#include <cstring>

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

Vector::Vector(const Vector &v) :
    Vector(v.n_, v.elements_)
{}

Vector::~Vector() {
    delete [] elements_;
}

double Vector::operator [](int i) const {
    if (i < 0 || i >= n_) {
        throw std::runtime_error("index in vector operator [] is out of bounds");
    }

    return elements_[i];
}

double &Vector::operator [](int i) {
    if (i < 0 || i >= n_) {
        throw std::runtime_error("index in vector operator [] is out of bounds");
    }

    return elements_[i];
}

int Vector::Size() const {
    return n_;
}

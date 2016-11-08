#pragma once

class Vector {
public:
    Vector(int n);
    Vector(int n, const double *elements);

    ~Vector();

    int Size() const;

    double operator [](int i) const;
    double &operator [](int i);

private:
    int n_;
    double *elements_;
};

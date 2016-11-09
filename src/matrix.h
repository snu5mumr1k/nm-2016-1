#pragma once

#include <vector.h>

class Matrix {
public:
    Matrix(int n);
    Matrix(int n, const double *elements);

    ~Matrix();

    void Print() const;

    void SwapRows(int i, int j);
    void AddRow(int dest, int src, double multiplier);

    double Determinant() const;
    Matrix Inverse() const;

    Vector GaussianElimination(Vector v);

    const double *operator [](int i) const;
    bool OutOfBounds(int i) const;

private:
    int n_;
    double *elements_;
};

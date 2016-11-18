#pragma once

#include <vector.h>

typedef double (*filling_function)(int i, int j);

class Matrix {
public:
    Matrix(int n);
    Matrix(int n, const double *elements);
    Matrix(int n, filling_function get_element);
    Matrix(const Matrix &other);

    ~Matrix();

    Matrix &operator =(const Matrix &other);

    void Print() const;
    int Size() const;

    void SwapRows(int i, int j);
    void MultiplyRow(int i, double multiplier);
    void AddRow(int dest, int src, double multiplier);

    double Determinant();
    Vector Solve(Vector v);
    Matrix Inverse();

    const double *operator [](int i) const;
    bool OutOfRange(int i) const;

private:
    int n_;
    double *elements_;

    template <typename T>
    double GaussianElimination(T &other);
};

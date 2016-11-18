#pragma once

#include <element_generator.h>
#include <vector.h>

enum Pivoting : bool {
    USE_PIVOTING = true,
    DONT_USE_PIVOTING = false,
};

class Matrix {
public:
    Matrix(int n);
    Matrix(int n, const double *elements);
    Matrix(int n, const BaseElementGenerator &element_generator);
    Matrix(const Matrix &other);

    ~Matrix();

    Matrix &operator =(const Matrix &other);

    void Print() const;
    int Size() const;

    void SwapRows(int i, int j);
    void MultiplyRow(int i, double multiplier);
    void AddRow(int dest, int src, double multiplier);

    double Determinant(Pivoting use_pivoting = DONT_USE_PIVOTING);
    Vector Solve(Vector v, Pivoting use_pivoting = DONT_USE_PIVOTING);
    Matrix Inverse(Pivoting use_pivoting = DONT_USE_PIVOTING);

    const double *operator [](int i) const;
    bool OutOfRange(int i) const;

private:
    int n_;
    double *elements_;

    template <typename T>
    double GaussianElimination(T &right_part);

    template <typename T>
    double GaussianEliminationWithPivoting(T &right_part);
};

#pragma once

class Matrix {
public:
    Matrix(int n);
    Matrix(int n, const double *elements);

    ~Matrix();

    double Determinant() const;
    Matrix Inverse() const;

private:
    int n_;
    double *elements_;
};

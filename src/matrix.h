#pragma once

#include <base_right_part.h>
#include <element_generator.h>
#include <fstream>
#include <vector.h>

enum Pivoting : bool {
    USE_PIVOTING = true,
    DONT_USE_PIVOTING = false,
};

class Matrix : public BaseRightEquationsSystemPart {
public:
    Matrix(int n);
    Matrix(int n, const double *elements);
    Matrix(int n, const BaseElementGenerator &element_generator);
    Matrix(const Matrix &other);

    ~Matrix();

    void Print(std::ofstream &fout) const;
    bool OutOfRange(int i) const;
    int Size() const;

    void SetNaN();
    void SwapRows(int i, int j);
    void MultiplyRow(int i, double multiplier);
    void AddRow(int dest, int src, double multiplier);

    Matrix Transpose() const;

    double Determinant(Pivoting use_pivoting = DONT_USE_PIVOTING);
    Vector Solve(const Vector &v, Pivoting use_pivoting = DONT_USE_PIVOTING);
    Matrix Inverse(Pivoting use_pivoting = DONT_USE_PIVOTING);

    Vector SuccessiveOverRelaxation(const Vector &f, double rel_factor) const;

    const double *operator [](int i) const;

    Matrix &operator =(const Matrix &other);
    Matrix operator += (const Matrix &other);
    Matrix operator -= (const Matrix &other);
    Matrix operator *= (const Matrix &other);

    Matrix operator + (const Matrix &other) const;
    Matrix operator - (const Matrix &other) const;
    Matrix operator * (const Matrix &other) const;

    Vector operator * (const Vector &other) const;

    Matrix operator + () const;
    Matrix operator - () const;

private:
    int n_;
    double *elements_;

    int ChooseRow(int curr_row, Pivoting use_pivoting = DONT_USE_PIVOTING);

    double GaussianElimination(BaseRightEquationsSystemPart &right_part,
        Pivoting use_pivoting = DONT_USE_PIVOTING);
};

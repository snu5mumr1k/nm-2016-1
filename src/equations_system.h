#pragma once

#include <element_generator.h>
#include <string>
#include <vector.h>
#include <matrix.h>

class EquationsSystem {
public:
    EquationsSystem(const std::string &filename);
    EquationsSystem(int n, const BaseElementGenerator &element_generator);

    ~EquationsSystem();

    Vector Solve(Pivoting use_pivoting = DONT_USE_PIVOTING) const;
    double Residual(Pivoting use_pivoting = DONT_USE_PIVOTING) const;
    double Determinant(Pivoting use_pivoting = DONT_USE_PIVOTING) const;
    Matrix Inverse(Pivoting use_pivoting = DONT_USE_PIVOTING) const;

    Vector SuccessiveOverRelaxation(double rel_factor) const;
    double RelaxationResidual(double rel_factor) const;

private:
    Matrix *coefficients_;
    Vector *constants_;
};

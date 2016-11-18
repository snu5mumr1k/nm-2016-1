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
    double Determinant(Pivoting use_pivoting = DONT_USE_PIVOTING) const;

private:
    Matrix *coefficients_;
    Vector *constants_;
};

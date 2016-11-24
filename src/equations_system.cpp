#include <cmath>
#include <equations_system.h>
#include <fstream>
#include <utils.h>

EquationsSystem::EquationsSystem(const std::string &filename) {
    std::fstream file(filename);

    int n = 0;
    file >> n;
    double *matrix_elements = new double[n * n];
    double *vector_elements = new double[n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix_elements[i * n + j];
        }
        file >> vector_elements[i];
    }

    coefficients_ = new Matrix(n, matrix_elements);
    constants_ = new Vector(n, vector_elements);

    delete [] matrix_elements;
    delete [] vector_elements;
}

EquationsSystem::EquationsSystem(int n, const BaseElementGenerator &element_generator) {
    coefficients_ = new Matrix(n, element_generator);
    constants_ = new Vector(n, element_generator);
}

EquationsSystem::~EquationsSystem() {
    delete coefficients_;
    delete constants_;
}

Vector EquationsSystem::Solve(Pivoting use_pivoting) const {
    Matrix tmp(*coefficients_);

    return tmp.Solve(*constants_, use_pivoting);
}

double EquationsSystem::Residual(Pivoting use_pivoting) const {
    Vector result = Solve(use_pivoting);

    Vector residual_vector = *coefficients_ * result - *constants_;

    return residual_vector.EuclideanNorm();
}

double EquationsSystem::Determinant(Pivoting use_pivoting) const {
    Matrix tmp(*coefficients_);

    return tmp.Determinant(use_pivoting);
}

Matrix EquationsSystem::Inverse(Pivoting use_pivoting) const {
    Matrix tmp(*coefficients_);

    return tmp.Inverse(use_pivoting);
}

Vector EquationsSystem::SuccessiveOverRelaxation(double rel_factor = 1.0) const {
    Matrix tmp_matrix = coefficients_->Transpose() * *coefficients_;
    Vector tmp_vector = coefficients_->Transpose() * *constants_;

    return tmp_matrix.SuccessiveOverRelaxation(tmp_vector, rel_factor);
}

double EquationsSystem::RelaxationResidual(double rel_factor = 1.0) const {
    Vector result = SuccessiveOverRelaxation(rel_factor);

    if (std::isnan(result[0])) {
        return std::nan("");
    }

    Vector residual_vector = *coefficients_ * result - *constants_;
    return residual_vector.EuclideanNorm();
}

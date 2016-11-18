#include <cmath>
#include <utils.h>

bool Equal(double a, double b) {
    return fabs(a - b) < EPS;
}

bool Zero(double a) {
    return Equal(a, 0.0);
}

ElementGenerator::ElementGenerator(int m, double x) :
    BaseElementGenerator(),
    m_(m),
    x_(x)
{}

double ElementGenerator::GetElem(int i) const {
    return x_ * exp(x_ / i) * cos (x_ / i);
}

double ElementGenerator::GetElem(int i, int j) const {
    static const double Q = 1.001 - 2 * m_ * 0.001;

    if (i == j) {
        return pow(Q - 1, i + j);
    }

    return pow(Q, i + j) + 0.1 * (j - i);
}

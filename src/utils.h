#pragma once

#include <element_generator.h>

const double EPS = 1e-9;

bool Equal(double a, double b);
bool Zero(double a);

class ElementGenerator : public BaseElementGenerator {
public:
    ElementGenerator(int m, double x);

    double GetElem(int i) const;
    double GetElem(int i, int j) const;

private:
    double x_;
    int m_;
};

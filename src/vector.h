#pragma once

#include <base_right_part.h>
#include <element_generator.h>

class Vector : public BaseRightEquationsSystemPart {
public:
    Vector(int n);
    Vector(int n, const double *elements);
    Vector(int n, const BaseElementGenerator &element_generator);
    Vector(const Vector &v);

    ~Vector();

    void Print() const;
    int Size() const;

    void SetNaN();
    void MultiplyRow(int i, double multiplier);
    void SwapRows(int i, int j);
    void AddRow(int dest, int src, double coef);

    double operator [](int i) const;
    double &operator [](int i);

    bool OutOfRange(int i) const;

    Vector operator +();
    Vector operator -();

    Vector operator +=(const Vector &other);
    Vector operator +(const Vector &other);

    Vector operator -=(const Vector &other);
    Vector operator -(const Vector &other);

private:
    int n_;
    double *elements_;
};

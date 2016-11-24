#pragma once

#include <base_right_part.h>
#include <element_generator.h>
#include <fstream>

class Vector : public BaseRightEquationsSystemPart {
public:
    Vector(int n);
    Vector(int n, const double *elements);
    Vector(int n, const BaseElementGenerator &element_generator);
    Vector(const Vector &v);

    ~Vector();

    void Print(std::ofstream &fout) const;
    int Size() const;

    void SetNaN();
    void MultiplyRow(int i, double multiplier);
    void SwapRows(int i, int j);
    void AddRow(int dest, int src, double coef);

    double EuclideanNorm() const;

    double operator [](int i) const;
    double &operator [](int i);

    bool OutOfRange(int i) const;


    Vector operator +=(const Vector &other);
    Vector operator -=(const Vector &other);

    Vector operator +(const Vector &other) const;
    Vector operator -(const Vector &other) const;
    Vector operator +() const;
    Vector operator -() const;

private:
    int n_;
    double *elements_;
};

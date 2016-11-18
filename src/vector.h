#pragma once

class Vector {
public:
    Vector(int n);
    Vector(int n, const double *elements);
    Vector(const Vector &v);

    ~Vector();

    void Print() const;
    int Size() const;

    void MultiplyRow(int i, double multiplier);
    void SwapRows(int i, int j);
    void AddRow(int dest, int src, double coef);

    double operator [](int i) const;
    double &operator [](int i);

    bool OutOfRange(int i) const;

private:
    int n_;
    double *elements_;
};

#pragma once

#include <base_right_part.h>

class OperationsCounter : public BaseRightEquationsSystemPart {
public:
    OperationsCounter(int n);

    void SwapRows(int i, int j);
    void MultiplyRow(int i, double coef);
    void AddRow(int dst, int src, double coef);
    int Size() const;
private:
    int n_;

    int multiplies_;
    int adds_;
    int swaps_;
};

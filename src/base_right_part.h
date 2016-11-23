#pragma once

class BaseRightEquationsSystemPart {
public:
    virtual void SetNaN();
    virtual void SwapRows(int i, int j);
    virtual void MultiplyRow(int i, double coef);
    virtual void AddRow(int dest, int src, double coef);
    virtual int Size() const;
};

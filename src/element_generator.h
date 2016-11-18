#pragma once

class BaseElementGenerator {
public:
    BaseElementGenerator() = default;

    virtual double GetElem(int i) const;
    virtual double GetElem(int i, int j) const;
};

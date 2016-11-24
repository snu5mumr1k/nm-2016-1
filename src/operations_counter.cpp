#include <operations_counter.h>

OperationsCounter::OperationsCounter(int n) :
    n_(n),
    multiplies_(0),
    adds_(0),
    swaps_(0)
{}

void OperationsCounter::SwapRows(int i, int j) {
    swaps_ += n_;
}

void OperationsCounter::MultiplyRow(int i, double coef) {
    multiplies_ += n_;
}

void OperationsCounter::AddRow(int dest, int src, double coef) {
    multiplies_ += n_;
    adds_ += n_;
}

int OperationsCounter::Size() const {
    return n_;
}

#include <utils.h>
#include <cmath>

bool Equal(double a, double b) {
    return fabs(a - b) < EPS;
}

bool Zero(double a) {
    return Equal(a, 0.0);
}

#include <equations_system.h>
#include <vector.h>

int main(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        EquationsSystem s(argv[i]);
        s.Solve().Print();
    }

    return 0;
}

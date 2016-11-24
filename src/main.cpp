#include <equations_system.h>
#include <utils.h>
#include <vector.h>
#include <fstream>
#include <iostream>

void run_small(std::ofstream &fout_gauss, std::ofstream &fout_gauss_with_pivoting, std::ofstream &fout_zeidel) {
    std::ifstream fin;
    fin.open("data/inputs_small");
    std::ofstream fout_residual;
    fout_residual.open("data/residual");

    while (!fin.eof()) {
        std::string filename;
        fin >> filename;
        if (filename.size() == 0) {
            break;
        }
        EquationsSystem s(filename);
        s.Solve().Print(fout_gauss);
        s.Solve(USE_PIVOTING).Print(fout_gauss_with_pivoting);
        double res_without_pivot = s.Residual();
        double res_with_pivot = s.Residual(USE_PIVOTING);
        fout_residual << res_without_pivot << ' ' << res_with_pivot << ' ' << res_with_pivot - res_without_pivot << std::endl;
    }
    fout_residual.close();
    fin.close();
}

void run_big(std::ofstream &fout_gauss, std::ofstream &fout_gauss_with_pivoting, std::ofstream &fout_zeidel) {
    std::ifstream fin;
    fin.open("data/inputs_big");
    std::ofstream fout_residual;
    fout_residual.open("data/residual");

    int n = 0;
    int M = 0;
    fin >> n >> M;
    while (!fin.eof()) {
        double x = 0.0;
        fin >> x;
        if (fin.eof()) {
            break;
        }

        ElementGenerator g(M, x);
        EquationsSystem s(n, g);
        s.Solve().Print(fout_gauss);
        s.Solve(USE_PIVOTING).Print(fout_gauss_with_pivoting);
        double res_without_pivot = s.Residual();
        double res_with_pivot = s.Residual(USE_PIVOTING);
        fout_residual << res_without_pivot << ' ' << res_with_pivot << ' ' << res_with_pivot - res_without_pivot << std::endl;
    }
    fout_residual.close();
    fin.close();
}

int main() {
    std::ofstream fout_gauss;
    fout_gauss.open("data/gauss_out");
    std::ofstream fout_gauss_with_pivoting;
    fout_gauss_with_pivoting.open("data/gauss_pivot_out");
    std::ofstream fout_zeidel;
    fout_zeidel.open("data/zeidel_out");

    run_small(fout_gauss, fout_gauss_with_pivoting, fout_zeidel);
    run_big(fout_gauss, fout_gauss_with_pivoting, fout_zeidel);

    fout_gauss.close();
    fout_gauss_with_pivoting.close();
    fout_zeidel.close();

    return 0;
}

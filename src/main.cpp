#include <equations_system.h>
#include <utils.h>
#include <vector.h>
#include <fstream>
#include <iostream>

void run_small(std::ofstream &fout_gauss, std::ofstream &fout_gauss_with_pivoting, std::ofstream &fout_relaxation) {
    std::ifstream fin;
    fin.open("data/inputs_small");
    std::ofstream fout_residual;
    fout_residual.open("data/residual");

    while (!fin.eof()) {
        std::string filename;
        double rel_factor = 0.0;
        fin >> filename >> rel_factor;
        if (filename.size() == 0) {
            break;
        }
        EquationsSystem s(filename);

        s.Solve().Print(fout_gauss);
        s.Solve(USE_PIVOTING).Print(fout_gauss_with_pivoting);

        s.SuccessiveOverRelaxation(rel_factor).Print(fout_relaxation);

        double res_without_pivot = s.Residual();
        double res_with_pivot = s.Residual(USE_PIVOTING);
        double res_relax = s.RelaxationResidual(rel_factor);
        fout_residual << res_without_pivot << ' ' << res_with_pivot << ' ' << res_relax << std::endl;
    }
    fout_residual.close();
    fin.close();
}

void run_big(std::ofstream &fout_gauss, std::ofstream &fout_gauss_with_pivoting, std::ofstream &fout_relaxation) {
    std::ifstream fin;
    fin.open("data/inputs_big");
    std::ofstream fout_residual;
    fout_residual.open("data/residual");

    int n = 0;
    int M = 0;
    fin >> n >> M;
    while (!fin.eof()) {
        double x = 0.0;
        double rel_factor = 0.0;
        fin >> x >> rel_factor;
        if (fin.eof()) {
            break;
        }

        ElementGenerator g(M, x);
        EquationsSystem s(n, g);

        s.Solve().Print(fout_gauss);
        s.Solve(USE_PIVOTING).Print(fout_gauss_with_pivoting);

        s.SuccessiveOverRelaxation(rel_factor).Print(fout_relaxation);

        double res_without_pivot = s.Residual();
        double res_with_pivot = s.Residual(USE_PIVOTING);
        double res_relax = s.RelaxationResidual(rel_factor);
        fout_residual << res_without_pivot << ' ' << res_with_pivot << ' ' << res_relax << std::endl;
    }
    fout_residual.close();
    fin.close();
}

int main() {
    std::ofstream fout_gauss;
    fout_gauss.open("data/gauss_out");
    std::ofstream fout_gauss_with_pivoting;
    fout_gauss_with_pivoting.open("data/gauss_pivot_out");
    std::ofstream fout_relaxation;
    fout_relaxation.open("data/relaxation_out");

    run_small(fout_gauss, fout_gauss_with_pivoting, fout_relaxation);
    run_big(fout_gauss, fout_gauss_with_pivoting, fout_relaxation);

    fout_gauss.close();
    fout_gauss_with_pivoting.close();
    fout_relaxation.close();

    return 0;
}

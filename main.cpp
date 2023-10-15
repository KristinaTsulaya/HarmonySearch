#include <iostream>
#include <fstream>
#include "HS.h"

int main() {
    double f_min = 0.0;
    double cur_f_value = DBL_MAX - 1;
    size_t cur_iter = 1;

    // boundaries of the domain
    int min = -10;
    int max = 10;

    HS hs(min, max, 20, 2);
    hs.gen_rand_harmonies();

    std::ofstream out;
    out.open("/home/tsulayakris/CLionProjects/HarmonySearch/results");

    while (std::abs(cur_f_value - f_min) > pow(10, -3)) {
        cur_f_value = hs.find_best();
        ++cur_iter;
    }

    out << "Iteration: " << cur_iter << std::endl;
    out << "Solution: " << cur_f_value << std::endl;
    hs.print_val(out);
    out << std::endl;

    out.close();
    return 0;
}

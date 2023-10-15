#include <iostream>
#include "HS.h"

int main() {
    double f_min = 0.0;
    double cur_f_value = DBL_MAX - 1;
    size_t cur_iter = 1;

    // boundaries of the domain
    int min = -10;
    int max = 10;

    HS hs(min, max, 30, 2);
    hs.gen_rand_harmonies();

//    std::cout << "Harmony memory: " << std::endl;
//    hs.print();

    while (std::abs(cur_f_value - f_min) > pow(10, -7)) {
        std::cout << cur_iter << std::endl;
        cur_f_value = hs.find_best();
        ++cur_iter;
    }
    return 0;
}

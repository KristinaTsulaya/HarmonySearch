#include <iostream>
#include <fstream>
#include <chrono>
#include "HS.h"

int main() {
    size_t cur_iter = 0;
    size_t max_iter = 3000;
    double cur_f_value;

    // boundaries of the domain
    double min = 0;
    double max = 3.14;

    HS hs(min, max, 50, 2);

    std::ofstream out;
    out.open("/home/tsulayakris/CLionProjects/HarmonySearch/results");

    auto start = std::chrono::high_resolution_clock::now();
    while (cur_iter < max_iter) {
        cur_f_value = hs.find_best(cur_iter, max_iter);
        if (cur_iter % 10 == 0){
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            out << "Time: " << duration.count() / 1e6 << std::endl;
            out << "Solution: " << cur_f_value << std::endl;
            hs.print_val(out);
            out << std::endl;
        }
        ++cur_iter;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    out << "Time: " << duration.count() / 1e6 << std::endl;
    out << "Solution: " << cur_f_value << std::endl;
    hs.print_val(out);
    out << std::endl;

    out.close();
    return 0;
}

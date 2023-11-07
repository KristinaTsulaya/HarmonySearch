#include <iostream>
#include <random>

namespace _random {
    class distributions {
    public:
        static double uniform_real(double a, double b) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(a, b);
            return dis(gen);
        }
        static double normal_double(double a, double b) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<> dis(a, b);
            return dis(gen);
        }

        static double bernoulli(double p) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::bernoulli_distribution dis(p);
            return dis(gen);
        }

        static int uniform_int(int a, int b) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(a, b);
            return dis(gen);
        }
    };
}
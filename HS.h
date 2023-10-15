#include <vector>
#include <random>
#include <cfloat>

class HS {
private:
    size_t cols, rows; // --- |||
    size_t size;

    int max;
    int min;

    std::vector<double> harmonies;
    std::vector<double> tmp_harmony;

    size_t worst_position = 0;
    size_t best_position = 0;

    double fitness_worst = 0, fitness_best = DBL_MAX;

public:
    struct adjusters {
    public:
        double r_pa = 0.5; // par
        double r_accept = 0.95; // hmar
        double pitch_lim = 0;

        double e = gen_double_val(-1, 1); // uniform
        double bandwidth = gen_double_val(-1, 1); // uniform // bw

    public:
        double gen_double_val(double a, double b) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(a, b);
            return dis(gen);
        }

        int gen_int_val(int a, int b) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(a, b);
            return dis(gen);
        }
    };

    adjusters adjusters;

public:
    HS(int _min, int _max, size_t _cols, size_t _rows) {
        min = _min;
        max = _max;

        cols = _cols;
        rows = _rows;
        size = cols * rows;

        harmonies.resize(size);
        tmp_harmony.resize(rows);
    }

    void gen_rand_harmonies() {
        for (size_t i = 0; i < harmonies.size(); ++i) {
            harmonies[i] = adjusters.gen_double_val(min, max);
        }
    }

    void gen_new_harmony() {
        for (size_t i = 0; i < tmp_harmony.size(); ++i) {
            tmp_harmony[i] = adjusters.gen_double_val(0, 0);
        }
    }

    double fitness(double x, double y) {
//        return log(1 + pow(1 - x, 2) + 100 * pow(y - pow(x, 2), 2)); // fx min at (1, 1)
        return pow(x, 2) + pow(y, 2);  // fx min at (0, 0)
//        return exp(pow(x,2) + pow(y, 2));
    }

    double find_best() {
        for (size_t j = 0; j < rows; ++j) {
            int i = adjusters.gen_int_val(0, cols);
            double rand_value = adjusters.gen_double_val(0, 1);

            if (rand_value < adjusters.r_accept) {
                tmp_harmony[j] = harmonies[i * rows + j];
                rand_value = adjusters.gen_double_val(0, 1);
                if (rand_value < adjusters.r_pa) {
                    tmp_harmony[j] = tmp_harmony[j] + adjusters.e * adjusters.bandwidth;
                }
            } else {
                tmp_harmony[j] = adjusters.gen_double_val(min, max);
            }
        }

        for (size_t i = 0; i < cols; ++i) {
            double fitness_tmp_val = fitness(harmonies[i * rows + 0], harmonies[i * rows + 1]);
            if (fitness_tmp_val < fitness_best) {
                fitness_best = fitness_tmp_val;
                best_position = i;
            }
            if (fitness_tmp_val > fitness_worst) {
                fitness_worst = fitness_tmp_val;
                worst_position = i;
            }
        }

        double fitness_tmp = fitness(tmp_harmony[0], tmp_harmony[1]);
        if (fitness_tmp < fitness_worst) {
            for (size_t j = 0; j < rows; ++j) {
                harmonies[worst_position * rows + j] = tmp_harmony[j];
            }
        }

        std::cout << "Solution: " << fitness_tmp << std::endl;
        std::cout << "Generated harmony (x): " << tmp_harmony[0] << " " << tmp_harmony[1] << std::endl;
//        std::cout << "Harmony memory: " << std::endl;
//        print();

        fitness_worst = 0, fitness_best = DBL_MAX;
        gen_new_harmony();

        return fitness_tmp;
    }

    void print() const{
        for (size_t i = 0; i < cols; ++i) {
            for (size_t j = 0; j < rows; ++j) {
                std::cout << harmonies[i * rows + j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
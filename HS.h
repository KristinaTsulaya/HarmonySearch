#include <vector>
#include <cfloat>
#include "_random.h"

class HS {
private:
    size_t cols, rows; // --- |||
    size_t size;

    double max;
    double min;

    std::vector<double> harmonies;
    std::vector<double> tmp_harmony;

    size_t worst_position = 0;
    size_t best_position = 0;

    double fitness_worst;
    double fitness_best;
    std::vector<double> val;

public:
    struct adjusters {
    public:
        double r_pa = 0.5;
        double r_accept = 0.95;

        double e = _random::distributions::uniform_real(-1, 1); // uniform
        double bandwidth = 0.1;
    };

    adjusters adjusters;

public:
    HS(double _min, double _max, size_t _cols, size_t _rows) {
        min = _min;
        max = _max;

        cols = _cols;
        rows = _rows;
        size = cols * rows;

        harmonies.resize(size);
        tmp_harmony.resize(rows);
        val.resize(cols);

        gen_rand_harmonies();
        for (size_t i = 0; i < cols; ++i) {
            double fitness_tmp_val = fitness(harmonies[i * rows + 0], harmonies[i * rows + 1]);
            val[i] = fitness_tmp_val;
        }

        fitness_best = *std::min_element(val.begin(), val.end());
        fitness_worst = *std::max_element(val.begin(), val.end());

        best_position = std::distance(std::begin(val), std::min_element(val.begin(), val.end()));
        worst_position = std::distance(std::begin(val), std::max_element(val.begin(), val.end()));
    }

    void gen_rand_harmonies() {
        for (size_t i = 0; i < harmonies.size(); ++i) {
            harmonies[i] = min + _random::distributions::uniform_real(0, 1) * (max - min);
        }
    }

    double fitness(double x, double y) {
//        return log(1 + pow(1 - x, 2) + 100 * pow(y - pow(x, 2), 2)); // fx min at (1, 1)
//        return pow(1 - x, 2) + 100 * pow(y - pow(x, 2), 2);
        return -sin(x) * pow(sin(pow(x, 2) / 3.14 ), 20) - sin(y) * pow(sin(2 * pow(y, 2) / 3.14 ), 20);
    }

    double find_best(size_t cur_iter, size_t max_iter) {
        for (size_t j = 0; j < rows; ++j) {
            int i = _random::distributions::uniform_int(0, cols - 1);
            double rand_value = _random::distributions::uniform_real(0, 1);

            if (rand_value < adjusters.r_accept) {
                tmp_harmony[j] = harmonies[i * rows + j];
                rand_value = _random::distributions::uniform_real(0, 1);
                if (rand_value < adjusters.r_pa) {
                    adjusters.bandwidth = 0.5 + ((0.6 - 0.5) / double(max_iter - 1)) * double(cur_iter - 1);
                    tmp_harmony[j] = tmp_harmony[j] + (2 * _random::distributions::bernoulli(0.5) - 1) * adjusters.bandwidth *
                                                              _random::distributions::normal_double(0, 1);
                }
            }
            else {
                tmp_harmony[j] = min + (max - min) * _random::distributions::uniform_real(0, 1);
            }
        }

        for (size_t i = 0; i < cols; ++i) {
            double fitness_tmp_val = fitness(harmonies[i * rows + 0], harmonies[i * rows + 1]);
            val[i] = fitness_tmp_val;
        }
        fitness_worst = *std::max_element(val.begin(), val.end());
        worst_position = std::distance(std::begin(val), std::max_element(val.begin(), val.end()));

        double fitness_tmp = fitness(tmp_harmony[0], tmp_harmony[1]);
        if (fitness_tmp < fitness_worst) {
            for (size_t j = 0; j < rows; ++j) {
                harmonies[worst_position * rows + j] = tmp_harmony[j];
            }
        }

        for (size_t i = 0; i < cols; ++i) {
            double fitness_tmp_val = fitness(harmonies[i * rows + 0], harmonies[i * rows + 1]);
            val[i] = fitness_tmp_val;
        }

        fitness_best = *std::min_element(val.begin(), val.end());
        best_position = std::distance(std::begin(val), std::min_element(val.begin(), val.end()));

        return fitness_best;
    }

    void print_val(std::ofstream& out){
        out << "Solution (x, y): " << harmonies[best_position * rows + 0] << " " << harmonies[best_position * rows + 1] << std::endl;
    }
};
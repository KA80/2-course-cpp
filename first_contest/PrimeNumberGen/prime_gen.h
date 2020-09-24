#include <iostream>
#include <vector>
#include <cmath>

class PrimeNumberGenerator {
    int cur_num;

 public:
    explicit PrimeNumberGenerator(int start) {
        this->cur_num = start;
    }

    int GetNextPrime() {
        int next_prime_num;
        bool is_prime = false;
        std::vector<int> prime_nums;

        while (!is_prime) {
            int counter = 0;
            for (int i = 2; i <= floor(sqrt(cur_num)); i++) {
                if (cur_num % i == 0) {
                    counter++;
                }
                if (counter) {
                    break;
                }
            }
            if (!counter && cur_num > 1) {
                is_prime = true;
            } else {
                cur_num++;
            }
        }

        next_prime_num = cur_num++;
        return next_prime_num;
    }
};

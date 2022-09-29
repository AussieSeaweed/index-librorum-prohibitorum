#include <cmath>

bool f(int N) {
    int factor = std::sqrt(N);
    return factor * factor == N;
}
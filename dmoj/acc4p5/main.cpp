#include <cmath>

bool f(int N) {
    if (N == 1)
        return false;

    for (int i = 2, m = std::sqrt(N); i <= m; ++i)
        if (N % i == 0)
            return false;

    return true;
}
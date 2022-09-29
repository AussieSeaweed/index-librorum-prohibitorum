#include <iostream>

unsigned int A[100], B[100], C[100], D[100], n;

int main() {
    std::cin >> n;

    for (unsigned int i = 0; i < n; ++i) {
        unsigned int a, b;
        std::cin >> a >> b;
        ++A[--a], ++B[--b];

        std::copy(A, A + 100, C);
        std::copy(B, B + 100, D);

        unsigned int c = 0, d = 99, maximalSum = 0;

        while (c < 100 && d >= 0) {
            if (!C[c]) {
                ++c;
                continue;
            } else if (!D[d]) {
                --d;
                continue;
            }

            maximalSum = std::max(maximalSum, c + d);

            unsigned int m = std::min(C[c], D[d]);
            C[c] -= m;
            D[d] -= m;
        }

        std::cout << maximalSum + 2 << std::endl;
    }

    return 0;
}
#include <iostream>
#include <bitset>

std::bitset<1000000> dp[2][20], A;
unsigned int n, q;

void setup() {
    for (unsigned int i = 0; i < n; ++i) {
        dp[0][0][i] = !A[i];
        dp[1][0][i] = false;
    }

    for (unsigned int j = 1; j < 20; ++j) {
        for (unsigned int i = 0; i + (1 << j) <= n; ++i) {
            dp[0][j][i] = dp[dp[0][j - 1][i]][j - 1][i + (1 << (j - 1))];
            dp[1][j][i] = dp[dp[1][j - 1][i]][j - 1][i + (1 << (j - 1))];
        }
    }
}

bool query(unsigned int begin, unsigned int end, bool init) {
    for (int j = 19; j >= 0; --j) {
        if (begin + (1 << j) <= end) {
            init = dp[init][j][begin];
            begin += 1 << j;
        }
    }

    return init;
}

int main() {
    std::cin >> n;

    for (unsigned int i = 0; i < n; ++i) {
        bool a; std::cin >> a;
        A[i] = a;
    }

    setup();

    std::cin >> q;

    while (q--) {
        unsigned int x, y;
        std::cin >> x >> y;

        std::cout << query(x, y, A[x - 1]) << std::endl;
    }

    return 0;
}
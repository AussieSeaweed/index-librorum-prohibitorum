#include <iostream>

int N, M;
std::string str;
unsigned long long int bases[22501], hash[22501];

void precomputeHash() {
    for (int i = bases[0] = 1; i <= str.size(); ++i) {
        bases[i] = bases[i - 1] * 29;
        hash[i] = hash[i - 1] + (str[i - 1] - '0' + 1) * bases[i];
    }
}

bool equals(int b1, int b2, int n) {
    if (b1 > b2) std::swap(b1, b2);

    unsigned long long int h1 = hash[b1 + n] - hash[b1], h2 = hash[b2 + n] - hash[b2];

    return h1 * bases[b2 - b1] == h2;
}

double solve() {
    for (int i = M / 2; i >= 1; --i) {
        if (M % i == 0) {
            bool flag = false;

            for (int j = i; j < M; j += i) {
                if (!equals(j - i, j, i)) {
                    flag = true;
                    break;
                }
            }

            if (!flag)
                return (double) i * i / M;
        }
    }
}

int main() {
    std::cin >> N;

    double maxComplexity = 0;

    while (N--) {
        std::cin >> M >> str;

        precomputeHash();
        maxComplexity = std::max(maxComplexity, solve());
    }

    std::cout << maxComplexity << std::endl;

    return 0;
}
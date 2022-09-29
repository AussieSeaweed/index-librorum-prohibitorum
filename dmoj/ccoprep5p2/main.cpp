#include <iostream>

int T, N, sums[20001], roots[20001];

std::pair<int, int> query(int i) {
    if (i != roots[i]) {
        auto[sum, root] = query(roots[i]);
        sums[i] += sum;
        roots[i] = root;
    }

    return std::make_pair(sums[i], roots[i]);
}

void update(int from, int to) {
    sums[from] = std::abs(to - from) % 1000;
    roots[from] = to;
}

int main() {
    std::cin >> T;

    while (T--) {
        std::cin >> N;

        std::fill(sums + 1, sums + N + 1, 0);

        for (int i = 1; i <= N; ++i)
            roots[i] = i;

        char symbol;

        do {
            std::cin >> symbol;

            switch (symbol) {
                case 'E': {
                    int I;
                    std::cin >> I;
                    std::cout << query(I).first << std::endl;
                    break;
                }
                case 'I': {
                    int I, J;
                    std::cin >> I >> J;
                    update(I, J);
                    break;
                }
                default:
                    break;
            }
        } while (symbol != 'O');
    }

    return 0;
}
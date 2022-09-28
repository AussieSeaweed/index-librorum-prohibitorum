#include <iostream>

int N, M, harmonies[100000], disturbances[100000], dp[100000][2];

int main() {
    std::cin >> N;

    for (int i = 0; i < N; ++i)
        std::cin >> harmonies[i];

    std::cin >> M;

    for (int i = 0; i < M; ++i) {
        int index;
        std::cin >> index >> disturbances[index - 1];
    }

    dp[0][0] = 0;
    dp[0][1] = harmonies[0];

    for (int i = 1; i < N; ++i) {
        dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][1] = harmonies[i] + std::max(dp[i - 1][0], dp[i - 1][1] - disturbances[i - 1]);
    }

    std::cout << std::max(dp[N - 1][0], dp[N - 1][1]) << std::endl;

    return 0;
}

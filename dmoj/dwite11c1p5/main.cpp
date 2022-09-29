#include <iostream>
#include <cstring>

std::string str;
int dp[256][256];

int solve(int i, int j) {
    if (i > j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (i == j) return dp[i][j] = 1;
    if (i == j - 1 && str[i] == str[j]) return dp[i][j] = 2;
    if (str[i] == str[j]) return dp[i][j] = 2 + solve(i + 1, j - 1);
    return dp[i][j] = std::max(solve(i + 1, j), solve(i, j - 1));
}

int main() {
    for (int _ = 0; _ < 5; _++) {
        memset(dp, -1, sizeof dp);
        std::cin >> str;
        printf("%d\n", solve(0, str.size() - 1));
    }
    return 0;
}
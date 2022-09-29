#include <iostream>
#include <vector>
#define INFINITY 99999999
using namespace std;

vector<int> num(1000);
vector<int> tm(1000);
vector<vector<int>> dp(1000, vector<int>(1000, -1));
int C, M;

int main() {
    scanf("%d%d", &C, &M);

    for (int i = 0; i < C; i++) {
        scanf("%d%d", &num[i], &tm[i]);
    }

    int solution = 0;

    for (int i = 0; i < C; i++) {
        dp[i][0] = 0;
    }

    for (int t = 1; t <= M; t++) {
        dp[0][t] = t - tm[0] == 0 ? num[0] : -INFINITY;
        solution = max(solution, dp[0][t]);
        for (int i = 1; i < C; i++) {
            dp[i][t] = max(dp[i - 1][t], t - tm[i] >= 0 ? num[i] + dp[i - 1][t - tm[i]] : -INFINITY);
            solution = max(solution, dp[i][t]);
        }
    }

    printf("%d", solution);
    return 0;
}
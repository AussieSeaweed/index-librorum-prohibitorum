#include <iostream>
#include <vector>

using namespace std;

int dp[2][5000];
char str[5001];
int N;

int main() {
    scanf("%d %s", &N, str);

    for (int i = 0; i < N; i++)
        dp[0][i] = 0;

    for (int i = 0; i < N - 1; i++) {
        if (str[i] == str[i + 1])
            dp[1][i] = 0;
        else
            dp[1][i] = 1 + min(dp[0][i], dp[0][i + 1]);
    }

    for (int offset = 2; offset < N; offset++) {
        for (int i = 0; i < N - offset; i++) {
            if (str[i] == str[i + offset]) {
                dp[offset & 1][i] = dp[offset & 1][i + 1];
            } else {
                dp[offset & 1][i] = 1 + min(dp[(offset - 1) & 1][i], dp[(offset - 1) & 1][i + 1]);
            }
        }
    }

    printf("%d", dp[(N - 1) & 1][0]);
    return 0;
}
#include <iostream>
using namespace std;

int dp[1001][1001];
int a[1001];
int b[1001];
int na, nb;

int main() {
    scanf("%d%d", &na, &nb);
    for (int i = 0; i < na; i++) {
        scanf("%d", a + i + 1);
    }
    for (int i = 0; i < nb; i++) {
        scanf("%d", b + i + 1);
    }
    for (int i = 1; i <= na; i++) {
        for (int j = 1; j <= nb; j++) {
            if (a[i] == b[j]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    printf("%d", dp[na][nb]);
    return 0;
}
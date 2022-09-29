#include <iostream>
#include <cstring>
using namespace std;

int d, i, r;
string a, b;
int dp[1000][1000];

int main() {
    memset(dp, -1, sizeof dp);
    scanf("%d%d%d", &d, &i, &r);
    cin >> a >> b;
    for (int m = 0; m <= a.size(); m++) {
        for (int n = 0; n <= b.size(); n++) {
            if (m == 0) dp[m][n] = i * n;
            else if (n == 0) dp[m][n] = d * m;
            else if (a[m - 1] == b[n - 1]) dp[m][n] = dp[m - 1][n - 1];
            else dp[m][n] = min(i + dp[m][n - 1], min(d + dp[m - 1][n], r + dp[m - 1][n - 1]));
        }
    }
    printf("%d", dp[a.size()][b.size()]);
    return 0;
}
#include <iostream>
#define inf 999999999
using namespace std;

bool dp[2][11000000];
int num[110], value[110], N, sum = 0, sumd2, count[11000000];

void solve() {
    dp[1][0] = true;
    int highest = 0;

    for (int n = 0; n < N; n++) {
        int h = n & 1, ph = !h;
        highest = min(sum, min(sumd2, highest) + num[n] * value[n]);
        fill(count, count + sum + 1, 0);
        int limit = highest;
        for (int i = 0; i < value[n]; i++) {
            dp[h][i] = dp[ph][i];
        }

        for (int i = value[n]; i <= limit; i++) {
            dp[h][i] = dp[ph][i];

            if (dp[h][i - value[n]] && count[i - value[n]] < num[n]) {
                dp[h][i] = true;
                count[i] = count[i - value[n]] + 1;
            }

            if (dp[ph][i]) {
                count[i] = 0;
            } else if (dp[ph][i - value[n]]) {
                dp[h][i] = true;
                count[i] = 1;
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", num + i, value + i);
        sum += value[i] * num[i];
    }
    sumd2 = sum / 2;
    solve();
    int min_dif = inf, h = (N - 1) & 1;
    for (int i = sumd2; i >= 0; i--)
        if (dp[h][i]) {
            min_dif = sumd2 - i;
            break;
        }
    for (int i = sumd2 + 1; i <= sum; i++)
        if (dp[h][i]) {
            min_dif = min(min_dif, i - sumd2);
            break;
        }
    printf("%d", min_dif * 2 + sum % 2);
    return 0;
}
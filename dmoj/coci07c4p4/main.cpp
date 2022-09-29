#include <iostream>

int T, N, sum, t[500], prev[10000], start[500];
bool dp[2][10000], used[500];

void solve() {
    std::fill(std::begin(prev), std::end(prev), -1);
    dp[1][0] = true;

    for (int n = 0; n < N; n++) {
        int h = n & 1, ph = !h;
        for (int i = 0; i < std::min(sum, t[n]); i++) {
            dp[h][i] = dp[ph][i];
        }

        for (int i = t[n]; i <= sum; i++) {
            dp[h][i] = dp[ph][i];

            if (!dp[h][i] && dp[ph][i - t[n]]) {
                dp[h][i] = true;
                prev[i] = n;
            }
        }
    }
}

int main() {
    scanf("%d%d", &T, &N);
    sum = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", t + i);
        sum += t[i];
    }
    solve();
    int fsum = 0, h = (N - 1) & 1;

    for (int i = sum / 2; i >= 0; i--) {
        if (dp[h][i]) {
            fsum = i;
            break;
        }
    }

    int ptime = fsum;
    int node = prev[fsum];

    while (node != -1) {
        start[node] = ptime - t[node];
        ptime = start[node];
        used[node] = true;
        node = prev[start[node]];
    }

    ptime = 0;

    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            start[i] = ptime;
            ptime += t[i];
        }
    }

    for (int i = 0; i < N; i++)
        printf("%d ", start[i]);
    return 0;
}
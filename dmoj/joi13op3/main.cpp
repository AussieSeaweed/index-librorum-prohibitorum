#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, P, Q, pos[2001];
int dp[2002][2002];

bool works(int w) {
    for (int i = 0; i <= P + 1; i++)
        fill(dp[i], dp[i] + Q + 2, -1);

    for (int p = 0; p <= P; p++) {
        for (int q = 0; q <= Q; q++) {
            int cur = dp[p][q];
            dp[p + 1][q] = max(dp[p + 1][q], (int) (upper_bound(pos + cur + 1, pos + N, pos[cur + 1] + w - 1) - pos - 1));
            dp[p][q + 1] = max(dp[p][q + 1], (int) (upper_bound(pos + cur + 1, pos + N, pos[cur + 1] - 1 + w * 2) - pos - 1));
        }
    }

    for (int p = 0; p <= P; p++) {
        for (int q = 0; q <= Q; q++) {
            if (dp[p][q] == N - 1) return true;
        }
    }

    return false;
}

int main() {
    scan(N);
    scan(P);
    scan(Q);

    if (P + Q >= N) {
        printf("1\n");
        return 0;
    }

    for (int i = 0; i < N; i++)
        scan(pos[i]);

    sort(pos, pos + N);

    int lo = 1, hi = 1000000000;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (works(mid)) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d\n", lo);

    return 0;
}
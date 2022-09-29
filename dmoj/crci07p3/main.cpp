#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, M, x[100], y[100], sm[100], pm[100], sv[100], pv[100];

int required(int s) {
    int ret = 0;

    for (int i = 0; i < N; i++) {
        int lim = (s * x[i] - y[i]) / sv[i] + ((bool) ((s * x[i] - y[i]) % sv[i])), cur = inf;
        for (int j = 0; j <= lim; j++) {
            int rem = max(0, (s * x[i] - y[i]) - j * sv[i]);
            cur = min(cur, j * pv[i] + pm[i] * (rem / sm[i]) + pm[i] * ((bool) (rem % sm[i])));
        }
        ret += cur;
    }

    return ret;
}

int main() {
    scan(N);
    scan(M);

    for (int i = 0; i < N; i++) {
        scan(x[i]);
        scan(y[i]);
        scan(sm[i]);
        scan(pm[i]);
        scan(sv[i]);
        scan(pv[i]);
    }

    int lo = 0, hi = 100000;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (required(mid) <= M) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    printf("%d\n", lo - 1);

    return 0;
}
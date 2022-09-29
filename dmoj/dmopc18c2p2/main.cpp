#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

vector<int> rows;
int M, N, K, heights[200000];

int main() {
    scan(M);
    scan(N);
    scan(K);

    for (int i = 0; i < K; i++)
        scan(heights[i]);

    sort(heights, heights + K);

    rows.resize(M);

    long long ans = 0;

    int lo = 0, hi = K - 1, r = 0;

    while (lo <= hi) {
        if (r == 0) {
            rows[r] = heights[hi--];
        } else {
            rows[r] = heights[lo++];
        }
        if (r != 0) {
            ans += rows[r - 1] - rows[r] + 1;
            rows[r] = rows[r - 1] + 1;
        }
        if (++r == M) {
            r = 0;
        }
    }

    printf("%lld\n", ans);

    return 0;
}
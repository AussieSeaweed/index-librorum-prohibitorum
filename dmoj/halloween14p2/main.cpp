#include <iostream>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
using namespace std;

int N, n;
long long W;
long long width[500001], cuteness[500001];
long long dp[500001][2];

int main() {
    scan(N);
    scan(W);
    n = 0;

    while (N--) {
        char t;
        scanf(" %c", &t);

        if (t == 'A') {
            long long p, c;
            scan(p);
            scan(c);
            width[++n] = p + width[n - 1];
            cuteness[n] = c + cuteness[n - 1];
            int i = lower_bound(width, width + n + 1, width[n] - W) - width;
            dp[n][0] = cuteness[n] - cuteness[i];
            dp[n][1] = max(dp[n][0], dp[n - 1][1]);
            printf("%lld\n", dp[n][1]);
        } else
            --n;
    }

    return 0;
}
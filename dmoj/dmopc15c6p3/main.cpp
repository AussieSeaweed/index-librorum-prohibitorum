#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, M;
long long K, num[200002];

int main() {
    scan(N);
    scan(M);
    scan(K);

    num[0] = M;

    for (int i = 1; i <= M; i++) {
        int a, b;
        scan(a);
        scan(b);

        num[a]--;
        num[b + 1]++;
    }

    for (int i = 1; i <= N; i++) {
        num[i] += num[i - 1];
    }

    num[0] = 0;

    for (int i = 1; i <= N; i++) {
        num[i] += num[i - 1];
    }

    int l = 0, ans = inf;

    for (int r = 1; r <= N; r++) {
        while (l <= r && num[r] - num[l] >= K) {
            ans = min(ans, r - l++);
        }
    }

    printf("%d\n", ans == inf ? -1 : ans);

    return 0;
}
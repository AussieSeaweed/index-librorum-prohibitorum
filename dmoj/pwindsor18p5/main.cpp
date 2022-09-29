#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
#define MOD 1000000007
using namespace std;

int N;

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scan(N);

    int delta;
    long long ans = 1;

    while (true) {
        if (N <= 3) {
            ans = ans * max(1, N) % MOD;
            break;
        } else {
            delta = (N - 1) % 3 == 0 ? 4 : 3;
            ans = ans * delta % MOD;
            N -= delta;
        }
    }

    printf("%lld\n", ans);

    return 0;
}
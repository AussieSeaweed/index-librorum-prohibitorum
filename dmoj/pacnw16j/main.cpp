#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

long long st[200001][18], N, Q;
int cache[200001];

inline long long query(int l, int r) {
    int len = cache[r - l + 1];
    return min(st[l][len],  st[r - (1 << len) + 1][len]);
}

int main() {
    scan(N);
    scan(Q);

    cache[1] = 0;

    for (int i = 2; i <= N; i++)
        cache[i] = 1 + cache[i / 2];

    for (int i = 1; i <= N; i++)
        scan(st[i][0]);

    for (int j = 1; j < 18; j++)
        for (int i = 1; i + (1 << j) - 1 <= N; i++)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);

    long long v;
    int l, r;

    while (Q--) {
        scan(v);
        scan(l);
        scan(r);

        while (l <= r && query(l, r) <= v) {
            int ml = l, mr = r;
            while (ml <= mr) {
                int mmid = ml + (mr - ml) / 2;
                if (query(ml, mmid) <= v) {
                    mr = mmid - 1;
                } else {
                    ml = mmid + 1;
                }
            }
            if (ml <= r) {
                v %= st[ml][0];
                l = ml + 1;
            } else {
                break;
            }
        }

        printf("%lld\n", v);
    }

    return 0;
}
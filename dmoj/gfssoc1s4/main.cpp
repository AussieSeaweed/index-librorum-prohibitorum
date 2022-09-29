#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

unsigned long long bit[251][251][251], value[251][251][251], N, Q;

void update(int x, int y, int z, unsigned long long delta) {
    for (int i = x; i <= N; i += i & -i)
        for (int j = y; j <= N; j += j & -j)
            for (int k = z; k <= N; k += k & -k)
                bit[i][j][k] += delta;
}

unsigned long long query(int x, int y, int z) {
    unsigned long long ret = 0;

    for (int i = x; i; i -= i & -i)
        for (int j = y; j; j -= j & -j)
            for (int k = z; k; k -= k & -k)
                ret += bit[i][j][k];

    return ret;
}

int main() {
    scan(N);
    scan(Q);

    unsigned long long ans = 0;

    while (Q--) {
        char t;
        scanf(" %c", &t);

        switch (t) {
            case 'C': {
                int x, y, z; unsigned long long l, delta;
                scan(x);
                scan(y);
                scan(z);
                scan(l);
                delta = l - value[x][y][z];
                value[x][y][z] = l;
                update(x, y, z, delta);
            }
                break;
            case 'S': {
                int x1, y1, z1, x2, y2, z2;
                scan(x1);
                scan(y1);
                scan(z1);
                scan(x2);
                scan(y2);
                scan(z2);
                ans += query(x2, y2, z2) - query(x1 - 1, y2, z2) - query(x2, y1 - 1, z2) - query(x2, y2, z1 - 1) - query(x1 - 1, y1 - 1, z1 - 1)
                        + query(x1 - 1, y2, z1 - 1) + query(x2, y1 - 1, z1 - 1) + query(x1 - 1, y1 - 1, z2);
            }
                break;
            default: break;
        }
    }

    printf("%llu\n", ans);

    return 0;
}
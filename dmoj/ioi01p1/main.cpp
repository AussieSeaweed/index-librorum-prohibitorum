#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int S, bit[1025][1025];

void update(int r, int c, long long delta) {
    for (int i = r; i <= S; i += i & -i)
        for (int j = c; j <= S; j += j & -j)
            bit[i][j] += delta;
}

long long query(int r, int c) {
    long long ret = 0;
    for (int i = r; i; i -= i & -i)
        for (int j = c; j; j -= j & -j)
            ret += bit[i][j];
    return ret;
}

int main() {
    bool run = true;

    while (run) {
        int type;
        scan(type);

        switch (type) {
            case 0: {
                scanf("%d", &S);
            }
                break;
            case 1: {
                int x, y;
                long long a;
                scanf("%d%d%lld", &x, &y, &a);
                ++x;
                ++y;
                update(x, y, a);
            }
                break;
            case 2: {
                int l, b, r, t;
                scanf("%d%d%d%d", &l, &b, &r, &t);
                ++l;
                ++b;
                ++r;
                ++t;
                printf("%lld\n", query(r, t) - query(l - 1, t) - query(r, b - 1) + query(l - 1, b - 1));
            }
                break;
            case 3: {
                run = false;
            }
                break;
            default: break;
        }
    }
    return 0;
}
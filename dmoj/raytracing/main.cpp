#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int height[8193], st[8193][8193], N, Q;

void update(int r, int c, int delta) {
    for (; r <= N; r += r & -r)
        for (int i = c; i <= N; i += i & -i)
            st[r][i] += delta;
}

int query(int r, int c) {
    int ret = 0;

    for (; r; r -= r & -r)
        for (int i = c; i; i -= i & -i)
            ret += st[r][i];

    return ret;
}

int main() {
    scan(N);

    for (int i = 1; i <= N; i++) {
        scan(height[i]);
        height[i]++;
        update(i, height[i], 1);
    }

    scan(Q);

    while (Q--) {
        int t;
        scan(t);

        switch (t) {
            case 1: {
                int i, j, a, b;
                scan(i);
                scan(j);
                scan(a);
                scan(b);
                i++, j++, a++, b++;
                printf("%d\n", query(j, b) - query(i - 1, b) - query(j, a - 1) + query(i - 1, a - 1));
            }
                break;
            default: {
                int i, h;
                scan(i);
                scan(h);
                i++, h++;
                update(i, height[i], -1);
                height[i] = h;
                update(i, height[i], 1);
            }
                break;
        }
    }

    return 0;
}
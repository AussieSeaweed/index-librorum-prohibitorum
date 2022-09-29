#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

const int MAX_NODE = 100000;
long long sum[MAX_NODE + 1], cnt[100001];

void update(long long bit[], int index, long long delta) {
    while (index <= MAX_NODE) {
        bit[index] += delta;
        index += index & -index;
    }
}

long long query(const long long bit[], int index) {
    long long ret = 0;
    while (index) {
        ret += bit[index];
        index -= index & -index;
    }
    return ret;
}

long long range(const long long bit[], int l, int r) {
    return query(bit, r) - query(bit, l - 1);
}

long long single(const long long bit[], int index) {
    return query(bit, index) - query(bit, index - 1);
}

int N, M;

int main() {
    scan(N);
    scan(M);

    for (int i = 1; i <= N; i++) {
        int value;
        scan(value);
        update(sum, i, value);
        update(cnt, value, 1);
    }

    while (M--) {
        char t;
        scanf(" %c", &t);

        switch (t) {
            case 'C': {
                int x, v;
                scan(x);
                scan(v);
                long long original = single(sum, x);
                update(sum, x, v - original);
                update(cnt, v, 1);
                update(cnt, original, -1);
            }
                break;
            case 'S': {
                int l, r;
                scan(l);
                scan(r);
                printf("%lld\n", range(sum, l, r));
            }
                break;
            case 'Q': {
                int v;
                scan(v);
                printf("%lld\n", query(cnt, v));
            }
                break;
        }
    }

    return 0;
}
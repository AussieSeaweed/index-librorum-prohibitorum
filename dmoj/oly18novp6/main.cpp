#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, M, root[100001], values[100000], bsize = 316;
long long blocks[317];

int get_next(int i) {
    return root[i] == i ? i : root[i] = get_next(root[i]);
}

inline void update(int l, int r) {
    for (int i = get_next(l); i <= r; i = get_next(i + 1)) {
        int delta = ((int) sqrt(values[i])) - values[i];
        values[i] += delta;
        blocks[i / bsize] += delta;
        if (values[i] <= 1)
            root[i] = get_next(root[i + 1]);
    }
}

inline long long query(int l, int r) {
    long long ret = 0;
    int lb = l / bsize, rb = r / bsize;
    if (lb == rb) {
        for (int i = l; i <= r; i++) {
            ret += values[i];
        }
    } else {
        for (int i = l, lim = (lb + 1) * bsize; i < lim; i++) {
            ret += values[i];
        }
        for (int i = lb + 1; i < rb; i++) {
            ret += blocks[i];
        }
        for (int i = bsize * rb; i <= r; i++) {
            ret += values[i];
        }
    }
    return ret;
}

int main() {
    scan(N);
    for (int i = 0; i < N; i++) {
        root[i] = i;
        scan(values[i]);
        blocks[i / bsize] += values[i];
    }
    root[N] = N;
    for (int i = N - 1; i >= 0; i--)
        if (values[i] == 1)
            root[i] = get_next(i + 1);
    scan(M);
    while (M--) {
        int x, l, r;
        scan(x);
        scan(l);
        scan(r);
        --l, --r;

        if (x == 1) {
            printf("%lld\n", query(l, r));
        } else {
            update(l, r);
        }
    }
    return 0;
}
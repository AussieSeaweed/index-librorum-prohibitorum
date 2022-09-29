#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

long long N, Q, a[200000];
long long *elems[524288], *prefix_sum[524288];

inline void build_seg_tree(int node, int lo, int hi) {
    if (lo == hi) {
        elems[node] = new long long[1] { a[lo] };
        prefix_sum[node] = new long long[1] { a[lo] };
    } else {
        int mid = (lo + hi) >> 1;
        build_seg_tree(node << 1, lo, mid);
        build_seg_tree(node << 1 | 1, mid + 1, hi);
        int size = hi - lo + 1;
        elems[node] = new long long[size];
        prefix_sum[node] = new long long[size];
        merge(elems[node << 1], elems[node << 1] + (mid - lo + 1), elems[node << 1 | 1], elems[node << 1 | 1] + (hi - mid), elems[node]);
        copy(elems[node], elems[node] + size, prefix_sum[node]);
        for (int i = 1; i < size; i++) {
            prefix_sum[node][i] += prefix_sum[node][i - 1];
        }
    }
}

inline long long query(int node, int lo, int hi, int left, int right, long long k) {
    if (right < lo || hi < left) return 0;
    if (left <= lo && hi <= right) {
        int index = lower_bound(elems[node], elems[node] + (hi - lo + 1), k) - elems[node];
        if (index > 0) {
            return prefix_sum[node][hi - lo] - prefix_sum[node][index - 1] - prefix_sum[node][index - 1];
        } else {
            return prefix_sum[node][hi - lo];
        }
    }

    int mid = (lo + hi) >> 1;

    return query(node << 1, lo, mid, left, right, k) + query(node << 1 | 1, mid + 1, hi, left, right, k);
}

int main() {
    pscan(N);
    pscan(Q);

    for (int i = 0; i < N; i++)
        pscan(a[i]);

    build_seg_tree(1, 0, N - 1);

    while (Q--) {
        long long l, r, k;
        pscan(l);
        pscan(r);
        pscan(k);
        l--, r--;
        printf("%lld\n", query(1, 0, N - 1, l, r, k));
    }

    return 0;
}
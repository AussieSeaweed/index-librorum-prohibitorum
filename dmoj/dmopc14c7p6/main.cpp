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

int N, seg_tree[262144], lazy[262144], values[100000];

void handle_lazy(int node, int lo, int hi) {
    if (lazy[node]) {
        seg_tree[node] += lazy[node];

        if (lo != hi) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        lazy[node] = 0;
    }
}

void update(int node, int lo, int hi, int left, int right, int delta) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return;
    if (left <= lo && hi <= right) {
        lazy[node] += delta;
        handle_lazy(node, lo, hi);
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, left, right, delta);
        update(node * 2 + 1, mid + 1, hi, left, right, delta);
        seg_tree[node] = max(seg_tree[node * 2], seg_tree[node * 2 + 1]);
    }
}

int query(int node, int lo, int hi, int left, int right) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return -inf;
    if (left <= lo && hi <= right) return seg_tree[node];

    int mid = (lo + hi) / 2, lq = query(node * 2, lo, mid, left, right), rq = query(node * 2 + 1, mid + 1, hi, left, right);

    return max(lq, rq);
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++)
        scan(values[i]);

    int ans = 0;

    for (int i = 0, j = 1; j < N; i++, j += 2) {
        if (j == 1) {
            update(1, 1, N, values[i], N, 1);
            update(1, 1, N, values[j], N, -1);
        } else {
            update(1, 1, N, values[i], N, 2);
            update(1, 1, N, values[j - 1], N, -1);
            update(1, 1, N, values[j], N, -1);
        }

        if (!query(1, 1, N, 1, N))
            ans = i + 1;
    }

    printf("%d\n", ans);

    return 0;
}
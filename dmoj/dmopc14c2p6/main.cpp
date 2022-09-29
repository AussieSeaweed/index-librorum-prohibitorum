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

int N, Q, m[100000];
vector<int> elems[262144], prefix_sum[262144];

void build_tree(int node, int lo, int hi) {
    if (lo == hi) {
        elems[node].push_back(m[lo]);
        prefix_sum[node].push_back(m[lo]);
    } else {
        int mid = (lo + hi) / 2;
        build_tree(node * 2, lo, mid);
        build_tree(node * 2 + 1, mid + 1, hi);
        merge(elems[node * 2].begin(), elems[node * 2].end(), elems[node * 2 + 1].begin(), elems[node * 2 + 1].end(), back_inserter(elems[node]));
        copy(elems[node].begin(), elems[node].end(), back_inserter(prefix_sum[node]));
        for (int i = 1; i < prefix_sum[node].size(); i++) prefix_sum[node][i] += prefix_sum[node][i - 1];
    }
}

int query(int node, int lo, int hi, int left, int right, int q) {
    if (right < lo || hi < left) return 0;
    if (left <= lo && hi <= right) {
        int index = lower_bound(elems[node].begin(), elems[node].end(), q) - elems[node].begin();
        return prefix_sum[node].back() - (index ? prefix_sum[node][index - 1] : 0);
    }

    int mid = (lo + hi) / 2;

    return query(node * 2, lo, mid, left, right, q) + query(node * 2 + 1, mid + 1, hi, left, right, q);
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) scan(m[i]);

    build_tree(1, 0, N - 1);

    scan(Q);

    while (Q--) {
        int a, b, q;
        scan(a);
        scan(b);
        scan(q);
        printf("%d\n", query(1, 0, N - 1, a, b, q));
    }

    return 0;
}
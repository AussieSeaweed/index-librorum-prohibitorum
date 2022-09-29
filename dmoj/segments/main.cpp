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

struct Node {
    int max_val, lazy;
} ltree[524288], rtree[524288];

int T, N, values[200000];
pair<int, int> segments[200000];
unordered_map<int, int> comp;

void handle_lazy(int node, int lo, int hi, Node seg_tree[]) {
    if (seg_tree[node].lazy) {
        seg_tree[node].max_val += seg_tree[node].lazy;

        if (lo != hi) {
            seg_tree[node * 2].lazy += seg_tree[node].lazy;
            seg_tree[node * 2 + 1].lazy += seg_tree[node].lazy;
        }

        seg_tree[node].lazy = 0;
    }
}

void update(int node, int lo, int hi, int left, int right, int delta, Node seg_tree[]) {
    handle_lazy(node, lo, hi, seg_tree);
    if (right < lo || hi < left) return;

    if (left <= lo && hi <= right) {
        seg_tree[node].lazy += delta;
        handle_lazy(node, lo, hi, seg_tree);
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, left, right, delta, seg_tree);
        update(node * 2 + 1, mid + 1, hi, left, right, delta, seg_tree);
        seg_tree[node].max_val = max(seg_tree[node * 2].max_val, seg_tree[node * 2 + 1].max_val);
    }
}

int query_overall(Node seg_tree[]) {
    handle_lazy(1, 0, 199999, seg_tree);
    return seg_tree[1].max_val;
}

int main() {
    scan(T);
    for (int t = 1; t <= T; t++) {
        scan(N);

        for (int i = 0; i < N; i++) {
            scan(segments[i].first);
            scan(segments[i].second);
            values[i * 2] = segments[i].first, values[i * 2 + 1] = segments[i].second;
        }

        sort(values, values + N * 2);

        for (int i = 0; i < 2 * N; i++) {
            comp[values[i]] = i;
        }

        for (int i = 0; i < N; i++) {
            segments[i].first = comp[segments[i].first];
            segments[i].second = comp[segments[i].second];
        }

        for (int i = 0; i < 524288; i++)
            ltree[i].lazy = ltree[i].max_val = rtree[i].lazy = rtree[i].max_val = 0;

        sort(segments, segments + N);

        for (int i = 0; i < N; i++)
            update(1, 0, 199999, segments[i].first, segments[i].second, 1, rtree);

        int ans = query_overall(rtree);

        for (int i = 0; i < N; i++) {
            update(1, 0, 199999, segments[i].first, segments[i].second, 1, ltree);
            update(1, 0, 199999, segments[i].first, segments[i].second, -1, rtree);
            ans = max(ans, query_overall(ltree) + query_overall(rtree));
        }

        printf("Case %d: %d\n", t, ans);
    }
    return 0;
}
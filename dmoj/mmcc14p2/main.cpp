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

int N, M, Q;
char raw_grid[2000][5001];
vector<int> *grid[2000];
pair<vector<int> *, int> seg_tree[4096];

inline int merge(vector<int> *a, vector<int> *b, int bound) {
    int i = 0, j = 0;

    while (i < a->size() && j < b->size() && a->operator[](i) < bound && b->operator[](j) < bound && a->operator[](i) == b->operator[](j)) {
        i++, j++;
    }

    return min(i == a->size() ? M : a->operator[](i), j == b->size() ? M : b->operator[](j), bound);
}

inline void build(int node, int lo, int hi) {
    if (lo == hi) {
        seg_tree[node] = {grid[lo], M};
    } else {
        int mid = (lo + hi) / 2;
        build(node * 2, lo, mid);
        build(node * 2 + 1, mid + 1, hi);
        seg_tree[node].first = seg_tree[node * 2].first;
        seg_tree[node].second = merge(seg_tree[node * 2].first, seg_tree[node * 2 + 1].first, min(seg_tree[node * 2].second, seg_tree[node * 2 + 1].second));
    }
}

inline void update(int node, int lo, int hi, int index) {
    if (index < lo || hi < index) return;

    if (lo == hi) {
        seg_tree[node].first = grid[lo];
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, index);
        update(node * 2 + 1, mid + 1, hi, index);
        seg_tree[node].first = seg_tree[node * 2].first;
        seg_tree[node].second = merge(seg_tree[node * 2].first, seg_tree[node * 2 + 1].first, min(seg_tree[node * 2].second, seg_tree[node * 2 + 1].second));
    }
}

inline pair<vector<int> *, int> query(int node, int lo, int hi, int left, int right) {
    if (right < lo || hi < left) return {{}, -1};
    if (left <= lo && hi <= right) return seg_tree[node];

    int mid = (lo + hi) / 2;
    pair<vector<int> *, int> lq = query(node * 2, lo, mid, left, right), rq = query(node * 2 + 1, mid + 1, hi, left, right);

    if (lq.second == -1 || rq.second == -1) {
        return lq.second == -1 ? rq : lq;
    } else {
        return {lq.first, merge(lq.first, rq.first, min(lq.second, rq.second))};
    }
}

int main() {
    pscan(N);
    pscan(M);

    int one_cnt = 0;

    for (int i = 0; i < N; i++) {
        scanf("%s", raw_grid[i]);
        for (int j = 0; j < M; j++)
            if (raw_grid[i][j] == '1') one_cnt++;
    }

    if (one_cnt <= N * M / 2) {
        for (int i = 0; i < N; i++) {
            grid[i] = new vector<int>();
            for (int j = 0; j < M; j++)
                if (raw_grid[i][j] == '1') grid[i]->push_back(j);
        }
    } else {
        for (int i = 0; i < N; i++) {
            grid[i] = new vector<int>();
            for (int j = 0; j < M; j++)
                if (raw_grid[i][j] == '0') grid[i]->push_back(j);
        }
    }

    build(1, 0, N - 1);

    pscan(Q);

    while (Q--) {
        int i, j;
        pscan(i);
        pscan(j);
        i--, j--;

        printf("%d\n", (j - i + 1) * query(1, 0, N - 1, i, j).second);

        swap(grid[i], grid[j]);
        update(1, 0, N - 1, i);
        update(1, 0, N - 1, j);
    }

    return 0;
}
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

struct Path {
    long long len, num;
    Path(long long len, long long num) : len{ len }, num{ num } {}
};

int N;
vector<int> graph[400001];

pair<Path, Path> dfs(int node, int parent) {
    long long v1 = -1, v2 = -1, n1 = -1, n2 = -1;
    vector<long long> f, s;
    Path dm {-1, -1};
    bool has_children = false;

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        has_children = true;
        pair<Path, Path> p = dfs(adj, node);
        if (p.second.len > dm.len) dm = p.second;
        else if (p.second.len == dm.len) dm.num += p.second.num;
        Path &down = p.first;

        if (down.len > v1) {
            v2 = v1;
            n2 = n1;
            v1 = down.len;
            n1 = down.num;
            s = f;
            f.clear();
            f.push_back(down.num);
        } else if (down.len == v1) {
            n1 += down.num;
            f.push_back(down.num);
        } else if (down.len > v2) {
            v2 = down.len;
            n2 = down.num;
            s.clear();
            s.push_back(down.num);
        } else if (down.len == v2) {
            n2 += down.num;
            s.push_back(down.num);
        }
    }

    if (!has_children) {
        return {{1, 1}, {0, 0}};
    } else if (f.size() >= 2) { // only use from f
        long long ret = 0, sz = 0;

        for (long long val : f) {
            ret += sz * val;
            sz += val;
        }

        return {{v1 + 1, n1}, dm.len > 2 * v1 + 1 ? dm : Path(2 * v1 + 1, ret + (dm.len == 2 * v1 + 1 ? dm.num : 0))};
    } else if (s.empty()) { // only one path down
        return {{v1 + 1, n1}, dm};
    } else { // use both
        return {{v1 + 1, n1}, dm.len > v1 + 1 + v2 ? dm : Path(v1 + 1 + v2, n1 * n2 + (dm.len == v1 + 1 + v2 ? dm.num : 0))};
    }
}

int main() {
    scan(N);

    for (int i = 1; i < N; i++) {
        int u, v;
        scan(u);
        scan(v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    pair<Path, Path> q = dfs(1, -1);

    if (q.first.len == q.second.len) {
        printf("%lld %lld\n", q.first.len, q.first.num + q.second.num);
    } else if (q.second.len > q.first.len) {
        printf("%lld %lld\n", q.second.len, q.second.num);
    } else {
        printf("%lld %lld\n", q.first.len, q.first.num);
    }

    return 0;
}
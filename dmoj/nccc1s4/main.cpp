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

bool visited[1001];
vector<pair<int, pair<int, int>>> graph[1001];
set<int> k_events;
int N, M, K, S, T;

bool dfs(int node, int &k) {
    if (node == T) return true;
    visited[node] = true;

    for (auto &edge : graph[node]) {
        int adj = edge.first, c = edge.second.first, d = edge.second.second;
        if (c <= k && k <= d && !visited[adj]) {
            if (dfs(adj, k))
                return true;
        }
    }

    return false;
}

int main() {
    scan(N);
    scan(M);
    scan(K);
    scan(S);
    scan(T);

    while (M--) {
        int a, b, c, d;
        scan(a);
        scan(b);
        scan(c);
        scan(d);
        graph[a].emplace_back(b, make_pair(c, d));
        k_events.insert(c - 1);
        k_events.insert(d);
    }

    k_events.insert(K);

    long long prev_k = 0;
    long long ans = 0;

    for (int k : k_events) {
        fill(visited, visited + N + 1, false);
        if (dfs(S, k))
            ans += k - prev_k;
        prev_k = k;
    }

    printf("%lld\n", ans);
    return 0;
}
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

int N, M, D, max_depth[3001], min_depth[3001];
long long dist[3001][6000];
bool visited[3001][6000];
vector<long long> m[3001], b[3001];
vector<pair<int, long long>> graph[3001];

int get_max_depth(int node) {
    if (~max_depth[node]) return max_depth[node];
    if (node == 1) return max_depth[node] = 0;

    for (pair<int, long long> &adj_edge : graph[node]) {
        max_depth[node] = max(max_depth[node], 1 + get_max_depth(adj_edge.first));
    }

    return max_depth[node];
}

int get_min_depth(int node) {
    if (~min_depth[node]) return min_depth[node];
    if (node == 1) return min_depth[node] = 0;
    min_depth[node] = inf;

    for (pair<int, long long> &adj_edge : graph[node]) {
        min_depth[node] = min(min_depth[node], 1 + get_min_depth(adj_edge.first));
    }

    return min_depth[node];
}

long long distance(int node, int used) {
    if (visited[node][used]) return dist[node][used];
    visited[node][used] = true;
    if (node == 1) return dist[node][used] = used ? INF : 0;

    dist[node][used] = INF;

    for (pair<int, long long> &adj_edge : graph[node]) {
        long long query = distance(adj_edge.first, used - 1);
        if (query != INF && dist[node][used] > query + adj_edge.second) {
            dist[node][used] = query + adj_edge.second;
        }
    }

    return dist[node][used];
}

int main() {
    scan(N);
    scan(M);
    scan(D);

    while (M--) {
        int u, v;
        long long w;
        scan(u);
        scan(v);
        scan(w);
        graph[v].emplace_back(u, w);
    }

    memset(max_depth, -1, sizeof max_depth);
    memset(min_depth, -1, sizeof min_depth);

    for (int i = 1; i <= N; i++) {
        int lim = get_min_depth(i);
        for (int j = get_max_depth(i); j >= lim; j--) {
            if (distance(i, j) != INF) {
                while (m[i].size() >= 2 && (b[i][b[i].size() - 2] - b[i].back()) * (j - m[i][m[i].size() - 2]) >
                                            (b[i][b[i].size() - 2] - dist[i][j]) * (m[i].back() - m[i][m[i].size() - 2])) {
                    m[i].pop_back();
                    b[i].pop_back();
                }
                m[i].push_back(j);
                b[i].push_back(dist[i][j]);
            }
        }
    }

    long long delta = 0;

    while (D--) {
        long long c;
        int d;
        scan(c);
        scan(d);
        delta += c;

        if (b[d].empty()) {
            printf("Cannot Deliver\n");
        } else {
            int lo = 1, hi = b[d].size() - 1;

            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (m[d][mid - 1] * delta + b[d][mid - 1] > m[d][mid] * delta + b[d][mid]) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }

            printf("%lld\n", m[d][hi] * delta + b[d][hi]);
        }
    }

    return 0;
}
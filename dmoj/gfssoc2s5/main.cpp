#include <iostream>
#include <vector>
#include <cstring>
#define inf 999999999999

using namespace std;

int N, M;
pair<int, int> edges[1500000];
vector<int> graph[500001], igraph[500001], g[500001], topo;
bool visited[500001], relevant[500001];
int loots[500001], ploots[500000], ids[500001], SSC;
long long dp[500001][2], cnt[500001][2];

void topo_sort(int node) {
    visited[node] = true;

    for (int adj : igraph[node])
        if (!visited[adj])
            topo_sort(adj);

    topo.push_back(node);
}

void ptopo_sort(int node) {
    visited[node] = true;

    for (int adj : g[node])
        if (!visited[adj])
            ptopo_sort(adj);

    topo.push_back(node);
}

void set_id(int node, int id) {
    ids[node] = id;

    for (int adj : graph[node])
        if (ids[adj] == -1)
            set_id(adj, id);
}

void kosaraju() {
    memset(visited, false, sizeof visited);
    memset(ids, -1, sizeof ids);
    memset(ploots, 0, sizeof ploots);

    for (int i = 1; i <= N; i++)
        if (!visited[i])
            topo_sort(i);

    SSC = 0;

    while (!topo.empty()) {
        int node = topo.back();
        topo.pop_back();

        if (ids[node] == -1)
            set_id(node, SSC++);
    }

    for (int i = 1; i <= N; i++)
        ploots[ids[i]] += loots[i];

    for (int i = 0; i < M; i++)
        if (ids[edges[i].first] != ids[edges[i].second])
            g[ids[edges[i].first]].push_back(ids[edges[i].second]);

    memset(visited, false, sizeof visited);
    topo.clear();

    for (int i = 0; i < SSC; i++)
        if (!visited[i])
            ptopo_sort(i);
}

void solve() {
    dp[ids[N]][0] = 0;
    dp[ids[N]][1] = ploots[ids[N]];
    cnt[ids[N]][0] = 1;
    cnt[ids[N]][1] = 1;
    relevant[ids[N]] = true;

    for (int p : topo) {
        for (int adj : g[p]) {
            relevant[p] |= relevant[adj];
        }

        if (relevant[p]) {
            for (int adj : g[p]) {
                if (relevant[adj]) {
                    if (dp[p][1] < ploots[p] + dp[adj][0]) {
                        dp[p][1] = ploots[p] + dp[adj][0];
                        cnt[p][1] = cnt[adj][0];
                    } else if (dp[p][1] == ploots[p] + dp[adj][0]) {
                        cnt[p][1] = (cnt[p][1] + cnt[adj][0]) % 1000000007;
                    }

                    if (dp[p][0] < dp[adj][1]) {
                        dp[p][0] = dp[adj][1];
                        cnt[p][0] = cnt[adj][1];
                    } else if (dp[p][0] == dp[adj][1]) {
                        cnt[p][0] = (cnt[p][0] + cnt[adj][1]) % 1000000007;
                    }

                    if (dp[p][0] < dp[adj][0]) {
                        dp[p][0] = dp[adj][0];
                        cnt[p][0] = cnt[adj][0];
                    } else if (dp[p][0] == dp[adj][0]) {
                        cnt[p][0] = (cnt[p][0] + cnt[adj][0]) % 1000000007;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++) scanf("%d", loots + i);

    for (int i = 0; i < M; i++) {
        scanf("%d%d", &edges[i].first, &edges[i].second);
        graph[edges[i].first].push_back(edges[i].second);
        igraph[edges[i].second].push_back(edges[i].first);
    }

    kosaraju();
    solve();

    long long looted = max(dp[ids[1]][0], dp[ids[1]][1]), count;

    if (dp[ids[1]][0] == dp[ids[1]][1]) {
        count = (cnt[ids[1]][0] + cnt[ids[1]][1]) % 1000000007;
    } else {
        count = dp[ids[1]][0] > dp[ids[1]][1] ? cnt[ids[1]][0] : cnt[ids[1]][1];
    }

    printf("%lld %lld", looted, count);

    return 0;
}
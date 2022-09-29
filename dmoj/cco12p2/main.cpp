#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

const int MAX_NODE = 20000;
long long dist[2][MAX_NODE + 1], N, M;
bool in_queue[MAX_NODE + 1];
vector<pair<int, int>> graph[MAX_NODE + 1];

void solve(int source) {
    fill(begin(dist[0]), end(dist[0]), INF);
    fill(begin(dist[1]), end(dist[1]), INF);
    queue<int> q;
    q.push(source);
    dist[0][source] = 0;
    in_queue[source] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        in_queue[node] = false;

        for (pair<int, int> adj_edge : graph[node]) {
            int adj = adj_edge.first;
            int weight = adj_edge.second;

            if (dist[0][adj] > dist[0][node] + weight) {
                dist[1][adj] = dist[0][adj];
                dist[0][adj] = dist[0][node] + weight;
                if (!in_queue[adj]) {
                    q.push(adj);
                    in_queue[adj] = true;
                }
            } else if (dist[0][adj] != dist[0][node] + weight && dist[1][adj] > dist[0][node] + weight) {
                dist[1][adj] = dist[0][node] + weight;
                if (!in_queue[adj]) {
                    q.push(adj);
                    in_queue[adj] = true;
                }
            }

            if (dist[0][adj] != dist[1][node] + weight && dist[1][adj] > dist[1][node] + weight) {
                dist[1][adj] = dist[1][node] + weight;
                if (!in_queue[adj]) {
                    q.push(adj);
                    in_queue[adj] = true;
                }
            }
        }
    }
}

int main() {
    scan(N);
    scan(M);

    while (M--) {
        int u, v, w;
        scan(u);
        scan(v);
        scan(w);
        graph[u].emplace_back(v, w);
    }

    solve(1);

    printf("%lld\n", dist[1][N] == INF ? -1 : dist[1][N]);

    return 0;
}
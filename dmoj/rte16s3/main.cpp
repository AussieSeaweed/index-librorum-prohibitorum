#include <iostream>
#include <vector>
#include <unordered_map>
#include <bitset>

#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
using namespace std;

vector<vector<unsigned int>> dist(6000, vector<unsigned int>(6000));
vector<vector<pair<int, int>>> graph(6000);
int N, Q;

void dfs(int node, int source, int parent, int d) {
    dist[source][node] = d;

    for (pair<int, int> edge : graph[node]) {
        int adj = edge.first, cost = edge.second;
        if (adj != parent) {
            dfs(adj, source, node, d + cost);
        }
    }
}

int main() {
    scan(N);

    for (int i = 0; i < N - 1; i++) {
        int v, w, d;
        scan(v); scan(w); scan(d);
        graph[v].emplace_back(w, d);
        graph[w].emplace_back(v, d);
    }

    for (int i = 0; i < N; i++) {
        dfs(i, i, -1, 0);
    }

    scan(Q);

    while (Q--) {
        int v, w;
        scan(v); scan(w);
        printf("%u\n", dist[w][v]);
    }

    return 0;
}
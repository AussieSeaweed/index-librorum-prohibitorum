#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph(1000001);
vector<vector<int>> parents(1000001);
vector<bool> visited(1000001, false);
vector<double> prob(1000001, -1);

void dfs(int node) {
    visited[node] = true;
    for (int adj : graph[node]) {
        parents[adj].push_back(node);
        if (!visited[adj])
            dfs(adj);
    }
}

double getProb(int node) {
    if (prob[node] >= 0) return prob[node];

    double p = 0;

    for (int parent : parents[node])
        p += getProb(parent) / graph[parent].size();

    return prob[node] = p;
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);

    while (M--) {
        int v, w;
        scanf("%d%d", &v, &w);
        graph[v].push_back(w);
    }

    dfs(1);
    prob[1] = 1;

    for (int node = 1; node <= N; node++) {
        if (graph[node].empty()) {
            printf("%.9lf\n", getProb(node));
        }
    }

    return 0;
}
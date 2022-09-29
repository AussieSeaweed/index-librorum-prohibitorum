#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph(5001);
vector<int> dist(5001);
vector<int> parent(5001, 0);
vector<bool> visited(5001);
vector<bool> marked(5001, false);
vector<int> nodes;
int N, S;

void dfs(int node, int depth) {
    dist[node] = depth;

    for (int adj : graph[node]) {
        if (adj != parent[node]) {
            parent[adj] = node;
            dfs(adj, depth + 1);
        }
    }
}

int markRange(int node, int depth) {
    if (depth >= 0) {
        visited[node] = true;
        marked[node] = true;

        for (int adj : graph[node]) {
            if (!visited[adj]) {
                markRange(adj, depth - 1);
            }
        }
    }
}

int getStartNode(int node, int d) {
    if (parent[node] == 0 || !d) return node;
    else return getStartNode(parent[node], d - 1);
}

int getNumNeeded(int d) {
    int num = 0;
    fill(marked.begin(), marked.end(), false);
    for (int node : nodes) {
        if (!marked[node]) {
            fill(visited.begin(), visited.end(), false);
            int startNode = getStartNode(node, d);
            markRange(startNode, d);
            num++;
        }
    }
    return num;
}

int main() {
    scanf("%d%d", &N, &S);

    for (int i = 1; i < N; i++) {
        int v, w;
        scanf("%d%d", &v, &w);
        graph[v].push_back(w);
        graph[w].push_back(v);
        nodes.push_back(i);
    }
    nodes.push_back(N);

    dfs(1, 0);

    sort(nodes.begin(), nodes.end(), [&] (int i, int j) {
        return dist[i] > dist[j];
    });

    int lo = 0, hi = 5000, mid;

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (getNumNeeded(mid) <= S) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d", lo);

    return 0;
}
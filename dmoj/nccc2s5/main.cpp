#include <bits/stdc++.h>

int N, M;

class Edge {
public:
    int v, w, dist;

    Edge(int v, int w, int dist) {
        this->v = v;
        this->w = w;
        this->dist = dist;
    }

    int other(int vertex) {
        if (vertex == v) return w;
        else return v;
    }
};

std::vector<Edge> edgeList;
std::vector<std::vector<Edge>> graph;

std::vector<Edge> mst() {
    std::vector<Edge> edges = edgeList;

    std::vector<int> ds(N + 1);
    for (int i = 1; i <= N; i++) {
        ds[i] = i;
    }

    auto find = [&] (int e) {
        while (e != ds[e]) {
            ds[e] = ds[ds[e]];
            e = ds[e];
        }

        return e;
    };

    std::sort(edges.begin(), edges.end(), [] (Edge a, Edge b) {
        return a.dist > b.dist;
    });

    std::vector<Edge> ans;

    for (Edge e : edges) {
        if (ans.size() == N - 1) break;
        int r1 = find(e.v);
        int r2 = find(e.w);
        if (r1 != r2) {
            ans.push_back(e);
            ds[r1] = r2;
        }
    }

    return ans;
}

void createGraph() {
    graph = std::vector<std::vector<Edge>>(N + 1);

    std::vector<Edge> m = mst();

    for (Edge e : m) {
        graph[e.v].push_back(e);
        graph[e.w].push_back(e);
    }
}

bool reachableAux(int node, int dest, int min, std::vector<bool>& visited) {
    visited[node] = true;

    if (node == dest) return true;

    bool found = false;
    for (Edge e : graph[node]) {
        if (found) break;
        if (!visited[e.other(node)] && e.dist >= min) {
            found |= reachableAux(e.other(node), dest, min, visited);
        }
    }

    return found;
}

bool reachable(int node, int dest, int min) {
    std::vector<bool> visited(N + 1, false);

    return reachableAux(node, dest, min, visited);
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int u, v, z;
        scanf("%d%d%d", &u, &v, &z);
        edgeList.emplace_back(u, v, z);
    }

    createGraph();
    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int T;
        scanf("%d", &T);

        if (T == 1) {
            int m, x;
            scanf("%d%d", &m, &x);
            edgeList[m - 1].dist = x;
            createGraph();
        } else {
            int a, b, w;
            scanf("%d%d%d", &a, &b, &w);
            if (reachable(a, b, w)) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
    }

    return 0;
}
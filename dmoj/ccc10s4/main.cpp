#include <bits/stdc++.h>
#define INF 9999999

class Edge {
public:
    int from, to, weight;

    Edge(int f, int t, int w) {
        from = f;
        to = t;
        weight = w;
    }
};

bool eq(Edge a, Edge b) {
    return ((a.from == b.from && a.to == b.to) || (a.to == b.from && a.from == b.to)) && a.weight == b.weight;
}

class Room {
public:
    std::vector<Edge> edges;
};

int root(std::vector<int> uf, int e) {
    while (e != uf[e]) {
        e = uf[e];
    }
    return e;
}

int mst_len(std::vector<Edge> edges, int N, bool disregard_zero) {
    std::vector<int> uf(N+1);
    for (int i = 0; i <= N; i++) uf[i] = i;
    std::vector<Edge> mst;

    std::sort(edges.begin(), edges.end(), [] (Edge a, Edge b) -> bool {
        return a.weight < b.weight;
    });

    if (disregard_zero) N--;

    for (int i = 0; i < edges.size() && mst.size() < N; i++) {
        int r1 = root(uf, edges[i].from), r2 = root(uf, edges[i].to);
        if (r1 != r2) {
            mst.push_back(edges[i]);
            uf[r1] = r2;
        }
    }

    int sum = 0;
    for (Edge e : mst) {
        sum += e.weight;
    }

    return sum;
}

int main() {
    int N;
    scanf("%d", &N);
    std::vector<Room> rooms(N+1);
    int C;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C);
        std::vector<int> vertices;
        for (int j = 0; j < C; j++) {
            int m; scanf("%d", &m);
            vertices.push_back(m);
        }
        vertices.push_back(vertices[0]);
        int w;
        for (int j = 0; j < C; j++) {
            scanf("%d", &w);
            rooms[i].edges.emplace_back(vertices[j], vertices[j+1], w);
        }
    }

    std::vector<Edge> edges1;
    std::vector<Edge> edges2;
    std::vector<int> minToOutside(N+1, INF);

    for (int i = 1; i <= N; i++) {
        for (Edge e1 : rooms[i].edges) {
            bool flag = false;
            for (int j = 1; j <= N; j++) {
                if (i != j) {
                    bool found = false;
                    for (Edge e2 : rooms[j].edges) {
                        if (eq(e1, e2)) {
                            Edge e(i, j, e1.weight);
                            edges1.push_back(e);
                            edges2.push_back(e);
                            flag = true;
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }
            }
            if (!flag) minToOutside[i] = std::min(minToOutside[i], e1.weight);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (minToOutside[i] != INF) {
            edges2.emplace_back(0, i, minToOutside[i]);
        }
    }

    int ans1 = mst_len(edges1, N, true), ans2 = mst_len(edges2, N, false);

    printf("%d", std::min(ans1, ans2));
    return 0;
}
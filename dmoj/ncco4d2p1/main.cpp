#include <iostream>
#include <vector>
#define INFINITY 999999999

int N, M, W;

struct Edge {
    int v, w, t;

    Edge(int v, int w, int t) :v{v}, w{w}, t{t} {}
};

bool bellmanFord(std::vector<Edge> edgeList) {
    std::vector<int> min(N + 1, INFINITY);

    for (int i = 1; i <= N; i++) {
        for (Edge e : edgeList) {
            if (min[e.v] + e.t < min[e.w]) {
                min[e.w] = min[e.v] + e.t;
            }
        }
    }

    for (Edge e : edgeList) {
        if (min[e.v] + e.t < min[e.w]) {
            return true;
        }
    }

    return false;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d%d", &N, &M, &W);

        std::vector<Edge> edgeList;

        while (M--) {
            int v, w, t;
            scanf("%d%d%d", &v, &w, &t);
            edgeList.emplace_back(v, w, t);
            edgeList.emplace_back(w, v, t);
        }

        while (W--) {
            int v, w, t;
            scanf("%d%d%d", &v, &w, &t);
            edgeList.emplace_back(v, w, -t);
        }

        if (bellmanFord(edgeList))
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
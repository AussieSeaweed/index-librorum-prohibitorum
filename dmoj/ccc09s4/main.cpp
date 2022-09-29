#include <bits/stdc++.h>
#define INF 9999999

class Edge {
public:
    int start, end, cost;

    Edge(int s, int e, int c) {
        start = s;
        end = e;
        cost = c;
    }
};

int N, T, K;
std::vector<std::vector<Edge>> graph(5001, std::vector<Edge>());
std::map<int, int> sellers;

std::vector<int> dijkstra(int s) {
    std::vector<int> min(N+1, INF);
    std::vector<bool> visited(N+1, false);
    min[s] = 0;

    while (true) {
        int min_node = -1;
        for (int i = 1; i <= N; i++) {
            if (!visited[i]) {
                if (min[i] != INF) {
                    if (min_node == -1)
                        min_node = i;
                    else if (min[min_node] > min[i])
                        min_node = i;
                }
            }
        }

        if (min_node == -1) break;
        visited[min_node] = true;

        for (Edge e : graph[min_node]) {
            int adj = e.end;
            int weight = e.cost + min[min_node];
            if (weight < min[adj])
                min[adj] = weight;
        }
    }

    return min;
}

int main() {
    scanf("%d%d", &N, &T);
    for (int i = 0; i < T; i++) {
        int v, w, c;
        scanf("%d%d%d", &v, &w, &c);
        graph[v].emplace_back(v,w,c);
        graph[w].emplace_back(w,v,c);
    }

    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        int z, p;
        scanf("%d%d", &z, &p);
        sellers[z] = p;
    }

    int s;
    scanf("%d", &s);
    std::vector<int> min = dijkstra(s);

    int ans = INF;
    for (std::pair<int, int> p : sellers) {
        ans = std::min(ans, min[p.first] + p.second);
    }

    printf("%d", ans);

    return 0;
}
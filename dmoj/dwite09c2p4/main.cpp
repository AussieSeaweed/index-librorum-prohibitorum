#include <iostream>
#include <vector>
#include <queue>
#define INFINITY 99999999

std::vector<std::vector<int>> graph;
std::vector<std::pair<int, int>> edges;
int N;

int main() {
    int _ = 5;
    while (_--) {
        graph.clear();
        graph.resize(101);
        edges.clear();

        scanf("%d", &N);

        while (N--) {
            int v, w;
            scanf("%d%d", &v, &w);
            graph[v].push_back(w);
            graph[w].push_back(v);
            edges.emplace_back(v, w);
        }

        std::vector<int> level(101, INFINITY);
        std::queue<int> q;
        level[1] = 0;
        q.push(1);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int adj : graph[node]) {
                if (level[adj] == INFINITY) {
                    q.push(adj);
                    level[adj] = level[node] + 1;
                }
            }
        }

        int count = 0;

        for (std::pair<int, int> edge : edges) {
            if (level[edge.first] == level[edge.second]) count++;
        }

        printf("%d\n", count);
    }
    return 0;
}
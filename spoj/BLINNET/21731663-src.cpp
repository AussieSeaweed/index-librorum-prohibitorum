#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int v, w;
    long long weight;
    Edge(int v, int w, int weight) :v{v}, w{w}, weight{weight} {}
    bool operator>(Edge that) const {
        return weight > that.weight;
    }
};

vector<vector<Edge>> graph;
vector<bool> visited;
long long P;
int N, M;

int prim() {
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    visited[1] = true;
    for (Edge& e : graph[1]) pq.push(e);
    int total = 0;
    int count = 0;

    while (!pq.empty() && count != N - 1) {
        Edge e = pq.top();
        pq.pop();
        if (visited[e.w] ^ visited[e.v]) {
            count++;
            total += e.weight;
            if (!visited[e.w]) {
                visited[e.w] = true;
                for (Edge& edge : graph[e.w])
                    pq.push(edge);
            } else {
                visited[e.v] = true;
                for (Edge& edge : graph[e.w])
                    pq.push(edge);
            }
        }
    }

    return total;
}

int main() {
    int _;
    scanf("%d", &_);

    while (_--) {
        scanf("%d", &N);
        graph.clear();
        graph.resize(N + 1);
        visited.resize(N + 1);
        fill(visited.begin(), visited.end(), false);

        for (int i = 1; i <= N; i++) {
            string str;
            cin >> str;

            int m;
            scanf("%d", &m);
            while (m--) {
                int node, weight;
                scanf("%d%d", &node, &weight);
                graph[i].emplace_back(i, node, weight);
            }
        }

        printf("%d\n", prim());
    }

    return 0;
}
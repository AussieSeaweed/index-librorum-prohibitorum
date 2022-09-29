#include <iostream>
#include <vector>
#include <queue>
#define INFINITY 99999999
using namespace std;

struct Edge {
    int from, to, dist;
    Edge(int from, int to, int dist) :from{from}, to{to}, dist{dist} {}
};

struct Event {
    int node, dist;
    Event(int node, int dist) :node{node}, dist{dist} {}
};

vector<vector<Edge>> graph(5001);
int N, M;

vector<vector<int>> dijkstra(int source) {
    vector<vector<int>> dist(2, vector<int>(N + 1, INFINITY));
    vector<bool> inQ(N + 1, false);
    queue<int> q;
    q.push(source);
    dist[0][source] = 0;
    inQ[source] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        inQ[node] = false;

        for (Edge adjEdge : graph[node]) {
            int other = adjEdge.to;
            int weight = dist[0][node] + adjEdge.dist;

            if (weight < dist[0][other]) {
                dist[1][other] = dist[0][other];
                dist[0][other] = weight;
                if (!inQ[other]) {
                    q.push(other);
                    inQ[other] = true;
                }
            } else if (weight < dist[1][other] && weight != dist[0][other]) {
                dist[1][other] = weight;
                if (!inQ[other]) {
                    q.push(other);
                    inQ[other] = true;
                }
            }

            weight = dist[1][node] + adjEdge.dist;

            if (weight < dist[1][other] && weight != dist[0][other]) {
                dist[1][other] = weight;
                if (!inQ[other]) {
                    q.push(other);
                    inQ[other] = true;
                }
            }
        }
    }

    return dist;
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int v, w, d;
        scanf("%d%d%d", &v, &w, &d);
        graph[v].emplace_back(v, w, d);
        graph[w].emplace_back(w, v, d);
    }

    vector<vector<int>> dist = dijkstra(1);

    printf("%d\n", dist[1][N]);

    return 0;
}
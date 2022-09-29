#include <bits/stdc++.h>

class Edge {
public:
    int start, end, weight;

    Edge (int s, int e, int w) {
        start = s;
        end = e;
        weight = w;
    }

    bool operator < (Edge that) const {
        return weight < that.weight;
    }
};

int c, r, d;

std::vector<Edge> kruskal(std::priority_queue<Edge, std::vector<Edge>, std::less<Edge>> edges) {
    std::vector<int> uf(c + 1);

    for (int i = 1; i <= c; i++) {
        uf[i] = i;
    }

    auto root = [&] (int node) -> int {
        while (node != uf[node]) {
            uf[node] = uf[uf[node]];
            node = uf[node];
        }
        return node;
    };

    std::vector<Edge> mst;

    while (!edges.empty() && mst.size() != c - 1) {
        Edge min_edge = edges.top();
        edges.pop();

        int r1 = root(min_edge.start);
        int r2 = root(min_edge.end);

        if (r1 != r2) {
            mst.push_back(min_edge);
            uf[r1] = r2;
        }
    }

    return mst;
}

int main() {
    scanf("%d%d%d", &c, &r, &d);

    std::priority_queue<Edge, std::vector<Edge>, std::less<Edge>> edge_list;

    while (r--) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        edge_list.emplace(x, y, w);
    }

    std::vector<Edge> mst = kruskal(edge_list);
    std::set<int> destinations;

    while (d--) {
        int dest;
        scanf("%d", &dest);
        destinations.insert(dest);
    }

    std::vector<std::set<int>> inbound(c + 1);

    for (Edge e : mst) {
        inbound[e.start].insert(e.end);
        inbound[e.end].insert(e.start);
    }

    for (int i = 1; i <= c; i++) {
        if (inbound[i].size() == 1 && !destinations.count(i)) {
            int connectedTo = *inbound[i].begin();

            inbound[connectedTo].erase(i);
            inbound[i].erase(connectedTo);

            for (auto it = mst.begin(); it != mst.end(); it++) {
                if ((it->start == i && it->end == connectedTo) || (it->end == i && it->start == connectedTo)) {
                    it = mst.erase(it);
                    break;
                }
            }
        }
    }

    int min_weight = 999999999;

    for (Edge e : mst) {
        if (e.weight < min_weight)
            min_weight = e.weight;
    }

    printf("%d", min_weight);

    return 0;
}
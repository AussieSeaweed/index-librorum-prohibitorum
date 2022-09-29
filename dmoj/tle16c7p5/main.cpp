#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <set>
#include <queue>
#include <algorithm>

#define INFINITY 999999999999999999ull

struct Edge {
    int v, w;
    unsigned long long d;

    Edge(int v, int w, unsigned long long d) :v{v}, w{w}, d{d} {}
};

struct Compare {
    bool operator()(Edge *a, Edge *b) const {
        return a->w < b->w;
    }
};

std::unordered_map<unsigned long long, std::deque<int>> ans;
std::set<unsigned long long> seg;

std::vector<Edge *> edgeTo(301, nullptr);
std::vector<int> level(301, 99999999);
std::vector<std::vector<Edge *>> graph(301);
unsigned long long prev = 0;
int N, M, Q;

bool bfs() {
    for (int i = 1; i <= N; i++) { level[i] = 99999999; edgeTo[i] = nullptr; }

    std::queue<int> q;
    level[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int n = q.front(); q.pop();

        for (Edge *adj_edge : graph[n]) {
            int other = adj_edge->w;
            if (level[other] == 99999999 && adj_edge->d) {
                level[other] = level[n] + 1;
                q.push(other);
            }
        }
    }

    return level[N] != 99999999;
}

void record(unsigned long long min) {
    std::deque<int> p;

    for (int n = N; n != 1; n = edgeTo[n]->v) {
        edgeTo[n]->d -= min;
        p.push_front(n);
    }
    p.push_front(1);

    min += prev;
    seg.insert(min);
    ans[min] = p;
    prev = min;
}

unsigned long long dfs(int node, unsigned long long cf) {
    unsigned long long tmp = cf;
    if (node == N) {
        record(cf);
        return cf;
    }

    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->w;
        if (level[node] + 1 == level[other] && adj_edge->d && tmp) {
            edgeTo[other] = adj_edge;
            unsigned long long f = dfs(other, std::min(adj_edge->d, tmp));
            tmp -= f;
        }
    }

    return cf - tmp;
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int a, b;
        unsigned long long c;
        scanf("%d%d%llu", &a, &b, &c);
        graph[a].push_back(new Edge(a, b, c));
    }

    for (int i = 1; i <= N; i++)
        std::sort(graph[i].begin(), graph[i].end(), Compare());

    while (bfs()) {
        dfs(1, INFINITY);
    }

    scanf("%d", &Q);

    while (Q--) {
        unsigned long long q;
        scanf("%llu", &q);
        std::set<unsigned long long>::iterator it = seg.lower_bound(q);
        if (it == seg.end())
            printf("Fail\n");
        else {
            for (int n : ans[*it]) {
                printf("%d ", n);
            }
            printf("\n");
        }
    }

    return 0;
}
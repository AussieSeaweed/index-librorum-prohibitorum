#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cstring>

#define inf 999999999
using namespace std;

struct Edge {
    int from, to, capacity, flow;

    Edge(int from, int to, int capacity) : from{ from }, to{ to }, capacity{ capacity }, flow{ 0 } {}

    int other(int node) { return node == to ? from : to; }

    int get(int node) { return node == to ? capacity - flow : flow; }

    void add(int node, int delta) {
        if (node == to) flow += delta;
        else flow -= delta;
    }
};

string grid[200];
vector<Edge *> graph[80002];
vector<int> level(80002);
vector<pair<int, int>> adj_cells {
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, 1}
};

int N, sz;
int S = 80000, T = 80001;

int out(int i) {
    return i + sz;
}

int valid(int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < N;
}

bool in_order(char a, char b) {
    return (a == 'C' && b == 'A') || (a == 'A' && b == 'L') || (a == 'L' && b == 'I');
}

int bfs() {
    fill(level.begin(), level.end(), inf);
    queue<int> q;
    q.push(S);
    level[S] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (Edge *adj_edge : graph[node]) {
            int other = adj_edge->other(node);
            if (adj_edge->get(other) && level[other] == inf) {
                q.push(other);
                level[other] = level[node] + 1;
            }
        }
    }

    return level[T] != inf;
}

int dfs(int node, int pushed_flow) {
    if (node == T) return pushed_flow;
    int tmp = pushed_flow;

    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->other(node);
        if (level[other] == level[node] + 1 && adj_edge->get(other) && tmp) {
            int flow = dfs(other, min(tmp, adj_edge->get(other)));
            adj_edge->add(other, flow);
            tmp -= flow;
        }
    }

    return pushed_flow - tmp;
}

int to_i(int r, int c) {
    return r * N + c;
}

int dinic() {
    int flow = 0;

    while (bfs())
        flow += dfs(S, inf);

    return flow;
}

int main() {
    scanf("%d", &N);
    sz = N * N;

    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int hash = to_i(r, c), hash_out = out(hash);

            Edge *edge = new Edge(hash, hash_out, 1);
            graph[hash].push_back(edge);
            graph[hash_out].push_back(edge);

            if (grid[r][c] == 'C') {
                Edge *edge = new Edge(S, hash, inf);
                graph[S].push_back(edge);
                graph[hash].push_back(edge);
            } else if (grid[r][c] == 'I') {
                Edge *edge = new Edge(hash_out, T, inf);
                graph[hash_out].push_back(edge);
                graph[T].push_back(edge);
            }

            if (grid[r][c] != 'I') {
                for (pair<int, int> adj : adj_cells) {
                    int nr = r + adj.first;
                    int nc = c + adj.second;
                    if (valid(nr, nc) && in_order(grid[r][c], grid[nr][nc])) {
                        Edge *edge = new Edge(hash_out, to_i(nr, nc), inf);
                        graph[hash_out].push_back(edge);
                        graph[to_i(nr, nc)].push_back(edge);
                    }
                }
            }
        }
    }

    printf("%d\n", dinic());

    return 0;
}
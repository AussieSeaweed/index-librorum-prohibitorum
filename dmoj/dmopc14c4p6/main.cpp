#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
using namespace std;

vector<std::vector<int>> graph(500001);
vector<int> up(500001, -1);
vector<int> down(500001, -1);
vector<int> downalt(500001, -1);
vector<int> downnode(500001, -1);
vector<int> parent(500001, -1);
vector<bool> visited(500001, false);

int getDown(int node) {
    if (down[node] != -1) return down[node];

    visited[node] = true;

    down[node] = 1;
    for (int adj : graph[node]) {
        if (!visited[adj]) {
            parent[adj] = node;
            if (1 + getDown(adj) > down[node]) {
                downalt[node] = down[node];
                down[node] = 1 + getDown(adj);
                downnode[node] = adj;
            } else {
                downalt[node] = max(downalt[node], 1 + getDown(adj));
            }
        }
    }

    return down[node];
}

int getUp(int node) {
    up[node] = max(up[node], 1 + (parent[node] == -1 ? 0 : up[parent[node]]));

    for (int adj : graph[node])
        if (adj != parent[node])
            up[adj] = 1 + (adj == downnode[node] ? downalt[node] : down[node]);

    for (int adj : graph[node])
        if (adj != parent[node])
            getUp(adj);
}

int main() {
    int N;
    scan(N);

    for (int i = 1; i < N; i++) {
        int x, y;
        scan(x);
        scan(y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    getDown(1);
    getUp(1);

    for (int i = 1; i <= N; i++) {
        printf("%d\n", std::max(down[i], up[i]));
    }
}
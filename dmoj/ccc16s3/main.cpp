#include <bits/stdc++.h>

int N, M, V;
std::vector<std::set<int>> graph(100000);
std::vector<int> inBound(100000, 0);
std::vector<bool> isPho(100000, false);

int theNode;
int max = -INFINITY;

void dfs(int n, int count, std::vector<bool>& visited) {
    visited[n] = true;
    if (count > max) {
        max = count;
        theNode = n;
    }
    for (int adj : graph[n]) {
        if (!visited[adj]) {
            dfs(adj, count + 1, visited);
        }
    }
}

int get_diameter() {
    std::vector<bool> visited(N, false);
    dfs(theNode, 0, visited);

    visited = std::vector<bool>(N, false);
    dfs(theNode, 0, visited);

    return max;
}

int main() {
    scanf("%d%d", &N, &M);

    for (int i = 0; i < M; i++) {
        int a;
        scanf("%d", &a);
        isPho[a] = true;
    }

    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        graph[a].insert(b);
        graph[b].insert(a);
        inBound[a]++, inBound[b]++;
    }

    V = N;
    while (true) {
        bool flag = false;
        for (int i = 0; i < N; i++) {
            int j = i;
            while (!isPho[j] && inBound[j] == 1) {
                V--;
                int t = *graph[j].begin();
                graph[t].erase(j);
                graph[j].erase(t);
                inBound[t]--;
                inBound[j]--;
                j = t;
                flag = true;
            }
        }
        if (!flag) break;
    }

    for (int i = 0; i < N; i++) {
        if (isPho[i]) {
            theNode = i;
            break;
        }
    }

    int longest = get_diameter();
    int total = 2 * (V-1);

    printf("%d", total - longest);
    return 0;
}
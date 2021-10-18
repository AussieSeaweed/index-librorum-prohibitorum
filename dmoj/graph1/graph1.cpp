#include <iostream>
#include <vector>

int N, M, X, Y;
bool visited[10000];
std::vector<int> graph[10000];

void dfs(int node) {
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;

            dfs(neighbor);
        }
    }
}

int main() {
    std::cin >> N >> M;

    while (M--) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::cin >> X >> Y;
    --X, --Y;

    dfs(X);

    std::cout << (visited[Y] ? '1' : '0') << std::endl;

    return 0;
}
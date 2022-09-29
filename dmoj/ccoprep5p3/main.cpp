#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

int N, M;
float distances[3000][3001];
std::vector<std::pair<int, float>> graph[3000];

double solve() {
    for (int i = 0; i < N; ++i)
        std::fill(distances[i], distances[i] + N + 1, INFINITY);

    std::queue<std::pair<int, int>> queue;

    distances[0][0] = 0;
    queue.emplace(0, 0);

    while (!queue.empty()) {
        auto[node, count] = queue.front();
        queue.pop();

        if (count < N) {
            for (auto[neighbor, weight]: graph[node]) {
                if (distances[neighbor][count + 1] > distances[node][count] + weight) {
                    distances[neighbor][count + 1] = distances[node][count] + weight;
                    queue.emplace(neighbor, count + 1);
                }
            }
        }
    }

    double ret = INFINITY;

    for (int i = 0; i < N; ++i) {
        double cur = -INFINITY;

        for (int j = 0; j < N; ++j)
            if (distances[i][N] != INFINITY && distances[i][j] != INFINITY)
                cur = std::max(cur, (distances[i][N] - distances[i][j]) / ((double) N - j));

        if (cur != -INFINITY)
            ret = std::min(ret, cur);
    }

    return ret;
}

int main() {
    std::cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int u, v;
        double w;
        std::cin >> u >> v >> w;
        --u, --v;
        graph[u].emplace_back(v, w);
    }

    std::cout.precision(15);
    std::cout << solve() << std::endl;

    return 0;
}
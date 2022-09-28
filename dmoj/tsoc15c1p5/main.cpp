#include <iostream>
#include <vector>
#include <queue>
#include <climits>

int N, M, W, antDistances[100], humanDistances[100];
std::vector<int> graph[100];
std::queue<int> antQueue, humanQueue;

int main() {
    std::cin >> N >> M;

    while (M--) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::fill(antDistances, antDistances + N, INT_MAX);
    std::fill(humanDistances, humanDistances + N, INT_MAX);

    std::cin >> W;

    for (int i = 0; i < W; ++i) {
        int w;
        std::cin >> w;
        --w;
        antDistances[w] = 0;
        antQueue.push(w);
    }

    humanDistances[0] = 0;
    humanQueue.push(0);

    for (int i = 0; !antQueue.empty() || !humanQueue.empty(); ++i) {
        if (i > 0 && i % 4 == 0) {
            std::queue<int> queue;

            while (!antQueue.empty()) {
                int node = antQueue.front();
                antQueue.pop();

                for (int neighbor: graph[node]) {
                    if (antDistances[neighbor] == INT_MAX) {
                        antDistances[neighbor] = antDistances[node] + 4;
                        queue.push(neighbor);
                    }
                }
            }

            antQueue = queue;
        }

        std::queue<int> queue;

        while (!humanQueue.empty()) {
            int node = humanQueue.front();
            humanQueue.pop();

            if (antDistances[node] > humanDistances[node]) {
                for (int neighbor: graph[node]) {
                    if (humanDistances[neighbor] == INT_MAX) {
                        humanDistances[neighbor] = humanDistances[node] + 1;
                        queue.push(neighbor);
                    }
                }
            } else {
                humanDistances[node] = INT_MAX;
            }
        }

        humanQueue = queue;
    }

    if (humanDistances[N - 1] == INT_MAX)
        std::cout << "sacrifice bobhob314" << std::endl;
    else
        std::cout << humanDistances[N - 1] << std::endl;

    return 0;
}
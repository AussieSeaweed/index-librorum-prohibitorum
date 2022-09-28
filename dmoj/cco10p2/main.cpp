#include <iostream>
#include <vector>
#include <cstring>

constexpr int ZERO = 300, INF = 100000;
int N, D, color[300], memo[300][601];
std::vector<int> graph[300];

int solve(int node, int diff) {
    if (diff < -N || N < diff)
        return INF;

    int &ret = memo[node][ZERO + diff];

    if (~ret)
        return ret;

    ret = INF;

    if (diff == 0)
        ret = 1;

    if (graph[node].empty())
        ret = std::min(ret, color[node] == diff ? 0 : INF);
    else if (graph[node].size() == 1)
        ret = std::min(ret, solve(graph[node][0], diff - color[node]));
    else if (graph[node].size() == 2)
        for (int i = -N; i <= N; ++i)
            ret = std::min(ret, solve(graph[node][0], i) + solve(graph[node][1], diff - i - color[node]));

    if (ret > INF)
        ret = INF;

    return ret;
}

int main() {
    std::cin >> N >> D;

    for (int i = 0; i < N; ++i) {
        int node, c, count;
        std::cin >> node >> c >> count;

        color[node] = c ? 1 : -1;

        while (count--) {
            int child;
            std::cin >> child;
            graph[node].push_back(child);
        }
    }

    memset(memo, -1, sizeof memo);

    std::cout << (solve(0, D) == INF ? -1 : solve(0, D)) << std::endl;

    return 0;
}
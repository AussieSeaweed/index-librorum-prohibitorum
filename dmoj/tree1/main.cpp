#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph(4, std::vector<int>(4, 0));
std::vector<bool> visited(4, false);
std::vector<int> parent(4, -1);
bool isTree(int node) {
    visited[node] = true;
    bool returnVal = true;

    for (int i = 0; i < 4; i++) {
        if (graph[node][i]) {
            if (visited[i]) {
                if (parent[node] == i) continue;

                return false;
            }

            parent[i] = node;
            returnVal &= isTree(i);
        }
    }

    return returnVal;
}

int main() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            std::cin >> graph[i][j];

    graph[0][0] = false;
    graph[1][1] = false;
    graph[2][2] = false;
    graph[3][3] = false;

    if (isTree(1) && visited[0] && visited[1] && visited[2] && visited[3])
        printf("Yes");
    else
        printf("No");

    return 0;
}
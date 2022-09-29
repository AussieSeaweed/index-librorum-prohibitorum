#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph(10001);
vector<bool> usable(10001, false);
vector<bool> visited(10001, false);
vector<bool> in_path(10001, false);
vector<long long> dp(10001, -1);
bool isCyclic = false;
bool isLarge = false;
int N, M;

void checkUsable(int node) {
    if (node == 2) {
        visited[node] = true;
        usable[node] = true;
        return;
    }
    visited[node] = true;
    for (int adj : graph[node]) {
        if (!visited[adj]) {
            checkUsable(adj);
        }
        usable[node] = usable[node] || usable[adj];
    }
}

long long check(long long val) {
    if (val >= 1000000000) {
        isLarge = true;
    }
    return val % 1000000000;
}

long long getAns(int node, int parent) {
    if (isCyclic) return 0;
    if (dp[node] != -1) return dp[node];
    if (node == 2) return 1;
    in_path[node] = true;

    long long ans = 0;

    for (int adj : graph[node]) {
        if (usable[adj]) {
            if (!in_path[adj]) {
                ans += getAns(adj, node);
                ans = check(ans);
            } else {
                isCyclic = true;
                return 0;
            }
        }
    }

    in_path[node] = false;
    return dp[node] = ans;
}

int main() {
    scanf("%d%d", &N, &M);
    while (M--) {
        int v, w;
        scanf("%d%d", &v, &w);
        graph[v].push_back(w);
    }

    checkUsable(1);
    getAns(1, -1);

    if (isCyclic) {
        printf("inf");
    } else {
        printf(isLarge ? "%09lld" : "%lld", dp[1]);
    }
    return 0;
}
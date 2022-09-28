#include <iostream>
#include <vector>
#include <cstring>
#define inf 999999999

using namespace std;

vector<int> graph[100001];
int parent[100001];
int dp[100001][2];
int N;

int solve(int node, bool must) {
    if (dp[node][must] != -1) return dp[node][must];

    dp[node][must] = !must ? solve(node, true) : inf;

    if (must) {
        dp[node][must] = 1;

        for (int adj : graph[node]) {
            if (adj != parent[node]) {
                parent[adj] = node;
                dp[node][must] += solve(adj, false);
            }
        }
    } else {
        int val = 0;

        for (int adj : graph[node]) {
            if (adj != parent[node]) {
                parent[adj] = node;
                val += solve(adj, true);
            }
        }

        dp[node][must] = min(dp[node][must], val);
    }

    return dp[node][must];
}

int main() {
    memset(dp, -1, sizeof dp);
    scanf("%d", &N);

    while (--N) {
        int u, v;
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    printf("%d", solve(1, false));

    return 0;
}
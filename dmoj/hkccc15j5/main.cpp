#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M, C = 0, size[1001], dp[1001][1001];
bool color[1001], visited[1001], unable, succ[1001][1001];
string ans1(1001, '0'), ans2(1001, '0');
pair<int, int> count[1001];
vector<int> graph[1001], sets[1001];

void dfs(int node, bool c, int id) {
    if (unable) return;
    visited[node] = true;
    color[node] = c;
    sets[id].push_back(node);
    (c ? count[id].second : count[id].first)++;

    for (int adj : graph[node]) {
        if (visited[adj]) {
            if (c == color[adj]) {
                unable = true;
                return;
            }
        } else {
            dfs(adj, !c, id);
        }
    }
}

int solve(int c, int n) {
    if (~dp[c][n]) return dp[c][n];
    if (c == C + 1) return 2 * abs(N / 2 - n) + (N % 2);

    dp[c][n] = solve(c + 1, n + count[c].first);
    succ[c][n] = false;

    int cur = solve(c + 1, n + count[c].second);
    if (cur < dp[c][n]) {
        dp[c][n] = cur;
        succ[c][n] = true;
    }

    return dp[c][n];
}

int main() {
    scanf("%d%d", &N, &M);

    while (M--) {
        int S, T;
        scanf("%d%d", &S, &T);
        graph[S].push_back(T);
        graph[T].push_back(S);
    }

    for (int i = 1; i <= N && !unable; i++) {
        if (!visited[i])
            dfs(i, false, ++C);
    }

    if (unable) {
        printf("-1\n");
        return 0;
    }

    for (int i = 1; i <= C; i++) {
        size[i] = count[i].first + count[i].second + size[i - 1];
    }

    memset(dp, -1, sizeof dp);
    memset(succ, -1, sizeof succ);

    solve(1, 0);

    for (int c = 1, n = 0; c <= C; c++) {
        if (succ[c][n]) {
            for (int node : sets[c]) {
                if (color[node]) {
                    ans1[node] = '1';
                    ans2[node] = '2';
                } else {
                    ans1[node] = '2';
                    ans2[node] = '1';
                }
            }
        } else {
            for (int node : sets[c]) {
                if (color[node]) {
                    ans1[node] = '2';
                    ans2[node] = '1';
                } else {
                    ans1[node] = '1';
                    ans2[node] = '2';
                }
            }
        }

        n += succ[c][n] ? count[c].second : count[c].first;
    }

    if (ans1 < ans2) {
        for (int i = 1; i <= N; i++) {
            printf("%c", ans1[i]);
        }
    } else {
        for (int i = 1; i <= N; i++) {
            printf("%c", ans2[i]);
        }
    }

    printf("\n");

    return 0;
}
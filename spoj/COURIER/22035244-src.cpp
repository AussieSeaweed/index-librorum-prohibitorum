#include <iostream>
#include <cstring>
#include <vector>
#include <math.h>

#define inf 999999999
using namespace std;

vector<int> graph[101];
long long dp[101][371293], dist[101][101]; int N, M, B, Z, from[5], to[5];

void reset() {
    memset(dp, -1, sizeof dp);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dist[i][j] = inf;
        }
    }

    for (int i = 1; i <= N; i++) {
        dist[i][i] = 0;
    }
}

void floyd_warshall() {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

long long solve(int node, int mask) {
    if (dp[node][mask] != -1) return dp[node][mask];
    if (!mask) return dist[node][B];
    dp[node][mask] = inf;

    int pow = 1;
    int tmpmask = mask;

    for (int i = 0; i < Z; i++, pow *= 13, tmpmask /= 13)
        if (tmpmask % 13)
            dp[node][mask] = min(dp[node][mask], dist[node][from[i]] + dist[from[i]][to[i]] + solve(to[i], mask - pow));

    return dp[node][mask];
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        scanf("%d%d%d", &N, &M, &B);

        reset();

        while (M--) {
            int u, v; long long d;
            scanf("%d%d%lld", &u, &v, &d);
            dist[u][v] = min(dist[u][v], d);
            dist[v][u] = min(dist[v][u], d);
        }

        floyd_warshall();

        scanf("%d", &Z);

        int mask = 0, pow = 1;

        for (int i = 0; i < Z; i++, pow *= 13) {
            int f, t, val;
            scanf("%d%d%d", &f, &t, &val);
            from[i] = f;
            to[i] = t;
            mask += val * pow;
        }

        printf("%lld\n", solve(B, mask));
    }
    return 0;
}
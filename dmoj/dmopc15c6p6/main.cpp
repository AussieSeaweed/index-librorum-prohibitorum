#include <iostream>
#include <bitset>

using namespace std;

bitset<1501> reachable[1501], adj[1501], connected[1501];
int N, M, K;

int main() {
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 1; i <= N; i++) {
        reachable[i][i] = adj[i][i] = connected[i][i] = 1;
    }

    while (M--) {
        int v, w;
        scanf("%d%d", &v, &w);
        reachable[v][w] = reachable[w][v] = adj[v][w] = adj[w][v] = connected[v][w] = connected[w][v] = 1;
    }

    while (--K) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (reachable[i][j])
                    connected[i] |= adj[j];
            }
            reachable[i] |= connected[i];
        }
    }

    for (int i = 1; i <= N; i++)
        printf("%d\n", reachable[i].count());
    return 0;
}
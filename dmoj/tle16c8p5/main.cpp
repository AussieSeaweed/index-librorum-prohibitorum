#include <iostream>
#include <vector>
#include <queue>
#define inf 999999999
using namespace std;

bool chosen[101];
vector<vector<int>> adj(101);
vector<int> level(101);
vector<int> pairn(101, 0);
vector<int> pairm(101, 0);
int N, M, C;

void get_chosen() {
    scanf("%d", &C);

    for (int i = 0; i < C; i++) {
        int id;
        scanf("%d", &id);
        chosen[id] = true;
    }
}

bool bfs() {
    fill(level.begin(), level.end(), inf);
    queue<int> q;

    for (int n = 1; n <= N; n++) {
        if (!pairn[n]) {
            level[n] = 0;
            q.push(n);
        } else {
            level[n] = inf;
        }
    }

    level[0] = inf;

    while (!q.empty()) {
        int n = q.front();
        q.pop();

        if (level[n] < level[0]) {
            for (int m : adj[n]) {
                if (level[pairm[m]] == inf) {
                    level[pairm[m]] = level[n] + 1;
                    q.push(pairm[m]);
                }
            }
        }
    }

    return level[0] != inf;
}

bool dfs(int n) {
    if (!n) return true;

    for (int m : adj[n]) {
        if (level[pairm[m]] == level[n] + 1 && dfs(pairm[m])) {
            pairn[n] = m;
            pairm[m] = n;
            return true;
        }
    }

    level[n] = inf;
    return false;
}

int hopcroft_karp() {
    int matches = 0;

    while (bfs())
        for (int n = 1; n <= N; n++)
            if (!pairn[n])
                matches += dfs(n);

    return matches;
}

int main() {
    scanf("%d%d", &N, &M);

    get_chosen();

    for (int i = 2; i <= N; i++) {
        int c;
        scanf("%d", &c);
        while (c--) {
            int id;
            scanf("%d", &id);
            if (chosen[id]) {
                adj[i].push_back(id);
            }
        }
    }

    cout << C - hopcroft_karp() << endl;

    return 0;
}
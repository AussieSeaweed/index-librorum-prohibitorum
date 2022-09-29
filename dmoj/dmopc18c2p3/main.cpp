#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int dist1[100001], dist2[100001], N, M, K, A, B;
bool s[100001];
vector<int> graph[100001];

void bfs(int s, int dist[]) {
    fill(dist, dist + N + 1, inf);
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int adj : graph[node]) {
            if (dist[adj] == inf) {
                dist[adj] = dist[node] + 1;
                q.push(adj);
            }
        }
    }
}

int main() {
    scan(N);
    scan(M);
    scan(K);
    scan(A);
    scan(B);

    while (K--) {
        int n;
        scan(n);
        s[n] = true;
    }

    while (M--) {
        int u, v;
        scan(u);
        scan(v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    bfs(A, dist1);
    bfs(B, dist2);

    int ans = inf;

    for (int i = 1; i <= N; i++) {
        if (s[i]) {
            ans = min(ans, dist1[i] + dist2[i]);
        }
    }

    printf("%d\n", ans);

    return 0;
}
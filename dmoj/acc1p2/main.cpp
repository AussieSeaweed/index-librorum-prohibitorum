#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

vector<int> graph[100001];
int uf[100001], dist[100001], from[100001], marked[100001], cur_index = 0;

inline int id(int node) {
    while (node != uf[node]) {
        uf[node] = uf[uf[node]];
        node = uf[node];
    }
    return node;
}

inline int bfs(int s1, int s2) {
    if (s1 == s2) return 0;

    queue<int> q;
    marked[s1] = cur_index;
    marked[s2] = cur_index;
    dist[s1] = 0;
    dist[s2] = 0;
    from[s1] = s1;
    from[s2] = s2;
    q.push(s1);
    q.push(s2);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int &adj : graph[node]) {
            if (marked[adj] != cur_index) {
                marked[adj] = cur_index;
                dist[adj] = dist[node] + 1;
                from[adj] = from[node];
                q.push(adj);
            } else if (from[adj] != from[node]) {
                return dist[adj] + dist[node] + 1;
            }
        }
    }
}

int main() {
    int N, M, Q;
    scan(N);
    scan(M);
    scan(Q);

    for (int i = 1; i <= N; i++)
        uf[i] = i;

    while (M--) {
        int u, v;
        scan(u);
        scan(v);

        int ru = id(u), rv = id(v);
        if (ru != rv) uf[ru] = rv;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    while (Q--) {
        int u, v;
        scan(u);
        scan(v);

        int ru = id(u), rv = id(v);
        if (ru == rv) {
            cur_index++;
            printf("%d\n", bfs(u, v));
        } else {
            printf("-1\n");
        }
    }

    return 0;
}
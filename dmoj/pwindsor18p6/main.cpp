#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 100000000
#define MOD 1000000007
using namespace std;

int dist[1001];
vector<int> graph[1001];
int N, M, A, B;

int bfs(int s, int t) {
    fill(dist, dist + N, inf);
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

    return dist[t];
}

int main() {
    scan(N);
    scan(M);
    scan(A);
    scan(B);

    while (M--) {
        int u, v;
        scan(u);
        scan(v);

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int query = bfs(1, A) + bfs(A, B);

    printf("%d\n", query >= inf ? -1 : query);

    return 0;
}
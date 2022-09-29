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
#define inf 2000000000
using namespace std;

int N;
bool visited[500][500];
vector<int> adj[500];
char buffer[502];

void dfs(int node, int source) {
    visited[source][node] = true;

    for (int adj : adj[node]) {
        if (!visited[source][adj]) {
            dfs(adj, source);
        }
    }
}

int main() {
    scan(N);
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        for (int j = 0; j < N; j++) {
            if (buffer[j] == '1') {
                adj[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < N; i++)
        dfs(i, i);
    int ans = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (!visited[i][j] && !visited[j][i])
                ans++;
    printf("%d\n", ans);
    return 0;
}
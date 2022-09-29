#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N;
bool good[100001];
vector<int> graph[100001];

bool is_good(long long value) {
    long long sqrtval = sqrt(value);
    return sqrtval * (sqrtval + 1) == value;
}

pair<int, int> dfs(int node, int parent) {
    int down[2] {0, 0}, other = 0;

    for (int adj : graph[node]) {
        if (adj != parent) {
            pair<int, int> q = dfs(adj, node);
            other  = max(other, q.second);

            if (q.first >= down[0]) {
                down[1] = down[0];
                down[0] = q.first;
            } else if (q.first > down[1]) {
                down[1] = q.first;
            }
        }
    }

    return {good[node] ? down[0] + 1 : 0, max(other, good[node] ? down[0] + 1 + down[1] : 0)};
}

int main() {
    pscan(N);

    for (int i = 1; i <= N; i++) {
        long long value;
        pscan(value);
        good[i] = is_good(value);
    }

    for (int i = 1; i < N; i++) {
        int u, v;
        pscan(u);
        pscan(v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    pair<int, int> q = dfs(1, -1);

    printf("%d\n", q.second);

    return 0;
}
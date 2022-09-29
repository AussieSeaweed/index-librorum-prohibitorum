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

struct Edge {
    int a, b, o;

    Edge(int a, int b) : a{ a }, b{ b }, o{ -1 } {}

    int other(int node) {
        return a == node ? b : a;
    }

    void mark(int to_node, bool orientation) {
        if (b == to_node)
            o = orientation;
        else
            o = !orientation;
    }
};

int N;
vector<Edge *> graph[100001];
Edge *edge_list[100000];

void dfs(int node, int parent, bool o) {
    for (Edge *adj_edge : graph[node]) {
        int other = adj_edge->other(node);
        if (other != parent) {
            adj_edge->mark(other, o);
            dfs(other, node, !o);
        }
    }
}

int main() {
    scan(N);

    for (int i = 1; i < N; i++) {
        int a, b;
        scan(a);
        scan(b);
        edge_list[i] = new Edge(a, b);
        graph[a].push_back(edge_list[i]);
        graph[b].push_back(edge_list[i]);
    }

    dfs(1, -1, true);

    for (int i = 1; i < N; i++) {
        printf("%d\n", edge_list[i]->o);
    }

    return 0;
}
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
inline int ffs(int x) { return __builtin_ffs(x) - 1; }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x) - 1; }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

bool color[2000];
int N, match[2000];
pair<int, int> points[2000];
vector<int> graph[2000];
unordered_map<pair<int, int>, int, pair_hash> query;

bool bfs(int NIL, int num_nodes, const bool color[], int level[], int match[], vector<int> graph[]) {
    queue<int> q;

    for (int i = 0; i < num_nodes; i++) {
        if (color[i]) {
            if (match[i] == NIL) {
                level[i] = 0;
                q.push(i);
            } else {
                level[i] = inf;
            }
        }
    }

    level[NIL] = inf;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (level[node] < level[NIL]) {
            for (int adj : graph[node]) {
                if (level[match[adj]] == inf) {
                    level[match[adj]] = level[node] + 1;
                    q.push(match[adj]);
                }
            }
        }
    }

    return level[NIL] != inf;
}

bool dfs(int node, int NIL, int level[], int match[], vector<int> graph[]) {
    if (node == NIL) return true;

    for (int adj : graph[node]) {
        if (level[match[adj]] == level[node] + 1 && dfs(match[adj], NIL, level, match, graph)) {
            match[node] = adj;
            match[adj] = node;
            return true;
        }
    }

    level[node] = inf;
    return false;
}

int hopcroft_karp(int num_nodes, const bool color[], int match[], vector<int> graph[]) {
    int num_matches = 0, NIL = num_nodes, level[NIL + 1];
    fill(match, match + num_nodes, NIL);

    while (bfs(NIL, num_nodes, color, level, match, graph))
        for (int i = 0; i < num_nodes; i++)
            if (color[i] && match[i] == NIL)
                num_matches += dfs(i, NIL, level, match, graph);

    for (int i = 0; i < num_nodes; i++)
        if (match[i] == NIL)
            match[i] = -1;

    return num_matches;
}

int main() {
    while (cin >> N) {
        for_each(graph, graph + N, [] (vector<int> &v) -> void { v.clear(); });
        query.clear();

        for (int i = 0; i < N; i++) {
            scan(points[i].first);
            scan(points[i].second);
            query[{points[i].first, points[i].second}] = i;
            color[i] = (points[i].first & 1) ^ (points[i].second & 1);
        }

        for (int i = 0; i < N; i++) {
            if (color[i]) {
                if (query.count({points[i].first, points[i].second + 1})) graph[i].push_back(query[{points[i].first, points[i].second + 1}]);
                if (query.count({points[i].first, points[i].second - 1})) graph[i].push_back(query[{points[i].first, points[i].second - 1}]);
                if (query.count({points[i].first + 1, points[i].second})) graph[i].push_back(query[{points[i].first + 1, points[i].second}]);
                if (query.count({points[i].first - 1, points[i].second})) graph[i].push_back(query[{points[i].first - 1, points[i].second}]);
            }
        }

        printf("%d\n", N - hopcroft_karp(N, color, match, graph));
    }
    return 0;
}
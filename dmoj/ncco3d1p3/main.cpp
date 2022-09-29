#include <bits/stdc++.h>
#include <bits/extc++.h>
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
inline int ffs(int x) { return __builtin_ffs(x); }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x); }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename T> inline T gcd(const T &x, const T &y) { return std::__gcd(x, y); }
template<typename T, typename ...Ts> inline T gcd(const T &x, const Ts &...xs) { return std::__gcd(x, gcd(xs...)); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
template<typename T> inline void scan(T &x) { char c; bool sign; while ((x = getchar()) < '-'); sign = x == '-'; if (sign) while ((x = getchar()) < '0'); for(x -= '0'; '0' <= (c = getchar()); x = (x << 3) + (x << 1) + c - '0'); x = sign ? -x : x; }
template<typename T, typename ...Ts> inline void scan(T &x, Ts &...xs) { scan(x), scan(xs...); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

int R, C, N, grid[30][30], src, dest, dist[900], id[900], super[900], dsu[900];
long long dp[900];
bool visited[900];
vector<int> pred[900];
set<pair<int, int>> graph[900];
pair<int, int> adjs[] {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
set<int> neutrals[900];

int encode(int r, int c) {
    return r * C + c;
}

bool valid(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C && grid[r][c] != 2;
}

void bfs01() {
    fill(dist, dist + N, inf);
    deque<int> q { src };
    dist[src] = 0;

    while (!q.empty()) {
        int node = q.front(); q.pop_front();

        if (visited[node]) continue;
        visited[node] = true;

        for (pair<int, int> adj_edge : graph[node]) {
            int adj = adj_edge.first, weight = adj_edge.second;

            if (dist[adj] > dist[node] + weight) {
                pred[adj].clear();
                dist[adj] = dist[node] + weight;
                pred[adj].push_back(node);

                if (weight == 0) q.push_front(adj);
                else q.push_back(adj);
            } else if (dist[adj] == dist[node] + weight) {
                pred[adj].push_back(node);
            }
        }
    }
}

const set<int> &get_neutrals_aux(int node) {
    if (!neutrals[node].empty()) return neutrals[node];
    if (id[node] == 0 || id[node] == 3) return neutrals[node] = {node};

    for (int p : pred[node]) {
        const set<int> &cur = get_neutrals_aux(p);
        neutrals[node].insert(cur.begin(), cur.end());
    }

    return neutrals[node];
}

set<int> get_neutrals(int node) {
    set<int> ret;

    for (int p : pred[node]) {
        const set<int> &cur = get_neutrals_aux(p);
        ret.insert(cur.begin(), cur.end());
    }

    return ret;
}

long long solve(int node) {
    if (dp[node]) return dp[node];
    else if (node == src) return dp[node] = 1;

    for (int p : get_neutrals(node))
        dp[node] += solve(p);

    return dp[node];
}

int find_root(int node) { return dsu[node] == node ? node : dsu[node] = find_root(dsu[node]); }
void merge(int u, int v) { dsu[find_root(u)] = find_root(v); }

int main() {
    scan(R, C), N = R * C;
    for (int i = 0; i < N; i++) dsu[i] = i;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scan(grid[i][j]);
            id[encode(i, j)] = grid[i][j];

            if (grid[i][j] == 3)
                src = encode(i, j);
            else if (grid[i][j] == 4)
                dest = encode(i, j);

            if (grid[i][j] == 3 || grid[i][j] == 4)
                grid[i][j] = 1;
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            for (pair<int, int> &adj : adjs) {
                int nr = i + adj.first, nc = j + adj.second;
                if (valid(nr, nc) && grid[i][j] == 1 && grid[nr][nc] == 1) {
                    merge(encode(i, j), encode(nr, nc));
                }
            }
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            super[encode(i, j)] = find_root(encode(i, j));
        }
    }

    src = super[src], dest = super[dest];
    id[src] = 3, id[dest] = 4;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            for (pair<int, int> &adj : adjs) {
                int nr = i + adj.first, nc = j + adj.second;
                if (grid[i][j] != 2 && valid(nr, nc) && super[encode(i, j)] != super[encode(nr, nc)])
                    graph[super[encode(i, j)]].emplace(super[encode(nr, nc)], grid[nr][nc] == 0);
            }
        }
    }

    bfs01();

    if (dist[dest] == inf)
        printf("-1\n");
    else
        printf("%d\n%lld\n", dist[dest], solve(dest));

    return 0;
}
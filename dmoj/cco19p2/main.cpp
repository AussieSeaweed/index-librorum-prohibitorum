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

int N, M, C, *grid[1000000], dist[1000001];
vector<pair<int, int>> graph[1000001];
min_priority_queue<pair<int, int>> pq;
pair<int, int> adjs[] {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
char str[1000001], *output[1000000];

bool valid(int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < M;
}

void dfs(int r, int c, int id) {
    grid[r][c] = id;

    for (pair<int, int> &adj : adjs) {
        int nr = r + adj.first, nc = c + adj.second;
        if (valid(nr, nc) && !grid[nr][nc]) {
            dfs(nr, nc, id);
        }
    }
}

void handle_column(int c) {
    for (int r = N - 1, prev_node = 0, prev_row = N; r >= 0; r--) {
        if (grid[r][c] != -1) {
            graph[prev_node].emplace_back(grid[r][c], prev_row - r - 1);
            prev_node = grid[r][c], prev_row = r;
        }
    }
}

void dijkstra() {
    fill(dist, dist + C + 1, inf);
    dist[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        int node, cur_dist;
        tie(cur_dist, node) = pq.top(), pq.pop();

        if (cur_dist > dist[node]) continue;

        for (pair<int, int> &edge : graph[node]) {
            int adj = edge.first;
            if (dist[adj] > dist[node] + edge.second) {
                dist[adj] = dist[node] + edge.second;
                pq.emplace(dist[adj], adj);
            }
        }
    }
}

int main() {
    scan(N, M);
    for (int i = 0; i < N; i++) grid[i] = new int[M], output[i] = new char[M];

    for (int i = 0; i < N; i++) {
        scanf("%s", str);
        for (int j = 0; j < M; j++)
            grid[i][j] = str[j] == '#' ? 0 : -1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 0) {
                dfs(i, j, ++C);
            }
        }
    }

    for (int i = 0; i < M; i++)
        handle_column(i);

    dijkstra();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            output[i][j] = '.';
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] > 0) {
                output[i + dist[grid[i][j]]][j] = '#';
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}
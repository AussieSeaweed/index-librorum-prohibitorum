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

int H, V, N, sh, sv, fh, fv, dist[1000][1000];
vector<pair<int, int>> graph[1000][1000];
pair<int, int> adj[] {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
};

bool valid(int h, int v) {
    return 0 <= h && h < H && 0 <= v && v < V;
}

int main() {
    int T = 10;
    while (T--) {
        scan(H);
        scan(V);
        scan(sh);
        scan(sv);
        scan(fh);
        scan(fv);
        scan(N);

        for (int h = 0; h < H; h++) {
            for_each(graph[h], graph[h] + V, [] (vector<pair<int, int>> &vec) -> void { vec.clear(); });
            fill(dist[h], dist[h] + V, inf);
        }

        while (N--) {
            int th, tv, uh, uv;
            scan(th);
            scan(tv);
            scan(uh);
            scan(uv);
            graph[th][tv].emplace_back(uh, uv);
            graph[uh][uv].emplace_back(th, tv);
        }

        deque<pair<int, int>> q {{sh, sv}};
        dist[sh][sv] = 0;

        while (!q.empty()) {
            pair<int, int> c = q.front();
            q.pop_front();

            for (pair<int, int> &a : graph[c.first][c.second]) {
                if (dist[a.first][a.second] > dist[c.first][c.second]) {
                    dist[a.first][a.second] = dist[c.first][c.second];
                    q.emplace_front(a.first, a.second);
                }
            }

            for (pair<int, int> &a : adj) {
                int nr = c.first + a.first, nc = c.second + a.second;
                if (valid(nr, nc) && dist[nr][nc] > dist[c.first][c.second] + 1) {
                    dist[nr][nc] = dist[c.first][c.second] + 1;
                    q.emplace_back(nr, nc);
                }
            }
        }

        printf("%d\n", dist[fh][fv]);
    }
    return 0;
}
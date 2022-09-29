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
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(_EuclideanRingElement _m, _EuclideanRingElement _n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
#define ZERO 18
using namespace std;

int X, Y, N, xs, xe, ys, ye;
long long dist[101][101][37][37];
bool banned[101][101];
queue<quad<int, int, int, int>> q;

inline bool valid(int x, int y) {
    return 0 <= x && x <= X && 0 <= y && y <= Y;
}

inline bool path_banned(int x, int y, int tx, int ty) {
    if (x != tx || y != ty) {
        int dx = tx - x, dy = ty - y;
        int gcd = euclidean(abs(dx), abs(dy));
        dx /= gcd, dy /= gcd;

        if (banned[x][y]) return true;

        do {
            x += dx, y += dy;
            if (banned[x][y]) return true;
        } while (!(x == tx && y == ty));
    }
    return banned[tx][ty];
}

int main() {
    scan(X);
    scan(Y);
    scan(N);
    scan(xs);
    scan(ys);
    scan(xe);
    scan(ye);
    while (N--) {
        int xi, yi;
        scan(xi);
        scan(yi);
        banned[xi][yi] = true;
    }

    memset(dist, -1, sizeof dist);

    q.emplace(xs, ys, ZERO, ZERO);
    dist[xs][ys][ZERO][ZERO] = 0;

    while (!q.empty()) {
        auto state = q.front();
        q.pop();
        int x = state.first, y = state.second, vx = state.third, vy = state.fourth;

        for (int a = -1; a <= 1; a++) {
            {
                int tx = x + vx - ZERO + a, ty = y + vy - ZERO, tvx = vx + a, tvy = vy;
                if (valid(tx, ty) && !path_banned(x, y, tx, ty) && dist[tx][ty][tvx][tvy] == -1) {
                    dist[tx][ty][tvx][tvy] = dist[x][y][vx][vy] + 1;
                    q.emplace(tx, ty, tvx, tvy);
                }
            }

            {
                int tx = x + vx - ZERO, ty = y + vy - ZERO + a, tvx = vx, tvy = vy + a;
                if (valid(tx, ty) && !path_banned(x, y, tx, ty) && dist[tx][ty][tvx][tvy] == -1) {
                    dist[tx][ty][tvx][tvy] = dist[x][y][vx][vy] + 1;
                    q.emplace(tx, ty, tvx, tvy);
                }
            }
        }
    }

    printf("%lld\n", dist[xe][ye][ZERO][ZERO]);
    return 0;
}
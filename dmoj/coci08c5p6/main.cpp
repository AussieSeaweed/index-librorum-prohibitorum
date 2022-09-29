#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scanu(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
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
template<typename _EuclideanRingElement> inline _EuclideanRingElement gcd(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

enum { R, D, L, U };

struct Wizard {
    string instructions;
} *wizards[200][200];

long long N, K, M, num_changes[200][200][4][7], dists[200][200][4][7];
bool visited[200][200][4][7];

inline int next_r(int r, int d) {
    if (d == U)
        return r - 1;
    else if (d == D)
        return r + 1;
    else
        return r;
}

inline int next_c(int c, int d) {
    if (d == L)
        return c - 1;
    else if (d == R)
        return c + 1;
    else
        return c;
}

inline bool valid(int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < N;
}

long long dfs(int r, int c, int d, int w, long long changes, long long dist, bool ignore = false) {
    if (visited[r][c][d][w] && !ignore) {
        long long len_before = dists[r][c][d][w], cycle_len = dist - dists[r][c][d][w],
                    changes_before = num_changes[r][c][d][w], cycle_changes = changes - num_changes[r][c][d][w],
                    rem = K - changes_before, num_cycling = rem / cycle_changes, remainder = rem % cycle_changes;
        return len_before + cycle_len * num_cycling + dfs(r, c, d, w, K - remainder, 0, true);
    } else {
        visited[r][c][d][w] = true;
        num_changes[r][c][d][w] = changes;
        dists[r][c][d][w] = dist;
        int changing = 0, nd = d;

        if (wizards[r][c] && wizards[r][c]->instructions[w] != 'S') {
            changing++;
            nd = (d + (wizards[r][c]->instructions[w] == 'R' ? 1 : 3)) % 4;
        }

        if (!valid(next_r(r, nd), next_c(c, nd))) {
            changing++;
            nd = (nd + 2) % 4;
        }

        if (changes + changing >= K)
            return dist;
        else
            return dfs(next_r(r, nd), next_c(c, nd), nd, (w + 1) % 7, changes + changing, dist + 1);
    }
}

inline long long solve() {
    return dfs(0, 0, R, 0, 0, 0);
}

int main() {
    scan(N);
    scan(K);
    scan(M);
    while (M--) {
        int r, c;
        scan(r);
        scan(c);
        r--, c--;
        wizards[r][c] = new Wizard();
        cin >> wizards[r][c]->instructions;
    }
    printf("%lld\n", solve());
    return 0;
}
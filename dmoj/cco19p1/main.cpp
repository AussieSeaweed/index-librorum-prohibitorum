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

int R, C, J, D;
double dp[2][1594323];
bool visited[2][1594323], cur_role;
int grid[13][13];
char str[14];
pair<int, int> adjs[] {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool valid(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}

int get_cur_bitmask() {
    int bitmask = 0;

    for (int i = 0, power = 1; i < R; i++)
        for (int j = 0; j < C; j++, power *= 3)
            bitmask += grid[i][j] * power;

    return bitmask;
}

int get_count(int x) {
    int ret = 0;

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            ret += grid[i][j] == x;

    return ret;
}

double solve() {
    int bitmask = get_cur_bitmask();
    if (visited[cur_role][bitmask]) return dp[cur_role][bitmask];
    visited[cur_role][bitmask] = true;
    if (get_count(!cur_role ? 2 : 1) == 0) return dp[cur_role][bitmask] = 1;
    vector<double> probs;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == (!cur_role ? 1 : 2)) {
                for (pair<int, int> &adj : adjs) {
                    int nr = i + adj.first, nc = j + adj.second;
                    if (valid(nr, nc) && grid[nr][nc] > 0) {
                        int tmp = grid[nr][nc];

                        grid[i][j] = 0;
                        grid[nr][nc] = !cur_role ? 1 : 2;
                        cur_role = !cur_role;
                        probs.push_back(1 - solve());
                        cur_role = !cur_role;
                        grid[nr][nc] = tmp;
                        grid[i][j] = !cur_role ? 1 : 2;
                    }
                }
            }
        }
    }

    sort(probs.begin(), probs.end(), greater<double>());
    double ret = 0;

    for (int i = 0; i < min(!cur_role ? J : D, (int) probs.size()); i++)
        ret += probs[i] * (1. / min(!cur_role ? J : D, (int) probs.size()));

    return dp[cur_role][bitmask] = ret;
}

int main() {
    scan(R, C);

    for (int i = 0; i < R; i++) {
        scanf("%s", str);

        for (int j = 0; j < C; j++)
            grid[i][j] = str[j] == 'J' ? 1 : 2;
    }

    scan(J, D);

    printf("%.3lf\n", solve());

    return 0;
}
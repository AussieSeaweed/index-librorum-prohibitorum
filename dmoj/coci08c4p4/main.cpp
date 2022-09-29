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
inline int ffs(int x) { return __builtin_ffs(x); }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x); }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

int N, cnt[2][513][513];
char str[513][514];
pair<int, int> choice[349525];

int get_sum(int r1, int r2, int c1, int c2, int psum2d[][513]) {
    return psum2d[r2][c2] - psum2d[r1 - 1][c2] - psum2d[r2][c1 - 1] + psum2d[r1 - 1][c1 - 1];
}

int solve(int node, int r1, int r2, int c1, int c2) {
    if (r1 == r2 && c1 == c2) {
        return 0;
    } else {
        int rmid = (r1 + r2) / 2, cmid = (c1 + c2) / 2;
        int queries[]{solve(node * 4 - 2, r1, rmid, c1, cmid),
                      solve(node * 4 - 1, r1, rmid, cmid + 1, c2),
                      solve(node * 4, rmid + 1, r2, c1, cmid),
                      solve(node * 4 + 1, rmid + 1, r2, cmid + 1, c2)};

        int min_val = inf;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) continue;
                int cur = get_sum(i <= 1 ? r1 : rmid + 1, i <= 1 ? rmid : r2, i & 1 ? cmid + 1 : c1, i & 1 ? c2 : cmid, cnt[1]) +
                          get_sum(j <= 1 ? r1 : rmid + 1, j <= 1 ? rmid : r2, j & 1 ? cmid + 1 : c1, j & 1 ? c2 : cmid, cnt[0]);
                for (int k = 0; k < 4; k++)
                    if (k != i && k != j)
                        cur += queries[k];
                if (cur < min_val) {
                    min_val = cur;
                    choice[node] = {i, j};
                }
            }
        }

        return min_val;
    }
}

void fill_ans(int node, int r1, int r2, int c1, int c2, bool whiten, bool blacken) {
    if (whiten || blacken) {
        char character = blacken ? '1' : '0';
        for (int r = r1; r <= r2; r++)
            for (int c = c1; c <= c2; c++)
                str[r][c] = character;
    } else if (r1 != r2 && c1 != c2) {
        int rmid = (r1 + r2) / 2, cmid = (c1 + c2) / 2;
        fill_ans(node * 4 - 2, r1, rmid, c1, cmid, 0 == choice[node].first, 0 == choice[node].second);
        fill_ans(node * 4 - 1, r1, rmid, cmid + 1, c2, 1 == choice[node].first, 1 == choice[node].second);
        fill_ans(node * 4, rmid + 1, r2, c1, cmid, 2 == choice[node].first, 2 == choice[node].second);
        fill_ans(node * 4 + 1, rmid + 1, r2, cmid + 1, c2, 3 == choice[node].first, 3 == choice[node].second);
    }
}

int main() {
    scan(N);
    for (int i = 1; i <= N; i++) {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= N; j++) {
            cnt[str[i][j] - '0'][i][j] = 1;
        }
    }

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cnt[0][i][j] += cnt[0][i - 1][j] + cnt[0][i][j - 1] - cnt[0][i - 1][j - 1],
                    cnt[1][i][j] += cnt[1][i - 1][j] + cnt[1][i][j - 1] - cnt[1][i - 1][j - 1];

    printf("%d\n", solve(1, 1, N, 1, N));
    fill_ans(1, 1, N, 1, N, false, false);
    for (int i = 1; i <= N; i++)
        printf("%s\n", str[i] + 1);
    return 0;
}
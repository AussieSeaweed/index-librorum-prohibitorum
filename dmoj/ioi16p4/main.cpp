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

int N, K, *c, b_pre[200001], w_pre[200001];
bool ldp[200000][101], rdp[200000][101];
bool cw[200000], cb[200000];

inline int b_cnt(int i, int j) {
    return b_pre[j + 1] - b_pre[i];
}

inline int w_cnt(int i, int j) {
    return w_pre[j + 1] - w_pre[i];
}

void solve(bool dp[200000][101], string &s) {
    for (int i = 0; i < N; i++)
        dp[i][0] = b_cnt(0, i) == 0;

    for (int j = 1; j <= K; j++) {
        for (int i = c[j - 1] - 1; i < N; i++) {
            dp[i][j] = (s[i] != 'X' && dp[i - 1][j]) ||
                    (w_cnt(i - c[j - 1] + 1, i) == 0 && (i - c[j - 1] >= 0 ? s[i - c[j - 1]] != 'X' : true) &&
                    (i - c[j - 1] - 1 >= 0 ? dp[i - c[j - 1] - 1][j - 1] : (j - 1 == 0)));
        }
    }
}

string solve_puzzle(string s, int k, int c[]) {
    ::N = s.size(), ::K = k, ::c = c;

    for (int i = 0; i < N; i++)
        b_pre[i + 1] = s[i] == 'X', w_pre[i + 1] = s[i] == '_';
    for (int i = 1; i <= N; i++)
        b_pre[i] += b_pre[i - 1], w_pre[i] += w_pre[i - 1];

    solve(ldp, s);

    reverse(s.begin(), s.end()), reverse(c, c + K);

    for (int i = 0; i < N; i++)
        b_pre[i + 1] = s[i] == 'X', w_pre[i + 1] = s[i] == '_';
    for (int i = 1; i <= N; i++)
        b_pre[i] += b_pre[i - 1], w_pre[i] += w_pre[i - 1];

    solve(rdp, s);
    reverse(s.begin(), s.end()), reverse(c, c + K);

    for (int i = 0; i < N / 2; i++)
        for (int j = 0; j <= K; j++)
            swap(rdp[i][j], rdp[N - i - 1][j]);

    for (int i = 0; i < N; i++)
        b_pre[i + 1] = s[i] == 'X', w_pre[i + 1] = s[i] == '_';
    for (int i = 1; i <= N; i++)
        b_pre[i] += b_pre[i - 1], w_pre[i] += w_pre[i - 1];

    if (N == 1) {
        return s == "X" || s == "_" ? s : (k == 0 ? "_" : "X");
    } else {
        cw[0] = rdp[1][K] && s[0] != 'X';
        cw[N - 1] = ldp[N - 2][K] && s[N - 1] != 'X';

        for (int i = 1; i < N - 1; i++) {
            for (int j = 0; j <= K; j++)
                cw[i] |= ldp[i - 1][j] && rdp[i + 1][K - j];
            if (s[i] == 'X')
                cw[i] = false;
        }

        int m = -inf;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < K; j++) {
                if (i + c[j] <= N && (i == 0 || cw[i - 1]) && (i + c[j] == N || cw[i + c[j]]) && w_cnt(i, i + c[j] - 1) == 0 &&
                        (i - 2 >= 0 ? ldp[i - 2][j] : (j == 0)) && (i + c[j] + 1 < N ? rdp[i + c[j] + 1][K - j - 1] : (j == K - 1))) {
                    m = max(m, i + c[j] - 1);
                }
            }

            if (i <= m)
                cb[i] = true;

            if (s[i] == '_')
                cb[i] = false;
        }

        string ret = s;

        for (int i = 0; i < N; i++) {
            if (s[i] == 'X' || s[i] == '_')
                continue;
            if (cw[i] && cb[i])
                ret[i] = '?';
            else if (cw[i])
                ret[i] = '_';
            else
                ret[i] = 'X';
        }

        return ret;
    }
}
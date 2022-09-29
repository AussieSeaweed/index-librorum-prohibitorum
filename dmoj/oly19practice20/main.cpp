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
template<typename _EuclideanRingElement> inline _EuclideanRingElement gcd(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
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

int N, maxn = 100000, n;
unsigned long long power[100001], phash[11], chash[100001];
string pattern, chunks[11], cur;
vector<int> indices[11];
bool *dp[11];
int min_len[12], max_len[12];

inline void split() {
    int i = 0, p = 0, c = 0;

    for (; i < pattern.size(); i++) {
        if (pattern[i] == '*' || pattern[i] == '?') {
            if (i - p > 0)
                chunks[n - 1] = pattern.substr(p, i - p);

            if (pattern[i] == '*')
                max_len[n] = inf;
            else
                min_len[n]++, max_len[n]++;

            p = i + 1;
            c = 0;
        } else if (!c) {
            c = 1;
            n++;
        }
    }

    if (pattern.size() - p > 0)
        chunks[n - 1] = pattern.substr(p, pattern.size() - p);
}

inline void handle(string &s, unsigned long long &hash) {
    for (int i = 0; i < s.size(); i++)
        hash += power[i] * (s[i] - 'a' + 1);
}

inline bool solve() {
    for (int i = 0; i < cur.size(); i++)
        chash[i + 1] = chash[i] + (cur[i] - 'a' + 1) * power[i];

    for (int i = 0; i < n; i++) {
        indices[i].clear();

        for (int j = 0; j + chunks[i].size() <= cur.size(); j++) {
            if ((chash[j + chunks[i].size()] - chash[j]) * power[maxn - j] == phash[i])
                indices[i].push_back(j);
        }
    }

    for (int i = 0; i < n; i++)
        dp[i] = new bool[indices[i].size()], fill(dp[i], dp[i] + indices[i].size(), false);

    for (int i = 0; i < indices[n - 1].size(); i++) {
        dp[n - 1][i] = max_len[n] >= cur.size() - indices[n - 1][i] - chunks[n - 1].size() && cur.size() - indices[n - 1][i] - chunks[n - 1].size() >= min_len[n];
        if (n == 1 && dp[n - 1][i] && indices[n - 1][i] >= min_len[0])
            return true;
    }

    if (n == 1) return false;

    for (int i = n - 2; i >= 1; i--)
        for (int j = 0; j < indices[i].size(); j++)
            for (int k = lower_bound(indices[i + 1].begin(), indices[i + 1].end(), indices[i][j] + chunks[i].size()) - indices[i + 1].begin(); k < indices[i + 1].size() && !dp[i][j]; k++)
                dp[i][j] |= min_len[i + 1] <= indices[i + 1][k] - indices[i][j] - chunks[i].size() &&
                           indices[i + 1][k] - indices[i][j] - chunks[i].size() <= max_len[i + 1] && dp[i + 1][k];

    for (int i = 0; i < indices[0].size(); i++)
        for (int j = 0; j < indices[1].size(); j++)
            if (max_len[0] >= indices[0][i] && indices[0][i] >= min_len[0] && min_len[1] <= indices[1][j] - indices[0][i] - chunks[0].size() && indices[1][j] - indices[0][i] - chunks[0].size() <= max_len[1] && dp[1][j])
                return true;

    return false;
}

int main() {
    cin.tie(nullptr), cin.sync_with_stdio(false);
    power[0] = 1;
    for (int i = 1; i <= maxn; i++) power[i] = 31 * power[i - 1];
    cin >> pattern;
    split();

    for (int i = 0; i < n; i++)
        handle(chunks[i], phash[i]), phash[i] *= power[maxn];

    cin >> N;

    while (N--) {
        cin >> cur;
        cout << (solve() ? "YES\n" : "NO\n");
    }

    return 0;
}
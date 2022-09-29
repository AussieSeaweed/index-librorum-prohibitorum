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
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

map<pair<char, char>, vector<char>> conv;
vector<char> c[26];
int N, V, T, A, B, W;
char v[26], t[26], str[31];
bool dp[30][30][26];

bool solve() {
    memset(dp, 0, sizeof dp);
    N = strlen(str);

    for (int i  = 0; i < N; i++)
        for (char converted : c[str[i] - 'a'])
            dp[i][i][converted] = true;

    for (int offset = 0; offset < N; offset++) {
        for (int i = 0, j = offset; j < N; i++, j++) {
            for (int k = i; k < j; k++) {
                for (int a = 0; a < V; a++) {
                    for (int b = 0; b < V; b++) {
                        if (dp[i][k][v[a]] && dp[k + 1][j][v[b]] && conv.count({v[a], v[b]})) {
                            for (char converted : conv[{v[a], v[b]}]) {
                                dp[i][j][converted] = true;
                            }
                        }
                    }
                }
            }
        }
    }

    return dp[0][N - 1][v[0]];
}

int main() {
    scan(V);
    scan(T);

    for (int i = 0; i < V; i++) {
        scanf(" %c", v + i);
        v[i] -= 'A';
    }

    for (int i = 0; i < T; i++) {
        scanf(" %c", t + i);
        t[i] -= 'a';
    }

    scan(A);

    while (A--) {
        char a, b;
        scanf(" %c %c", &a, &b);
        a -= 'A';
        b -= 'a';
        c[b].push_back(a);
    }

    scan(B);

    while (B--) {
        char a, b, c;
        scanf(" %c %c %c", &a, &b, &c);
        a -= 'A';
        b -= 'A';
        c -= 'A';
        conv[{b, c}].push_back(a);
    }

    scan(W);

    while (W--) {
        scanf("%s", str);
        printf("%d\n", solve());
    }

    return 0;
}
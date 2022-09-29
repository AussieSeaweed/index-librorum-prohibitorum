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

long long ans[3][3];
bool solved[3][3];
pair<int, int> indices[] { {1, 1}, {0, 1}, {2, 1}, {1, 0}, {1, 2}, {0, 0}, {0, 2}, {2, 0}, {2, 2} };

inline bool solve_for_two_1(int i, int j) {
    int r = -1, rcnt = 0, c = -1, ccnt = 0;
    for (int col = 0; col < 3; col++)
        if (solved[i][col]) rcnt++, c = col;
    for (int row = 0; row < 3; row++)
        if (solved[row][j]) ccnt++, r = row;
    if (rcnt == 1 && ccnt == 1) {
        solved[i][j] = true;
        ans[i][j] = abs(r - i) < abs(c - j) ? ans[i][c] : ans[r][j];
        return true;
    } else {
        return false;
    }
}

inline bool solve_for_two_2(int i, int j) {
    int r = -1, rcnt = 0, c = -1, ccnt = 0;
    for (int col = 0; col < 3; col++)
        if (solved[i][col]) rcnt++, c = col;
    for (int row = 0; row < 3; row++)
        if (solved[row][j]) ccnt++, r = row;
    if (rcnt == 1 && ccnt == 0) {
        solved[i][j] = true;
        ans[i][j] = ans[i][c];
    } else if (rcnt == 0 && ccnt == 1) {
        solved[i][j] = true;
        ans[i][j] = ans[r][j];
    } else {
        return false;
    }

    return true;
}

inline void solve_for_two() {
    for (const pair<int, int> &indice : indices) {
        int i = indice.first, j = indice.second;
        if (!solved[i][j] && solve_for_two_1(i, j)) return;
    }

    for (const pair<int, int> &indice : indices) {
        int i = indice.first, j = indice.second;
        if (!solved[i][j] && solve_for_two_2(i, j)) return;
    }
}

inline bool solve_for_one() {
    int cnt = 0;

    for (int i = 0; i < 3; i++) {
        if (!solved[i][0] && solved[i][1] && solved[i][2])
            ans[i][0] = ans[i][1] - (ans[i][2] - ans[i][1]), solved[i][0] = true, cnt++;
        if (!solved[i][1] && solved[i][0] && solved[i][2])
            ans[i][1] = ans[i][0] + (ans[i][2] - ans[i][0]) / 2, solved[i][1] = true, cnt++;
        if (!solved[i][2] && solved[i][0] && solved[i][1])
            ans[i][2] = ans[i][1] + (ans[i][1] - ans[i][0]), solved[i][2] = true, cnt++;
    }

    for (int j = 0; j < 3; j++) {
        if (!solved[0][j] && solved[1][j] && solved[2][j])
            ans[0][j] = ans[1][j] - (ans[2][j] - ans[1][j]), solved[0][j] = true, cnt++;
        if (!solved[1][j] && solved[0][j] && solved[2][j])
            ans[1][j] = ans[0][j] + (ans[2][j] - ans[0][j]) / 2, solved[1][j] = true, cnt++;
        if (!solved[2][j] && solved[0][j] && solved[1][j])
            ans[2][j] = ans[1][j] + (ans[1][j] - ans[0][j]), solved[2][j] = true, cnt++;
    }

    return cnt > 0;
}

inline long long to_i(string &s) {
    istringstream iss(s);
    long long ret;
    iss >> ret;
    return ret;
}

int main() {
    int c = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            string s;
            cin >> s;
            if (s != "X") {
                ans[i][j] = to_i(s);
                solved[i][j] = true;
                c++;
            }
        }
    }

    if (c == 0)
        solved[0][0] = true, ans[0][0] = 0;

    while (true) {
        while (solve_for_one()) continue;
        solve_for_two();

        int counter = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                counter += solved[i][j];

        if (counter == 9) break;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%lld ", ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}
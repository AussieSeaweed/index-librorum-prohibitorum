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

string A[4], B[4], T[4];

bool is_identical_aux(string A[], string B[]) {
    for (int i = 0; i < 4; i++)
        if (A[i] != B[i])
            return false;
    return true;
}

void apply(int a, int b, int c, int d, string A[], string B[]) {
    copy(A, A + 4, B);

    vector<int> indices{ 1, 2, 3 };

    for (int i = 0; i < a; i++)
        swap(B[indices[0]], B[indices[1]]), swap(B[indices[0]], B[indices[2]]);

    indices = { 0, 2, 3 };

    for (int i = 0; i < b; i++)
        swap(B[indices[0]], B[indices[1]]), swap(B[indices[0]], B[indices[2]]);

    indices = { 0, 1, 3 };

    for (int i = 0; i < c; i++)
        swap(B[indices[0]], B[indices[1]]), swap(B[indices[0]], B[indices[2]]);

    indices = { 0, 1, 2 };

    for (int i = 0; i < d; i++)
        swap(B[indices[0]], B[indices[1]]), swap(B[indices[0]], B[indices[2]]);
}

bool is_identical() {
    for (int a = 0; a < 3; a++)
        for (int b = 0; b < 3; b++)
            for (int c = 0; c < 3; c++)
                for (int d = 0; d < 3; d++) {
                    apply(a, b, c, d, A, T);
                    if (is_identical_aux(T, B)) return true;
                }
    return false;
}

bool is_reflection_aux(string A[], string B[]) {
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            int o[2], O = 0;
            for (int k = 0; k < 4; k++)
                if (k == i || k == j) continue;
                else o[O++] = k;
            if (A[i] == B[i] && A[j] == B[j] && A[o[0]] == B[o[1]] && A[o[1]] == B[o[0]]) return true;
        }
    }
    return false;
}

bool is_reflection() {
    for (int a = 0; a < 3; a++)
        for (int b = 0; b < 3; b++)
            for (int c = 0; c < 3; c++)
                for (int d = 0; d < 3; d++) {
                    apply(a, b, c, d, A, T);
                    if (is_reflection_aux(T, B)) return true;
                }
    return false;
}

int main() {
    for (int i = 0; i < 4; i++)
        cin >> A[i];
    for (int i = 0; i < 4; i++)
        cin >> B[i];
    if (!is_identical() && is_reflection()) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
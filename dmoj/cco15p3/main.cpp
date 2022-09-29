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

long long X, K, N, Q, A[2000], B[2000], C[2000], n[2000], v[2000][11][2001], flog2[2002];
double x[2000][2001];
map<double, long long> cnt;

long long query(int i, int j, long long st[11][2001]) {
    int l = flog2[j - i + 1];
    return max(st[l][i], st[l][j - (1 << l) + 1]);
}

int main() {
    flog2[1] = 0;
    for (int i = 2; i <= 2001; i++) flog2[i] = 1 + flog2[i / 2];
    scan(X);
    scan(K);
    scan(N);
    scan(Q);

    for (int i = 0; i < N; i++) {
        scan(A[i]);
        scan(B[i]);
        scan(C[i]);
    }

    for (int i = 0; i < N; i++) {
        cnt.clear();
        cnt[0], cnt[X];

        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (A[i] - B[i] == A[j] - B[j]) {
                if (A[i] < A[j]) cnt[0] += C[j];
            } else {
                double x = X * (A[j] - A[i]) / ((double) B[i] - A[i] - (B[j] - A[j]));

                if (A[i] < A[j])
                    cnt[0] += C[j];

                if (0 <= x && x <= X) {
                    if (A[i] < A[j])
                        cnt[x] -= C[j];
                    else
                        cnt[x] += C[j];
                }
            }
        }

        long long prev = 0;

        for (pair<const double, long long> &it : cnt)
            x[i][n[i]] = it.first, v[i][0][n[i]] = prev += it.second, n[i]++;

        for (int j = 1; j < 11; j++) {
            for (int k = 0; k + (1 << j) - 1 < n[i]; k++) {
                v[i][j][k] = max(v[i][j - 1][k], v[i][j - 1][k + (1 << (j - 1))]);
            }
        }
    }

    while (Q--) {
        int index;
        long long s;
        scan(index); index--;
        scan(s);
        int i = upper_bound(x[index], x[index] + n[index], s) - x[index] - 1, j = upper_bound(x[index], x[index] + n[index], s + K) - x[index] - 1;
        printf("%lld\n", query(i, j, v[index]));
    }

    return 0;
}
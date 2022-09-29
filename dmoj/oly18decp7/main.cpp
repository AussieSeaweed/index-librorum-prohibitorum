#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> inline constexpr const T &_min(const T &x,const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x,const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x,const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x,const Ts &...xs) { return _max(x, _max(xs...)); }
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
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

int N, a[1000], d[1000];
double min_median = INFINITY, max_median = -INFINITY;

int main() {
    scan(N);
    for (int i = 0; i < N; i++) scan(a[i]);

    if (N == 1) {
        printf("%d.00 %d.00\n", a[0], a[0]);
        return 0;
    }

    sort(a, a + N);
    copy(a, a + N, d);
    reverse(d, d + N);
    for (int i = 0; i < N; i++) {
        // 0..i, i+1..N-1
        int left_size = i + 1, right_size = N - i - 1;
        if (left_size & 1) {
            if (left_size / 2 + 1 > i) {
                double right_median_a = right_size & 1 ? a[right_size / 2 + i + 1] : (a[right_size / 2 + i + 1] + a[right_size / 2 + i]) / 2.;
                double right_median_d = right_size & 1 ? d[right_size / 2 + i + 1] : (d[right_size / 2 + i + 1] + d[right_size / 2 + i]) / 2.;
                min_median = min(min_median, (a[left_size / 2] + right_median_a) / 2.);
                max_median = max(max_median, (d[left_size / 2] + right_median_d) / 2.);
            } else {
                min_median = min(min_median, (a[left_size / 2] + a[left_size / 2 + 1]) / 2.);
                max_median = max(max_median, (d[left_size / 2] + d[left_size / 2 + 1]) / 2.);
            }
        } else {
            min_median = min(min_median, (double) a[left_size / 2]);
            max_median = max(max_median, (double) d[left_size / 2]);
        }
    }
    printf("%.2lf %.2lf\n", min_median, max_median);
    return 0;
}
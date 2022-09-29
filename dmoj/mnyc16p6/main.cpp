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

int bit[10000];
string s[10000];
unordered_map<string, int> ind;

inline int get_mass(const string &a) {
    int ret = 0;

    for (const char &c : a)
        ret += c - 'a' + 1;

    return ret;
}

inline void update(int i, int v) {
    i++;
    while (i <= 10000) {
        bit[i - 1] += v;
        i += i & -i;
    }
}

inline int query(int i) {
    int ret = 0;
    i++;
    while (i) {
        ret += bit[i - 1];
        i -= i & -i;
    }
    return ret;
}

inline int range_query(int i, int j) {
    return query(j) - query(i - 1);
}

int C, N;

int main() {
    scan(C);

    while (C--) {
        char t;
        scanf(" %c", &t);

        if (t == 'A') {
            string r;
            cin >> r;

            if (ind.count(r)) {
                printf("Can't add ");
                cout << r << '\n';
            } else {
                update(N, get_mass(r));
                ind[r] = N;
                s[N] = r;
                N++;
            }
        } else if (t == 'S') {
            string x, y;
            cin >> x >> y;

            update(ind[x], -get_mass(x) + get_mass(y));
            update(ind[y], -get_mass(y) + get_mass(x));
            swap(ind[x], ind[y]);
            swap(s[ind[x]], s[ind[y]]);
        } else if (t == 'M') {
            string x, y;
            cin >> x >> y;

            printf("%d\n", range_query(min(ind[x], ind[y]), max(ind[x], ind[y])));
        } else if (t == 'R') {
            string x, y;
            cin >> x >> y;

            update(ind[x], -get_mass(x) + get_mass(y));
            s[ind[x]] = y;
            ind[y] = ind[x];
            ind.erase(x);
        } else if (t == 'N') {
            printf("%d\n", N);
        }
    }

    return 0;
}
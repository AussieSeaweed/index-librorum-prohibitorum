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
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(_EuclideanRingElement _m, _EuclideanRingElement _n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

struct Query {
    char t;
    int a, b;
};

struct Data {
    int t, l;
};

int N, Q, num, s, v, labels[200001];
unordered_map<int, int> t_l, l_i;
Data datas[100000];
Query queries[100000];
set<int> bit[200001], rev_bit[200001];

inline int get_closest(int a, int b, int t) {
    return abs(a - t) == abs(b - t) ? max(a, b) : (abs(a - t) < abs(b - t) ? a : b);
}

inline int get_closest(set<int> &values, int value) {
    auto it = values.lower_bound(value);
    return get_closest(it != values.begin() ? *--it : inf, it != values.end() ? *it : inf, value);
}

inline int rev(int i) {
    return num - i + 1;
}

inline void add(int i, int t, int priority, set<int> bit[]) {
    while (i <= num) {
        bit[i].insert(t);
        i += i & -i;
    }
}

inline void erase(int i, int t, set<int> bit[]) {
    while (i <= num) {
        bit[i].erase(t);
        i += i & -i;
    }
}

inline int query(int i, int t, set<int> bit[]) {
    int ret = inf;

    while (i) {
        ret = get_closest(ret, get_closest(bit[i], t), t);
        i -= i & -i;
    }

    return ret;
}

int main() {
    srand(time(nullptr));
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(datas[i].t);
        scan(datas[i].l);
        labels[++num] = datas[i].l;
    }

    scan(Q);

    for (int i = 0; i < Q; i++) {
        scanf(" %c", &queries[i].t);
        if (queries[i].t == 'F') scanf(" %c", &queries[i].a); else scan(queries[i].a);
        if (queries[i].t != 'S') scan(queries[i].b);
        if (queries[i].t == 'L' || queries[i].t == 'F') labels[++num] = queries[i].b;
    }

    sort(labels + 1, labels + num + 1);
    num = unique(labels + 1, labels + num + 1) - labels - 1;

    for (int i = 1; i <= num; i++) l_i[labels[i]] = i;

    for (int i = 0; i < N; i++) {
        datas[i].l = l_i[datas[i].l];
        t_l[datas[i].t] = datas[i].l;
        add(datas[i].l, datas[i].t, rand(), bit);
        add(rev(datas[i].l), datas[i].t, rand(), rev_bit);
    }

    for (int i = 0; i < Q; i++) {
        switch (queries[i].t) {
            case 'T': {
                int &label = t_l[queries[i].a];
                erase(label, queries[i].a, bit);
                erase(rev(label), queries[i].a, rev_bit);
                add(label, queries[i].b, rand(), bit);
                add(rev(label), queries[i].b, rand(), rev_bit);
                t_l[queries[i].b] = t_l[queries[i].a];
                t_l.erase(queries[i].a);
            } break;
            case 'L': {
                queries[i].b = l_i[queries[i].b];
                int &label = t_l[queries[i].a];
                erase(label, queries[i].a, bit);
                erase(rev(label), queries[i].a, rev_bit);
                add(queries[i].b, queries[i].a, rand(), bit);
                add(rev(queries[i].b), queries[i].a, rand(), rev_bit);
                label = queries[i].b;
            } break;
            case 'F': {
                v = queries[i].b = l_i[queries[i].b];
                s = queries[i].a;
            } break;
            case 'S': {
                int q;

                if (s == '>')
                    q = query(rev(v + 1), queries[i].a, rev_bit);
                else if (s == '<')
                    q = query(v - 1, queries[i].a, bit);
                else
                    q = query(num, queries[i].a, bit);

                printf("%d\n", q == inf ? -1 : q);
            } break;
        }
    }

    return 0;
}
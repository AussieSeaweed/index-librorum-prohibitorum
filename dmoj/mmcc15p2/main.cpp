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

template<typename T, typename Compare>
struct Convex_Hull_Trick {
    vector<T> m, b;
    Compare compare;
    int sind = 0;

    void add(T cm, T cb) {
        while (m.size() - sind >= 2 && (cb - b[b.size() - 2]) * (m[m.size() - 2] - m.back()) <=
                                       (b.back() - b[b.size() - 2]) * (m[m.size() - 2] - cm))
            m.pop_back(), b.pop_back();

        m.push_back(cm);
        b.push_back(cb);
    }

    template<typename Iterator_Type>
    void add_all(Iterator_Type it, Iterator_Type lim) {
        for (; it != lim; it++) add(it->first, it->second);
    }

    T query(double x) {
        while (m.size() - sind >= 2 && !compare(m[sind] * x + b[sind], m[sind + 1] * x + b[sind + 1]))
            sind++;

        return m[sind] * x + b[sind];
    }
};

struct Query {
    double x, y;
    int i;
    bool operator<(const Query &that) const { return x < that.x; }
} queries[500000];

double eps = 1e-9;
Convex_Hull_Trick<double, less<double>> minimize[1048576];
Convex_Hull_Trick<double, greater<double>> maximize[1048576];
vector<pair<double, double>> lt[1048576], gt[1048576];
int N, M, ans[500000];

void build_seg_tree(int node, int lo, int hi) {
    if (lo == hi) {
        double A, B, C, m, b;
        scanf("%lf%lf%lf", &A, &B, &C);
        m = -A / B, b = C / B;
        lt[node].emplace_back(m, b);
        gt[node].emplace_back(m, b);
        minimize[node].add(m, b);
        maximize[node].add(m, b);
    } else {
        int mid = (lo + hi) / 2;
        build_seg_tree(node * 2, lo, mid);
        build_seg_tree(node * 2 + 1, mid + 1, hi);
        merge(lt[node * 2].begin(), lt[node * 2].end(), lt[node * 2 + 1].begin(), lt[node * 2 + 1].end(), back_inserter(lt[node]), less<pair<double, double>>());
        merge(gt[node * 2].begin(), gt[node * 2].end(), gt[node * 2 + 1].begin(), gt[node * 2 + 1].end(), back_inserter(gt[node]), greater<pair<double, double>>());
        maximize[node].add_all(lt[node].begin(), lt[node].end());
        minimize[node].add_all(gt[node].begin(), gt[node].end());
    }
}

int query_lower_cut(int node, int lo, int hi, double x, double y) {
    if (lo == hi) return minimize[node].query(x) <= y + eps ? lo : N;
    int mid = (lo + hi) / 2;
    if (minimize[node * 2].query(x) <= y + eps) return query_lower_cut(node * 2, lo, mid, x, y);
    else return query_lower_cut(node * 2 + 1, mid + 1, hi, x, y);
}

int query_upper_cut(int node, int lo, int hi, double x, double y) {
    if (lo == hi) return maximize[node].query(x) >= y - eps ? lo : N;
    int mid = (lo + hi) / 2;
    if (maximize[node * 2].query(x) >= y - eps) return query_upper_cut(node * 2, lo, mid, x, y);
    else return query_upper_cut(node * 2 + 1, mid + 1, hi, x, y);
}

int main() {
    scan(N);
    scan(M);

    build_seg_tree(1, 0, N - 1);

    for (int i = 0; i < M; i++)
        scanf("%lf%lf", &queries[i].x, &queries[i].y), queries[i].i = i;

    sort(queries, queries + M);

    for (int i = 0; i < M; i++)
        ans[queries[i].i] = max(query_lower_cut(1, 0, N - 1, queries[i].x, queries[i].y), query_upper_cut(1, 0, N - 1, queries[i].x, queries[i].y));

    for (int i = 0; i < M; i++)
        printf("%d\n", ans[i] == N ? -1 : ans[i] + 1);

    return 0;
}
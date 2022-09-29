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

triple<int, int, int> coms[100000];
int N, Q, seg_tree[262144][4][4];

pair<int, int> get_pos(int i) {
    return {i / 4, i % 4};
}

void merge(int f1[4][4], int f2[4][4], int to[4][4]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            int pr, pc;
            tie(pr, pc) = get_pos(f2[r][c]);
            to[r][c] = f1[pr][pc];
        }
    }
}

void apply_aux(int r, int c, int k, int grid[4][4]) {
    if (k <= 1) return;

    int v = grid[r][c++];

    for (int i = 0; i < k - 1; i++, c++)
        swap(v, grid[r][c]);

    r++, c--;

    for (int i = 0; i < k - 1; i++, r++)
        swap(v, grid[r][c]);

    r--, c--;

    for (int i = 0; i < k - 1; i++, c--)
        swap(v, grid[r][c]);

    r--, c++;

    for (int i = 0; i < k - 1; i++, r--)
        swap(v, grid[r][c]);
}

void apply(triple<int, int, int> com, int grid[4][4]) {
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            grid[r][c] = r * 4 + c;

    apply_aux(com.first, com.second, com.third, grid);
}

void build_seg_tree(int node, int lo, int hi) {
    if (lo == hi) {
        apply(coms[lo], seg_tree[node]);
    } else {
        int mid = (lo + hi) / 2;
        build_seg_tree(node * 2, lo, mid);
        build_seg_tree(node * 2 + 1, mid + 1, hi);
        merge(seg_tree[node * 2], seg_tree[node * 2 + 1], seg_tree[node]);
    }
}

void update(int node, int lo, int hi, int i, triple<int, int, int> com) {
    if (i < lo || hi < i) return;
    else if (lo == hi) {
        coms[lo] = com;
        apply(coms[lo], seg_tree[node]);
    } else {
        int mid = (lo + hi) / 2;
        update(node * 2, lo, mid, i, com);
        update(node * 2 + 1, mid + 1, hi, i, com);
        merge(seg_tree[node * 2], seg_tree[node * 2 + 1], seg_tree[node]);
    }
}

int main() {
    scan(N, Q);

    for (int i = 0; i < N; i++) {
        scan(coms[i].first, coms[i].second, coms[i].third);
        coms[i].first--, coms[i].second--;
    }

    build_seg_tree(1, 0, N - 1);

    while (Q--) {
        int i, r, c, k;
        scan(i, r, c, k);
        i--, r--, c--;
        update(1, 0, N - 1, i, {r, c, k});

        for (int p = 0; p < 4; p++) {
            printf("%d %d %d %d\n", seg_tree[1][p][0] + 1, seg_tree[1][p][1] + 1, seg_tree[1][p][2] + 1, seg_tree[1][p][3] + 1);
        }
    }

    return 0;
}
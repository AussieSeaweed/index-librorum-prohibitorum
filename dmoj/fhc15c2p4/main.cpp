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
#define MOD 1000000000
using namespace std;


struct Node {
    long long sum, msval, m, b, oi, ei, oddcnt;
    bool ms;

    Node() { reset(); }

    inline void reset() {
        sum = msval = m = b = oi = ei = oddcnt = 0;
        ms = false;
    }
};

long long T, N, M;
long long S[1000000], O[1000000], A[1000000], B[1000000], C[1000000], D[1000000], ans,
        XS, YS, ZS,
        XO, YO, ZO,
        XA, YA, ZA,
        XB, YB, ZB,
        XC, YC, ZC,
        XD, YD, ZD;
Node seg_tree[2097152];

inline void handle_lazy(long long node, long long lo, long long hi) {
    if (seg_tree[node].ms) {
        seg_tree[node].sum = (seg_tree[node].msval * (hi - lo + 1)) % MOD;

        if (seg_tree[node].msval & 1) {
            seg_tree[node].oddcnt = (hi - lo) + 1;
            seg_tree[node].oi = seg_tree[node].ei = (hi - lo + 1) / 2;
            if ((hi - lo + 1) & 1) {
                if (lo & 1) seg_tree[node].oi++;
                else seg_tree[node].ei++;
            }
        } else {
            seg_tree[node].oddcnt = seg_tree[node].oi = seg_tree[node].ei = 0;
        }

        if (lo != hi) {
            seg_tree[node * 2].m = seg_tree[node * 2].b = seg_tree[node * 2 + 1].m = seg_tree[node * 2 + 1].b = 0;
            seg_tree[node * 2].ms = seg_tree[node * 2 + 1].ms = true;
            seg_tree[node * 2].msval = seg_tree[node * 2 + 1].msval = seg_tree[node].msval;
        }

        seg_tree[node].ms = false;
        seg_tree[node].msval = 0;
    }

    if (seg_tree[node].m || seg_tree[node].b) {
        seg_tree[node].sum = (seg_tree[node].sum + seg_tree[node].m * (((hi - lo + 1) * (lo + hi) / 2) % MOD) % MOD + seg_tree[node].b * (hi - lo + 1) % MOD) % MOD;

        if (seg_tree[node].b & 1) {
            long long ocnt = (hi - lo + 1) / 2, ecnt = (hi - lo + 1) / 2;
            if ((hi - lo + 1) & 1) {
                if (lo & 1) {
                    ocnt++;
                } else {
                    ecnt++;
                }
            }

            seg_tree[node].oi = ocnt - seg_tree[node].oi;
            seg_tree[node].ei = ecnt - seg_tree[node].ei;
        }

        if (seg_tree[node].m & 1) {
            long long ocnt = (hi - lo + 1) / 2;
            if ((hi - lo + 1) & 1 && lo & 1) {
                ocnt++;
            }

            seg_tree[node].oi = ocnt - seg_tree[node].oi;
        }

        seg_tree[node].oddcnt = seg_tree[node].oi + seg_tree[node].ei;

        if (lo != hi) {
            seg_tree[node * 2].m = (seg_tree[node * 2].m + seg_tree[node].m) % MOD;
            seg_tree[node * 2 + 1].m = (seg_tree[node * 2 + 1].m + seg_tree[node].m) % MOD;
            seg_tree[node * 2].b = (seg_tree[node * 2].b + seg_tree[node].b) % MOD;
            seg_tree[node * 2 + 1].b = (seg_tree[node * 2 + 1].b + seg_tree[node].b) % MOD;
        }

        seg_tree[node].m = seg_tree[node].b = 0;
    }
}

inline void merge(Node &node, Node &left, Node &right) {
    node.sum = (left.sum + right.sum) % MOD;
    node.oi = left.oi + right.oi;
    node.ei = left.ei + right.ei;
    node.oddcnt = left.oddcnt + right.oddcnt;
}

void build_seg_tree(long long node, long long lo, long long hi) {
    seg_tree[node].reset();

    if (lo == hi) {
        seg_tree[node].sum = S[lo - 1];

        if (S[lo - 1] & 1) {
            seg_tree[node].oddcnt = 1;
            if (lo & 1) {
                seg_tree[node].oi = 1;
            } else {
                seg_tree[node].ei = 1;
            }
        }

    } else {
        long long mid = (lo + hi) / 2;
        build_seg_tree(node * 2, lo, mid);
        build_seg_tree(node * 2 + 1, mid + 1, hi);
        merge(seg_tree[node], seg_tree[node * 2], seg_tree[node * 2 + 1]);
    }
}

void update_make_same(long long node, long long lo, long long hi, long long left, long long right, long long value) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return;

    if (left <= lo && hi <= right) {
        seg_tree[node].ms = true;
        seg_tree[node].msval = value;
        handle_lazy(node, lo, hi);
    } else {
        long long mid = (lo + hi) / 2;
        update_make_same(node * 2, lo, mid, left, right, value);
        update_make_same(node * 2 + 1, mid + 1, hi, left, right, value);
        merge(seg_tree[node], seg_tree[node * 2], seg_tree[node * 2 + 1]);
    }
}

void update_linear(long long node, long long lo, long long hi, long long left, long long right, long long m, long long b) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return;

    if (left <= lo && hi <= right) {
        seg_tree[node].m = m;
        seg_tree[node].b = b;
        handle_lazy(node, lo, hi);
    } else {
        long long mid = (lo + hi) / 2;
        update_linear(node * 2, lo, mid, left, right, m, b);
        update_linear(node * 2 + 1, mid + 1, hi, left, right, m, b);
        merge(seg_tree[node], seg_tree[node * 2], seg_tree[node * 2 + 1]);
    }
}

Node query(long long node, long long lo, long long hi, long long left, long long right) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return Node();
    if (left <= lo && hi <= right) return seg_tree[node];

    long long mid = (lo + hi) / 2;
    Node ret, lq = query(node * 2, lo, mid, left, right), rq = query(node * 2 + 1, mid + 1, hi, left, right);
    merge(ret, lq, rq);

    return ret;
}

inline void setup() {
    scan(N, M, S[0], S[1], XS, YS, ZS, O[0], O[1], XO, YO, ZO, A[0], A[1], XA, YA, ZA, B[0], B[1], XB, YB, ZB, C[0], C[1], XC, YC, ZC, D[0], D[1], XD, YD, ZD);

    for (long long i = 2; i < N; i++) {
        S[i] = (XS * S[i - 2] + YS * S[i - 1] + ZS) % MOD;
    }

    for (long long i = 2; i < M; i++) {
        O[i] = ((XO * O[i - 2] + YO * O[i - 1] + ZO) % 4) + 1;
        A[i] = ((XA * A[i - 2] + YA * A[i - 1] + ZA) % N) + 1;
        B[i] = ((XB * B[i - 2] + YB * B[i - 1] + ZB) % N) + 1;
        C[i] = (XC * C[i - 2] + YC * C[i - 1] + ZC) % MOD;
        D[i] = (XD * D[i - 2] + YD * D[i - 1] + ZD) % MOD;
    }

    build_seg_tree(1, 1, N);
}

inline long long handle_query(long long i) {
    long long ret = 0;

    switch (O[i]) {
        case 1: {
            long long right = A[i] + B[i] - 1;

            if (right > N) {
                update_linear(1, 1, N, A[i], N, D[i], (C[i] - D[i] * A[i]) % MOD);
                update_linear(1, 1, N, 1, right % N, D[i], (C[i] + D[i] * (N - A[i])) % MOD);
            } else {
                update_linear(1, 1, N, A[i], right, D[i], (C[i] - D[i] * A[i]) % MOD);
            }

            ret = (D[i] * ((B[i] * (B[i] - 1) / 2) % MOD) % MOD + C[i] * B[i] % MOD) % MOD;
        }
            break;
        case 2: {
            long long right = A[i] + B[i] - 1;

            if (right > N) {
                ret = (query(1, 1, N, A[i], N).sum + query(1, 1, N, 1, right % N).sum + (C[i] * B[i]) % MOD) % MOD;
                update_make_same(1, 1, N, A[i], N, C[i]);
                update_make_same(1, 1, N, 1, right % N, C[i]);
            } else {
                ret = (query(1, 1, N, A[i], right).sum + (C[i] * B[i]) % MOD) % MOD;
                update_make_same(1, 1, N, A[i], right, C[i]);
            }
        }
            break;
        case 3: {
            long long right = A[i] + B[i] - 1;

            if (right > N) {
                ret = (query(1, 1, N, A[i], N).sum + query(1, 1, N, 1, right % N).sum) % MOD;
            } else {
                ret = query(1, 1, N, A[i], right).sum;
            }
        }
            break;
        case 4: {
            long long right = A[i] + B[i] - 1;

            if (right > N) {
                ret = query(1, 1, N, A[i], N).oddcnt + query(1, 1, N, 1, right % N).oddcnt;
            } else {
                ret = query(1, 1, N, A[i], right).oddcnt;
            }
        }
            break;
        default: break;
    }

    return ret;
}

int main() {
    scan(T);

    for (long long t = 1; t <= T; t++) {
        setup();

        ans = 0;

        for (long long i = 0; i < M; i++) {
            ans = (ans + handle_query(i)) % MOD;
        }

        printf("Case #%lld: %lld\n", t, (ans + MOD) % MOD);
    }
    return 0;
}
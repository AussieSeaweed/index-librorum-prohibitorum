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
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
#define MOD 262144
using namespace std;

int N, Q, values[262144], block_size = 128, num_blocks, block_sum[2048][2048], last_ans, l, r, lb, rb, ans, lim, cnt[262144];
vector<int> indices[262144];

inline int get_count(int value, int lo, int hi) {
    return upper_bound(indices[value].begin(), indices[value].end(), hi) - lower_bound(indices[value].begin(), indices[value].end(), lo);
}

inline void solve(int i, int j) {
    int ql = i * block_size, qr = min(N - 1, (j + 1) * block_size - 1);

    while (l < ql) {
        ans = (ans - 2 * cnt[values[l]] + 1) % MOD;
        cnt[values[l]]--;
        l++;
    }

    while (l > ql) {
        l--;
        ans = (ans + 2 * cnt[values[l]] + 1) % MOD;
        cnt[values[l]]++;
    }

    while (r < qr) {
        r++;
        ans = (ans + 2 * cnt[values[r]] + 1) % MOD;
        cnt[values[r]]++;
    }

    while (r > qr) {
        ans = (ans - 2 * cnt[values[r]] + 1) % MOD;
        cnt[values[r]]--;
        r--;
    }

    block_sum[i][j] = ans;
}

int main() {
    pscan(N);
    pscan(Q);
    num_blocks = N / block_size + ((bool) (N % block_size));
    for (int i = 0; i < N; i++) {
        pscan(values[i]);
        indices[values[i]].push_back(i);
    }

    l = 0, r = -1;

    for (int i = 0; i < num_blocks; i++)
        if (i & 1)
            for (int j = num_blocks - 1; j >= 0; j--)
                solve(i, j);
        else
            for (int j = 0; j < num_blocks; j++)
                solve(i, j);

    while (Q--) {
        pscan(l);
        pscan(r);
        l ^= last_ans, r ^= last_ans;
        lb = l / block_size, rb = r / block_size;

        if (block_size - (l % block_size + 1) + r % block_size + 1 <= block_size) {
            if (rb - lb <= 1) {
                ans = 0;
                for (int i = l; i <= r; i++)
                    ans = (ans + get_count(values[i], l, r)) % MOD;
            } else {
                ans = block_sum[lb + 1][rb - 1];
                lim = min(N, (lb + 1) * block_size);
                int lim2 = rb * block_size;

                for (int i = l; i < lim; i++)
                    ans = (ans + 2 * get_count(values[i], i + 1, lim2 - 1) + 1) % MOD;

                for (int i = rb * block_size; i <= r; i++)
                    ans = (ans + 2 * get_count(values[i], l, i - 1) + 1) % MOD;
            }
        } else {
            ans = block_sum[lb][rb];
            lim = min(N, (rb + 1) * block_size);

            for (int i = lb * block_size; i < l; i++)
                ans = (ans - 2 * get_count(values[i], i, lim - 1) + 1) % MOD;

            for (int i = r + 1; i < lim; i++)
                ans = (ans - 2 * get_count(values[i], l, i) + 1) % MOD;
        }

        printf("%d\n", last_ans = (ans + MOD) % MOD);
    }

    return 0;
}
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

bool used[100000];
int N, K, l[100000], r[100000], intervals[100000], suboptimal[100000], S, ans, replaced[100000];
deque<int> cur;
vector<int> replacements[100000];

int solve(int i) {
    int ret = 0, last_r = 0;

    for (int index : replacements[i]) {
        if (last_r < l[index]) {
            ret++;
            last_r = r[index];
        }
    }

    return ret;
}

int solve(int i, int j) {
    unordered_set<int> indices;

    for (int index : replacements[i])
        indices.insert(index);

    for (int index : replacements[j])
        indices.insert(index);

    vector<int> replacements{ indices.begin(), indices.end() };
    sort(replacements.begin(), replacements.end(), [&] (int a, int b) -> bool { return r[a] == r[b] ? l[a] < l[b] : r[a] < r[b]; });

    int ret = 0, last_r = 0;

    for (int index : replacements) {
        if (last_r < l[index]) {
            ret++;
            last_r = r[index];
        }
    }

    return ret;
}

int main() {
    scan(N);
    scan(K);

    for (int i = 0; i < N; i++) {
        intervals[i] = i;
        scan(l[i]);
        scan(r[i]);
    }

    sort(intervals, intervals + N, [&] (int a, int b) -> bool { return l[a] == l[b] ? r[a] < r[b] : l[a] < l[b]; });

    for (int i = 0, last_r = 0; i < N; i++)
        if (last_r < l[intervals[i]])
            last_r = r[intervals[i]], suboptimal[S++] = intervals[i], used[intervals[i]] = true;

    ans = S;

    for (int i = 0, p = 0; i < N; i++)
        if (!used[intervals[i]])
            intervals[p++] = intervals[i];

    N -= S;

    sort(intervals, intervals + N, [&] (int a, int b) -> bool { return r[a] == r[b] ? l[a] < l[b] : r[a] < r[b]; });

    for (int i = 0, j = 0; i < S; i++) {
        int last_r = i == 0 ? 0 : r[suboptimal[i - 1]], next_l = i == S - 1 ? inf : l[suboptimal[i + 1]];

        while (!cur.empty() && r[cur.front()] <= last_r)
            cur.pop_front();

        while (j < N && r[intervals[j]] < next_l)
            cur.push_back(intervals[j++]);

        for (int index : cur)
            if (last_r < l[index])
                replacements[i].push_back(index);

        int current_gain = solve(i) - 1;
        ans = max(ans, S + current_gain);
        if (K == 2) ans = max(ans, S + current_gain + (i >= 2 ? replaced[i - 2] : 0));
        replaced[i] = max(i == 0 ? -inf : replaced[i - 1], current_gain);
    }

    if (K == 2) {
        for_each(replacements, replacements + S, [] (vector<int> &vec) -> void { vec.clear(); });
        cur.clear();

        for (int i = 1, j = 0; i < S; i++) {
            int last_r = i == 1 ? 0 : r[suboptimal[i - 2]], next_l = i == S - 1 ? inf : l[suboptimal[i + 1]];

            while (!cur.empty() && r[cur.front()] <= last_r)
                cur.pop_front();

            while (j < N && r[intervals[j]] < next_l)
                cur.push_back(intervals[j++]);

            for (int index : cur)
                if (last_r < l[index])
                    replacements[i].push_back(index);

            int current_gain = solve(i) - 2;
            ans = max(ans, S + current_gain);
            replaced[i] = max(replaced[i - 1], current_gain);
        }
    }

    printf("%d\n", ans);

    return 0;
}
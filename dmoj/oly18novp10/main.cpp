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
inline int ffs(int x) { return __builtin_ffs(x); }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x); }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename _EuclideanRingElement> inline _EuclideanRingElement euclidean(const _EuclideanRingElement &_m, const _EuclideanRingElement &_n) { return std::__gcd(_m, _n); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename ...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename ...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3fll
#define inf 0x3f3f3f3f
using namespace std;

int N, dp_left[2][40001], dp_right[2][40001], leftnode[40001], rightnode[40001], ans, topo[40000], ptr, parents[40001];
bool is_left[40001], is_right[40001];
vector<int> graph[40001];

void dfs(int node, int parent) {
    parents[node] = parent;
    if (is_left[node]) {
        dp_left[0][node] = dp_left[1][node] = 1;
        dp_right[0][node] = dp_right[1][node] = -1;
    } else {
        dp_left[0][node] = dp_left[1][node] = -1;
        dp_right[0][node] = dp_right[1][node] = 1;
    }

    for (int adj : graph[node]) {
        if (adj == parent) continue;
        dfs(adj, node);
        int left_val = dp_left[0][adj] + (is_left[node] ? 1 : -1), right_val = dp_right[0][adj] + (is_right[node] ? 1 : -1);

        if (dp_left[0][node] < left_val) {
            dp_left[1][node] = dp_left[0][node];
            dp_left[0][node] = left_val;
            leftnode[node] = adj;
        } else if (dp_left[1][node] < left_val) {
            dp_left[1][node] = left_val;
        }

        if (dp_right[0][node] < right_val) {
            dp_right[1][node] = dp_right[0][node];
            dp_right[0][node] = right_val;
            rightnode[node] = adj;
        } else if (dp_right[1][node] < right_val) {
            dp_right[1][node] = right_val;
        }
    }

    topo[ptr++] = node;
}

int main() {
    scan(N);

    for (int i = 2; i <= N; i++) {
        int node;
        scan(node);
        graph[i].push_back(node);
        graph[node].push_back(i);
    }

    for (int i = 1; i <= N; i++) {
        char ch;
        scanf(" %c", &ch);
        if (ch == '(')
            is_left[i] = true;
        else
            is_right[i] = true;
    }

    dfs(1, 0);

    for (int i = N - 1; i >= 0; i--) {
        int node = topo[i];

        if (node != 1) {
            int left_val = (leftnode[parents[node]] != node ? dp_left[0][parents[node]] : dp_left[1][parents[node]]) + (is_left[node] ? 1 : -1),
                    right_val = (rightnode[parents[node]] != node ? dp_right[0][parents[node]] : dp_right[1][parents[node]]) + (is_right[node] ? 1 : -1);

            if (dp_left[0][node] < left_val) {
                dp_left[1][node] = dp_left[0][node];
                dp_left[0][node] = left_val;
                leftnode[node] = parents[node];
            } else if (dp_left[1][node] < left_val) {
                dp_left[1][node] = left_val;
            }

            if (dp_right[0][node] < right_val) {
                dp_right[1][node] = dp_right[0][node];
                dp_right[0][node] = right_val;
                rightnode[node] = parents[node];
            } else if (dp_right[1][node] < right_val) {
                dp_right[1][node] = right_val;
            }
        }

        if (!leftnode[node] || !rightnode[node] || leftnode[node] != rightnode[node]) {
            int left_val = dp_left[0][node], right_val = dp_right[0][node];
            if (is_left[node]) right_val++; else left_val++;
            ans = max(ans, min(left_val, right_val));
        } else {
            int left_val = dp_left[0][node], right_val = dp_right[1][node];
            if (is_left[node]) right_val++; else left_val++;
            ans = max(ans, min(left_val, right_val));

            left_val = dp_left[1][node], right_val = dp_right[0][node];
            if (is_left[node]) right_val++; else left_val++;
            ans = max(ans, min(left_val, right_val));
        }
    }

    printf("%d\n", ans);
    return 0;
}
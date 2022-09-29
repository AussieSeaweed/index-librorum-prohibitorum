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

struct Node {
    int key;
    Node *left, *right;
    Node(int key) : key{ key }, left{}, right{} {}
} *nodes[500002];
int N, M, ptr, arr[500001], dp[500001], pred[500001], bit[500001], max_index;
bool marked[500001];

inline void update(int i, int j) {
    while (i <= N) {
        bit[i] = dp[bit[i]] > dp[j] ? bit[i] : j;
        i += i & -i;
    }
}

inline int query(int i) {
    int ret = 0;
    while (i) {
        ret = dp[ret] > dp[bit[i]] ? ret : bit[i];
        i -= i & -i;
    }
    return ret;
}

inline void link_before(Node *linking_node, Node *linked_node) {
    if (linking_node == linked_node) return;
    linking_node->left->right = linking_node->right, linking_node->right->left = linking_node->left;
    linking_node->left = linked_node->left, linking_node->right = linked_node;
    linking_node->left->right = linking_node;
    linking_node->right->left = linking_node;
}

int main() {
    scan(N);
    nodes[0] = new Node(0);
    for (int i = 1; i <= N + 1; i++) { nodes[i] = new Node(i); nodes[i - 1]->right = nodes[i], nodes[i]->left = nodes[i - 1]; }
    scan(M);

    while (M--) {
        char t; int A, B;
        scanf(" %c", &t);
        scan(A);
        scan(B);
        link_before(nodes[A], t == 'A' ? nodes[B] : nodes[B]->right);
    }

    for (int i = 0; i < N + 1; i = nodes[i]->right->key)
        arr[ptr++] = i;

    for (int i = 1; i <= N; i++) {
        pred[i] = query(arr[i]);
        dp[i] = 1 + dp[pred[i]];
        update(arr[i], i);
        max_index = dp[max_index] > dp[i] ? max_index : i;
    }

    for (int i = max_index; i; i = pred[i])
        marked[arr[i]] = true;

    printf("%d\n", N - dp[max_index]);

    if (!marked[1])
        printf("A 1 %d\n", arr[1]);

    for (int i = 2; i <= N; i++)
        if (!marked[i])
            printf("B %d %d\n", i, i - 1);

    return 0;
}
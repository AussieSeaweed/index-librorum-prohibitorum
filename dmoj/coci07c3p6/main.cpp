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

struct Node {
    int key, priority, size;
    Node *left, *right;
    Node(int key, int priority) : key{ key }, priority{ priority }, size{ 1 }, left{}, right{} {}
} *indices[10];

int N, M, a, b;
char str[250001];
Node *l[10], *m[10], *r[10];

inline int size(Node *node) {
    return node ? node->size : 0;
}

inline Node *update(Node *node) {
    node->size = size(node->left) + 1 + size(node->right);
    return node;
}

void split(Node *node, int key, Node *&left, Node *&right) {
    if (!node)
        left = right = nullptr;
    else if (node->key < key)
        split(node->right, key, node->right, right), left = update(node);
    else
        split(node->left, key, left, node->left), right = update(node);
}

void merge(Node *&node, Node *left, Node *right) {
    if (!left || !right)
        node = left ? left : right;
    else if (left->priority > right->priority)
        merge(left->right, left->right, right), node = update(left);
    else
        merge(right->left, left, right->left), node = update(right);
}

void insert(Node *&node, int key, int priority) {
    if (!node) node = new Node(key, priority);
    else if (priority > node->priority) {
        Node *ret = new Node(key, priority);
        split(node, key, ret->left, ret->right), node = update(ret);
    } else
        insert(key < node->key ? node->left : node->right, key, priority), node = update(node);
}

int main() {
    srand(time(nullptr));
    scan(N);
    scan(M);
    scanf("%s", str);

    for (int i = 0; i < N; i++)
        insert(indices[str[i] - '0'], i, rand());

    while (M--) {
        scan(a);
        scan(b);
        a--;

        int ans = 0;

        for (int i = 0; i < 10; i++)
            split(indices[i], a, l[i], m[i]), split(m[i], b, m[i], r[i]), ans += i * size(m[i]);

        for (int i = 0; i < 10; i++)
            merge(l[i], l[i], m[(i + 9) % 10]), merge(indices[i], l[i], r[i]);

        printf("%d\n", ans);
    }

    return 0;
}
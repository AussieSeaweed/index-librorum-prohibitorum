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
using namespace std;

struct Node {
    long long key, priority, size, sum;
    Node *left, *right;
    Node(long long key, long long priority) : key{ key }, priority{ priority }, sum{ key }, size{ 1 }, left{ nullptr }, right{ nullptr } {}
};

long long sum(Node *node) {
    return node ? node->sum : 0;
}

long long size(Node *node) {
    return node ? node->size : 0;
}

Node *update(Node *node) {
    node->sum = sum(node->left) + node->key + sum(node->right);
    node->size = size(node->left) + 1 + size(node->right);
    return node;
}

void split(Node *node, long long key, Node *&left, Node *&right) {
    if (!node)
        left = right = nullptr;
    else if (node->key < key || (node->key == key && rand() & 1))
        split(node->right, key, node->right, right), left = update(node);
    else
        split(node->left, key, left, node->left), right = update(node);
}

Node *join(Node *a, Node *b) {
    if (!a || !b) return a ? a : b;
    if (a->priority < b->priority) swap(a, b);
    Node *left = nullptr, *right = nullptr;
    split(b, a->key, left, right);
    a->left = join(a->left, left);
    a->right = join(a->right, right);
    return update(a);
}

Node *cut_treap(Node *node, long long s) {
    if (!node) return nullptr;

    if (s < sum(node->left) + node->key) {
        return cut_treap(node->left, s);
    } else {
        node->right = cut_treap(node->right, s - sum(node->left) - node->key);
        return update(node);
    }
}

int N;
Node *treap[100001];
long long ans, M, L[100001], B[100001], C[100001];

int main() {
    scan(N);
    scan(M);
    for (int i = 1; i <= N; i++) {
        scan(B[i]);
        scan(C[i]);
        scan(L[i]);
        treap[i] = new Node(C[i], rand());
    }
    for (int i = N; i >= 1; i--) {
        ans = max(ans, L[i] * size(treap[i]));
        treap[B[i]] = cut_treap(join(treap[B[i]], treap[i]), M);
    }
    printf("%lld\n", ans);
    return 0;
}
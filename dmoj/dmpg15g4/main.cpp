#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
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
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

struct Node {
    long double key;
    int priority, size;
    Node *left, *right;
    Node(long double key, int priority) : key{ key }, priority{ priority }, size{ 1 }, left{ nullptr }, right{ nullptr } {}
};

int size(Node *node) {
    return node ? node->size : 0;
}

Node *update(Node *node) {
    node->size = size(node->left) + 1 + size(node->right);
    return node;
}

void split(Node *node, long double key, Node *&left, Node *&right) {
    if (!node)
        left = right = nullptr;
    else if (node->key <= key)
        split(node->right, key, node->right, right), left = update(node);
    else
        split(node->left, key, left, node->left), right = update(node);
}

Node *insert(Node *node, long double key, int priority) {
    if (!node) return new Node(key, priority);
    if (priority > node->priority) {
        Node *ret = new Node(key, priority);
        split(node, key, ret->left, ret->right);
        return update(ret);
    } else if (key < node->key) {
        node->left = insert(node->left, key, priority);
    } else {
        node->right = insert(node->right, key, priority);
    }
    return update(node);
}

int ge_sz(Node *node, long double key) {
    if (!node) return 0;
    if (key <= node->key) {
        return size(node->right) + 1 + ge_sz(node->left, key);
    } else {
        return ge_sz(node->right, key);
    }
}

Node *root;
int N, X;
pair<long double, long double> angle[200000];
long long ans = 0;

int main() {
    scan(N);
    scan(X);

    for (int i = 0; i < N; i++) {
        int x, y;
        scan(x);
        scan(y);
        angle[i].first = atan2(y, x);
        angle[i].second = atan2(y, X - x);
    }

    sort(angle, angle + N, greater<pair<long double, long double>>());

    for (int i = 0; i < N; i++) {
        long long query = ge_sz(root, angle[i].second - 1e-9);
        ans += query * query;
        root = insert(root, angle[i].second, rand());
    }

    printf("%lld\n", ans);

    return 0;
}
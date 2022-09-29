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
    bool key, reverse;
    int priority, size, prefix, suffix, overall;
    Node *left, *right;
    Node(bool key, int priority) : key{ key }, priority{ priority }, size{ 1 }, left{ nullptr }, right{ nullptr }, reverse{ false }, prefix{ key }, suffix{ key }, overall{ key } {}
} *root;

int size(Node *node) {
    return node ? node->size : 0;
}

void handle_lazy(Node *node) {
    if (node) {
        if (node->reverse) {
            swap(node->prefix, node->suffix);
            swap(node->left, node->right);

            if (node->left) node->left->reverse = !node->left->reverse;
            if (node->right) node->right->reverse = !node->right->reverse;

            node->reverse = false;
        }
    }
}

Node *update(Node *node) {
    handle_lazy(node->left);
    handle_lazy(node->right);
    node->size = size(node->left) + 1 + size(node->right);

    if (node->left && node->right) {
        node->prefix = node->left->prefix == node->left->size && node->key ? node->left->prefix + 1 + node->right->prefix : node->left->prefix;
        node->suffix = node->right->suffix == node->right->size && node->key ? node->left->suffix + 1 + node->right->suffix : node->right->suffix;
        node->overall = max(node->left->overall, node->right->overall, node->prefix, node->suffix);
        if (node->key) node->overall = max(node->overall, node->left->suffix + 1 + node->right->prefix);
    } else if (node->left) {
        node->prefix = node->left->prefix == node->left->size && node->key ? node->left->prefix + 1 : node->left->prefix;
        node->suffix = node->key ? node->left->suffix + 1 : 0;
        node->overall = max(node->left->overall, node->prefix, node->suffix);
    } else if (node->right) {
        node->prefix = node->key ? 1 + node->right->prefix : 0;
        node->suffix = node->right->suffix == node->right->size && node->key ? 1 + node->right->suffix : node->right->suffix;
        node->overall = max(node->right->overall, node->prefix, node->suffix);
    } else {
        node->prefix = node->suffix = node->overall = node->key;
    }

    return node;
}

void split(Node *node, int index, Node *&left, Node *&right) {
    handle_lazy(node);

    if (!node)
        left = right = nullptr;
    else if (size(node->left) < index)
        split(node->right, index - size(node->left) - 1, node->right, right), left = update(node);
    else
        split(node->left, index, left, node->left), right = update(node);
}

void merge(Node *&node, Node *left, Node *right) {
    handle_lazy(left);
    handle_lazy(right);

    if (!left || !right)
        node = left ? left : right;
    else if (left->priority > right->priority)
        merge(left->right, left->right, right), node = update(left);
    else
        merge(right->left, left, right->left), node = update(right);
}

void insert_front(Node *&node, int key, int priority) {
    handle_lazy(node);

    if (!node)
        node = new Node(key, priority);
    else if (priority > node->priority) {
        Node *ret = new Node(key, priority);
        ret->right = node, node = update(ret);
    } else
        insert_front(node->left, key, priority), node = update(node);
}

void insert_back(Node *&node, int key, int priority) {
    handle_lazy(node);

    if (!node)
        node = new Node(key, priority);
    else if (priority > node->priority) {
        Node *ret = new Node(key, priority);
        ret->left = node, node = update(ret);
    } else
        insert_back(node->right, key, priority), node = update(node);
}

int N, Q;
char buffer[100002];

int main() {
    scan(N);
    scan(Q);
    scanf("%s", buffer);

    for (int i = N - 1; i >= 0; i--)
        insert_front(root, buffer[i] - '0', rand());

    while (Q--) {
        int t, i, l;
        Node *left, *middle, *right;
        scan(t);
        scan(i);
        scan(l);
        split(root, i, left, middle);
        split(middle, l, middle, right);

        if (t == 1) {
            middle->reverse = !middle->reverse;
        } else {
            printf("%d\n", middle->overall);
        }

        merge(root, left, middle);
        merge(root, root, right);
    }

    return 0;
}
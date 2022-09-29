#include <bits/stdc++.h>
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
    int key, priority, size;
    Node *left, *right;
    inline Node(int key, int priority) : key{ key }, priority{ priority }, size{ 1 }, left{ nullptr }, right{ nullptr } {}
};

inline int size(Node *node) {
    return node ? node->size : 0;
}

inline void handle_lazy(Node *node) {
    if (node) {

    }
}

inline Node *update(Node *node) {
    handle_lazy(node->left);
    handle_lazy(node->right);
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
    if (!node)
        node = new Node(key, priority);
    else if (priority > node->priority) {
        Node *ret = new Node(key, priority);
        split(node, key, ret->left, ret->right), node = update(ret);
    } else
        insert(key < node->key ? node->left : node->right, key, priority), node = update(node);
}

void erase(Node *&node, int key) {
    if (!node)
        return;
    else if (key == node->key) {
        Node *left = node->left, *right = node->right;
        delete node;
        merge(node, left, right);
    } else
        erase(key < node->key ? node->left : node->right, key), node = update(node);
}

void join(Node *&node, Node *a, Node *b) {
    handle_lazy(a);
    handle_lazy(b);

    if (!a || !b) { node = a ? a : b; return; }
    if (a->priority < b->priority) swap(a, b);
    Node *left, *right;
    split(b, a->key, left, right);
    join(a->left, a->left, left);
    join(a->right, a->right, right);
    node = update(a);
}

int order_of_key(Node *node, int key) {
    handle_lazy(node);

    if (!node)
        return -1;
    else if (key < node->key)
        return order_of_key(node->left, key);
    else if (node->key < key) {
        int query = order_of_key(node->right, key);
        return ~query ? query + size(node->left) + 1 : query;
    } else {
        int query = order_of_key(node->left, key);
        return ~query ? query : size(node->left);
    }
}

int find_by_order(Node *node, int index) {
    handle_lazy(node);

    if (!node)
        throw runtime_error("Error: Treap index out of range.\n");
    else if (index < size(node->left))
        return find_by_order(node->left, index);
    else if (size(node->left) < index)
        return find_by_order(node->right, index - size(node->left) - 1);
    else
        return node->key;
}

bool exists(Node *node, int key) {
    handle_lazy(node);

    if (!node)
        return false;
    else if (key == node->key)
        return true;
    else
        return exists(key < node->key ? node->left : node->right, key);
}

void print_treap(Node *node) {
    if (!node) return;
    print_treap(node->left);
    printf("%d ", node->key);
    print_treap(node->right);
}

int main() {
    Node *root = nullptr;
    int N, M, output = 0;
    scanf("%d%d", &N, &M);

    while (N--) {
        int value;
        scanf("%d", &value);
        insert(root, value, rand());
    }

    while (M--) {
        char T;
        int v;
        scanf(" %c%d", &T, &v);
        v ^= output;

        switch (T) {
            case 'I': {
                insert(root, v, rand());
            }
                break;
            case 'R': {
                erase(root, v);
            }
                break;
            case 'S': {
                output = find_by_order(root, v - 1);
                printf("%d\n", output);
            }
                break;
            case 'L': {
                int order = order_of_key(root, v);
                output = order == -1 ? -1 : order + 1;
                printf("%d\n", output);
            }
                break;
            default: break;
        }
    }

    print_treap(root);
    printf("\n");

    return 0;
}
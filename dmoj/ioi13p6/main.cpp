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

int R, C;

struct treap_node {
    pair<int, int> key;
    int priority, min_key, max_key;
    long long value, gcd;
    treap_node *left, *right;
    inline treap_node(pair<int, int> &key, long long value, int priority) : key{ key }, value{ value }, priority{ priority }, gcd{ value }, min_key{ key.first }, max_key{ key.first }, left{ nullptr }, right{ nullptr } {}
};

inline long long gcd(treap_node *node) {
    return node ? node->gcd : 0;
}

inline int min_key(treap_node *node) {
    return node ? node->min_key : inf;
}

inline int max_key(treap_node *node) {
    return node ? node->max_key : -inf;
}

inline treap_node *update(treap_node *node) {
    node->gcd = euclidean(euclidean(gcd(node->right), gcd(node->left)), node->value);
    node->min_key = min(min_key(node->left), node->key.first, min_key(node->right));
    node->max_key = max(max_key(node->left), node->key.first, max_key(node->right));
    return node;
}

inline treap_node *rotate_left(treap_node *node) {
    treap_node *right = node->right;
    node->right = right->left;
    right->left = node;
    node = right;
    update(node->left);
    update(node);
    return node;
}

inline treap_node *rotate_right(treap_node *node) {
    treap_node *left = node->left;
    node->left = left->right;
    left->right = node;
    node = left;
    update(node->right);
    update(node);
    return node;
}

inline treap_node *reorder(treap_node *node) {
    if (node->right && node->right->priority > node->priority) node = rotate_left(node);
    else if (node->left && node->left->priority > node->priority) node = rotate_right(node);
    else update(node);
    return node;
}

void split(treap_node *node, pair<int, int> key, treap_node *&left, treap_node *&right) {
    if (!node)
        left = right = nullptr;
    else if (node->key < key)
        split(node->right, key, node->right, right), left = update(node);
    else
        split(node->left, key, left, node->left), right = update(node);
}

void merge(treap_node *&node, treap_node *left, treap_node *right) {
    if (!left || !right)
        node = left ? left : right;
    else if (left->priority > right->priority)
        merge(left->right, left->right, right), node = update(left);
    else
        merge(right->left, left, right->left), node = update(right);
}

void insert(treap_node *&node, pair<int, int> key, long long value) {
    if (!node) node = new treap_node(key, value, rand());
    else if (key == node->key) node->value = value, node = update(node);
    else insert(key < node->key ? node->left : node->right, key, value), node = reorder(node);
}

long long query_range(treap_node *node, int left, int right) {
    if (!node || right < node->min_key || node->max_key < left)
        return 0;
    if (left <= node->min_key && node->max_key <= right)
        return gcd(node);
    long long query = euclidean(query_range(node->left, left, right), query_range(node->right, left, right));
    if (left <= node->key.first && node->key.first <= right) query = euclidean(query, node->value);
    return query;
}

struct Data {
    treap_node *root = nullptr;
    long long gcd = 0;
};

struct seg_tree_node {
    Data data;
    seg_tree_node *left, *right;
    seg_tree_node() : data{}, left{}, right{} {}
} *root;

void merge(Data &data, Data left, Data right) {
    data.gcd = euclidean(left.gcd, right.gcd);
}

void update(seg_tree_node *&node, int lo, int hi, int index, int key, long long value) {
    if (index < lo || hi < index) return;
    if (!node) node = new seg_tree_node();

    insert(node->data.root, {key, index}, value);

    if (lo == hi) {
    } else {
        int mid = lo + (hi - lo) / 2;
        update(node->left, lo, mid, index, key, value);
        update(node->right, mid + 1, hi, index, key, value);
        merge(node->data, node->left ? node->left->data : Data(), node->right ? node->right->data : Data());
    }
}

Data query(seg_tree_node *node, int lo, int hi, int left, int right, int down, int up) {
    if (!node || right < lo || hi < left) return Data();
    else if (left <= lo && hi <= right) return {0, query_range(node->data.root, down, up)};

    int mid = lo + (hi - lo) / 2;
    Data ret;
    merge(ret, query(node->left, lo, mid, left, right, down, up), query(node->right, mid + 1, hi, left, right, down, up));

    return ret;
}

void init(int R, int C) { srand(time(nullptr)); ::R = R, ::C = C; }

void update(int P, int Q, long long K) {
    update(root, 0, R - 1, P, Q, K);
}

long long calculate(int P, int Q, int U, int V) {
    return query(root, 0, R - 1, P, U, Q, V).gcd;
}

int main() {
    init(2, 3);
    update(0, 0, 20);
    update(0, 2, 15);
    update(1, 1, 12);
    cout << calculate(0, 0, 0, 2) << endl;
    cout << calculate(0, 0, 1, 1) << endl;
    update(0, 1, 6);
    update(1, 1, 14);
    cout << calculate(0, 0, 0, 2) << endl;
    cout << calculate(0, 0, 1, 1) << endl;
    return 0;
}
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
    long long key, sum, priority, size;
    Node *left, *right;
    Node(long long key, long long priority) : key{ key }, priority{ priority }, sum{ key }, size{ 1 }, left{ nullptr }, right{ nullptr } {}
} *l, *r;
int K, N, n;
long long ans, base;
pair<long long, long long> interval[100000];

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
    else if (node->key <= key)
        split(node->right, key, node->right, right), left = update(node);
    else
        split(node->left, key, left, node->left), right = update(node);
}

Node *merge(Node *left, Node *right) {
    if (!left || !right)
        return left ? left : right;
    else if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return update(left);
    } else {
        right->left = merge(left, right->left);
        return update(right);
    }
}

Node *insert(Node *node, long long key, long long priority) {
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

Node *erase(Node *node, long long key) {
    if (!node) return node;
    if (key < node->key) {
        node->left = erase(node->left, key);
    } else if (node->key < key) {
        node->right = erase(node->right, key);
    } else {
        Node *left = node->left, *right = node->right;
        delete node;
        return merge(left, right);
    }
    return update(node);
}

long long find_by_order(Node *node, long long index) {
    if (!node) return -1;
    if (index < size(node->left)) {
        return find_by_order(node->left, index);
    } else if (size(node->left) < index) {
        return find_by_order(node->right, index - size(node->left) - 1);
    } else {
        return node->key;
    }
}

long long solve(Node *&node, long long middle_element) {
    Node *left, *middle, *right;
    split(node, middle_element - 1, left, middle);
    split(middle, middle_element, middle, right);
    long long ret = size(left) * middle_element - sum(left) + sum(right) - size(right) * middle_element;
    node = merge(left, merge(middle, right));
    ret += size(node) / 2;
    return ret;
}

long long solve(Node *&node) {
    return solve(node, find_by_order(node, size(node) / 2));
}

int main() {
    scan(K);
    scan(N);
    for (int i = 0; i < N; i++) {
        char a, b;
        long long ax, bx;
        scanf(" %c", &a);
        scan(ax);
        scanf(" %c", &b);
        scan(bx);
        if (ax > bx) swap(ax, bx);
        if (a == b) base += bx - ax;
        else {
            interval[n++] = {ax, bx};
            r = insert(r, ax, rand());
            r = insert(r, bx, rand());
        }
    }
    ans = solve(r) + base;

    if (K == 1) {
        printf("%lld\n", ans);
    } else {
        sort(interval, interval + n, [] (const pair<long long, long long> &a, const pair<long long, long long> &b) -> bool { return a.first + a.second < b.first + b.second; });
        for (int i = 0; i < n; i++) {
            l = insert(l, interval[i].first, rand());
            l = insert(l, interval[i].second, rand());
            r = erase(r, interval[i].first);
            r = erase(r, interval[i].second);
            ans = min(ans, solve(l) + solve(r) + base);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
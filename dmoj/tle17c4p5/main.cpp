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

int N;
long long M;
vector<long long> prime_factors[200001];

struct Node {
    int priority;
    long long key, product;
    Node *left, *right;
    inline Node(long long key, int priority) : key{ key }, priority{ priority }, product{ key }, left{}, right{} {}
} *root;

inline long long product(Node *node) {
    return node ? node->product : 1;
}

inline Node *update(Node *node) {
    node->product = product(node->left) * node->key % M * product(node->right) % M;
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

void merge(Node *&node, Node *left, Node *right) {
    if (!left || !right)
        node = left ? left : right;
    else if (left->priority > right->priority)
        merge(left->right, left->right, right), node = update(left);
    else
        merge(right->left, left, right->left), node = update(right);
}

void insert(Node *&node, long long key, int priority) {
    if (!node)
        node = new Node(key, priority);
    else if (priority > node->priority) {
        Node *ret = new Node(key, priority);
        split(node, key, ret->left, ret->right), node = update(ret);
    } else
        insert(key < node->key || (key == node->key && rand() & 1) ? node->left : node->right, key, priority), node = update(node);
}

void erase(Node *&node, long long key) {
    if (!node)
        node = nullptr;
    else if (node->key == key) {
        Node *left = node->left, *right = node->right;
        delete node;
        merge(node, left, right);
    } else
        erase(key < node->key ? node->left : node->right, key), node = update(node);
}

void sieve() {
    for (int i = 2; i <= N; i++) {
        if (prime_factors[i].empty()) {
            for (int j = i; j <= N; j += i) {
                int k = j;
                while (k && k % i == 0)
                    prime_factors[j].push_back(i % M), k /= i;
            }
        }
    }
}

int main() {
    scan(N);
    scan(M);
    sieve();

    printf("1\n");

    for (int i = 1; i <= N; i++) {
        for (long long factor : prime_factors[N - i + 1])
            insert(root, factor, rand());
        for (long long factor : prime_factors[i])
            erase(root, factor);
        printf("%lld\n", product(root));
    }

    return 0;
}
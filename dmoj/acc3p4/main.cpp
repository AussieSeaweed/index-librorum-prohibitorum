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

int N, Q;

struct Data {
    long long m = 0, b = 0, value = 0;
};

struct Node {
    Data data;
    Node *left, *right;
    Node() : data{}, left{}, right{} {}
} *root;

void merge(Data &data, Data left, Data right) {
    data.value = left.value + right.value;
}

void handle_lazy(Node *node, int lo, int hi) {
    Data &data = node->data;

    if (data.m || data.b) {
        data.value += data.m * (hi - lo + 1) * (lo + hi) / 2 + data.b * (hi - lo + 1);

        if (lo != hi) {
            node->left->data.m += node->data.m;
            node->left->data.b += node->data.b;
            node->right->data.m += node->data.m;
            node->right->data.b += node->data.b;
        }

        data.m = data.b = 0;
    }
}

void build_seg_tree(Node *&node, int lo, int hi) {
    node = new Node();

    if (lo == hi) {

    } else {
        int mid = lo + (hi - lo) / 2;
        build_seg_tree(node->left, lo, mid);
        build_seg_tree(node->right, mid + 1, hi);
        merge(node->data, node->left->data, node->right->data);
    }
}

void update_range(Node *node, int lo, int hi, int left, int right, int m, int b) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return;
    else if (left <= lo && hi <= right) {
        node->data.m += m;
        node->data.b += b;
        handle_lazy(node, lo, hi);
    } else {
        int mid = lo + (hi - lo) / 2;
        update_range(node->left, lo, mid, left, right, m, b);
        update_range(node->right, mid + 1, hi, left, right, m, b);
        merge(node->data, node->left->data, node->right->data);
    }
}

void update(Node *node, int lo, int hi, int index, int delta) {
    handle_lazy(node, lo, hi);
    if (index < lo || hi < index) return;
    else if (lo == hi) {
        node->data.value += delta;
    } else {
        int mid = lo + (hi - lo) / 2;
        update(node->left, lo, mid, index, delta);
        update(node->right, mid + 1, hi, index, delta);
        merge(node->data, node->left->data, node->right->data);
    }
}

Data query(Node *node, int lo, int hi, int left, int right) {
    handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return Data();
    else if (left <= lo && hi <= right) return node->data;

    int mid = lo + (hi - lo) / 2;
    Data ret;
    merge(ret, query(node->left, lo, mid, left, right), query(node->right, mid + 1, hi, left, right));

    return ret;
}

int main() {
    scan(N);
    scan(Q);
    build_seg_tree(root, 1, N);
    while (Q--) {
        int t;
        scan(t);
        int l, r, a;
        scan(l);
        scan(r);
        if (t == 1) {
            scan(a);
            if (l != r) update_range(root, 1, N, l, r, a, - a * l + a);
            else update(root, 1, N, l, a);
        } else {
            printf("%lld\n", query(root, 1, N, l, r).value);
        }
    }
    return 0;
}
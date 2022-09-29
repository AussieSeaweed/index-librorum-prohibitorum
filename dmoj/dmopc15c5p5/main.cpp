#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
#define MOD 1000000007
using namespace std;

struct Node {
    long long key, value, size, total, priority;
    Node *left, *right;

    Node(long long key, long long value, long long priority) : key{ key }, value{ value }, priority{ priority }, total{ value }, size{ 1 }, left{ nullptr }, right{ nullptr } {}
};

long long size(Node *node) {
    return node ? node->size : 0;
}

long long total(Node *node) {
    return node ? node->total : 0;
}

Node *update(Node *node) {
    if (node) {
        node->size = size(node->left) + 1 + size(node->right);
        node->total = (total(node->left) + node->value + total(node->right)) % MOD;
    }

    return node;
}

void split(Node *node, long long key, Node *&left, Node *&right) {
    if (!node) {
        left = right = nullptr;
    } else if (node->key < key) {
        split(node->right, key, node->right, right), left = update(node);
    } else {
        split(node->left, key, left, node->left), right = update(node);
    }
}

Node *merge(Node *left, Node *right) {
    if (!left || !right) {
        return left ? left : right;
    } else if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return update(left);
    } else {
        right->left = merge(left, right->left);
        return update(right);
    }
}

Node *insert(Node *node, long long key, long long value, long long priority) {
    if (!node) return new Node(key, value, priority);

    if (priority > node->priority) {
        Node *ret = new Node(key, value, priority);

        split(node, key, ret->left, ret->right);

        return update(ret);
    } else if (key < node->key) {
        node->left = insert(node->left, key, value, priority);
    } else {
        node->right = insert(node->right, key, value, priority);
    }

    return update(node);
}

Node *join(Node *a, Node *b) {
    if (!a || !b) return a ? a : b;
    if (a->priority < b->priority) swap(a, b); // a is root
    Node *left, *right;
    split(b, a->key, left, right);
    a->left = join(a->left, left);
    a->right = join(a->right, right);
    return update(a);
}

long long t[200001], refcnt[200001], ans[200001];
int N, root;
vector<int> graph[200001];

Node *dfs(int node) {
    if (!refcnt[node]) {
        ans[node] = 1;
        return new Node(t[node], 1, rand());
    }

    Node *rt = nullptr;

    for (int adj : graph[node]) {
        rt = join(rt, dfs(adj));
    }

    Node *left = nullptr, *right = nullptr;
    split(rt, t[node], left, right);
    ans[node] = total(left) + 1;
    rt = merge(left, right);
    rt = insert(rt, t[node], ans[node], rand());

    return rt;
}

int main() {
    scan(N);

    for (int i = 1; i <= N; i++) {
        int parent;
        scan(parent);

        if (!parent) {
            root = i;
        } else {
            graph[parent].push_back(i);
            refcnt[parent]++;
        }
    }

    for (int i = 1; i <= N; i++) {
        int node;
        scan(node);
        t[node] = i;
    }

    dfs(root);

    for (int i = 1; i <= N; i++)
        printf("%lld ", ans[i]);
    printf("\n");

    return 0;
}
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int uf[100001], sz[100001];

int id(int node) {
    return node == uf[node] ? node : uf[node] = id(uf[node]);
}

bool connected(int a, int b) {
    return id(a) == id(b);
}

int connect(int a, int b) {
    a = id(a), b = id(b);

    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        uf[b] = a;
        sz[a] += sz[b];
        return a;
    }

    return -1;
}

int size(int node) {
    return sz[id(node)];
}

void init_uf(int N) {
    for (int i = 1; i <= N; i++)
        uf[i] = i;
    fill(sz, sz + N + 1, 1);
}

struct Node {
    int key, value, priority, size;
    Node *left, *right;

    Node(int key, int value, int priority) : key{ key }, value{ value }, size{ 1 }, priority{ priority } {}
} *roots[100001];

int size(Node *node) {
    return node ? node->size : 0;
}

Node *update(Node *node) {
    if (node)
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

Node *insert(Node *node, int key, int value, int priority) {
    if (!node) return new Node(key, value, priority);

    if (priority > node->priority) {
        Node *ret = new Node(key, value, priority);
        split(node, key, ret->left, ret->right);
        return update(ret);
    } else if (key < node->key) {
        node->left = insert(node->left, key, value, priority);
    } else if (node->key < key) {
        node->right = insert(node->right, key, value, priority);
    }

    return update(node);
}

int find_by_order(Node *node, int index) {
    if (!node) return -1;

    if (size(node->left) + 1 == index) {
        return node->value;
    } else if (index <= size(node->left)) {
        return find_by_order(node->left, index);
    } else {
        return find_by_order(node->right, index - size(node->left) - 1);
    }
}

Node *unite(Node *a, Node *b) {
    if (!a || !b) return a ? a : b;
    if (a->priority < b->priority) swap(a, b);
    Node *c, *d;
    split(b, a->key, c, d);
    a->left = unite(a->left, c);
    a->right = unite(a->right, d);
    return update(a);
}

int main() {
    int N, M;
    scan(N);
    scan(M);
    init_uf(N);

    for (int i = 1; i <= N; ++i) {
        int key;
        scan(key);
        roots[i] = insert(roots[i], key, i, rand());
    }

    while (M--) {
        int u, v;
        scan(u);
        scan(v);
        u = id(u);
        v = id(v);
        if (u != v) {
            int node = connect(u, v);
            roots[node] = unite(roots[node], roots[node == u ? v : u]);
        }
    }

    int Q;
    scan(Q);

    while (Q--) {
        char t;
        scanf(" %c", &t);

        switch (t) {
            case 'Q': {
                int x, y;
                scan(x);
                scan(y);
                x = id(x);
                printf("%d\n", find_by_order(roots[x], y));
            }
                break;
            case 'B': {
                int u, v;
                scan(u);
                scan(v);
                u = id(u);
                v = id(v);
                if (u != v) {
                    int node = connect(u, v);
                    roots[node] = unite(roots[node], roots[node == u ? v : u]);
                }
            }
                break;
            default: break;
        }
    }

    return 0;
}
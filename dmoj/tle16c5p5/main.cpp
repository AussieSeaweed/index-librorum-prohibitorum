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
using namespace std;

bool equals(double a, double b) {
    return a - 0.0001 < b && b < a + 0.0001;
}

double R, r[200001], pts[200000];
int N;

struct Node {
    double key, total;
    int priority, size;
    Node *left, *right;
    Node(double key, int priority) : key{ key }, total{ key }, priority{ priority }, size{ 1 }, left{ nullptr }, right{ nullptr } {};
} *root = nullptr;

double total(Node *node) {
    return node ? node->total : 0;
}

int size(Node *node) {
    return node ? node->size : 0;
}

Node *update(Node *node) {
    if (node) {
        node->size = size(node->left) + 1 + size(node->right);
        node->total = total(node->left) * r[size(node->right) + 1] + node->key * r[size(node->right)] + total(node->right);
    }

    return node;
}

void split(Node *node, double key, Node *&left , Node *&right) {
    if (!node)
        left = right = nullptr;
    else if (node->key < key)
        split(node->right, key, node->right, right), left = update(node);
    else
        split(node->left, key, left, node->left), right = update(node);
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

Node *insert(Node *node, double key, int priority) {
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

Node *erase(Node *node, double key) {
    if (!node) return nullptr;

    if (equals(node->key, key)) {
        Node *left = node->left, *right = node->right;
        delete node;
        return merge(left, right);
    } else if (key < node->key) {
        node->left = erase(node->left, key);
    } else {
        node->right = erase(node->right, key);
    }

    return update(node);
}

int main() {
    scanf("%lf", &R);
    scan(N);
    r[0] = 1;
    for (int i = 1; i <= N; i++) {
        r[i] = R * r[i - 1];
    }
    while (N--) {
        int p;
        double v;
        scan(p);
        scanf("%lf", &v);
        if (v > pts[p]) {
            root = erase(root, pts[p]);
            root = insert(root, v, rand());
            pts[p] = v;
        }
        printf("%.9lf\n", total(root));
    }
    return 0;
}
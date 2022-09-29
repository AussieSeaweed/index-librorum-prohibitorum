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

struct Node {
    int key, priority, size;
    Node *left, *right;
    Node (int key, int priority) : key{ key }, priority{ priority }, size{ 1 }, left{ nullptr }, right{ nullptr } {}
} *root = nullptr;

int T;

int size(Node *node) {
    return node ? node->size : 0;
}

Node *update(Node *node) {
    node->size = size(node->left) + 1 + size(node->right);
    return node;
}

pair<Node *, Node *> split(Node *node, int key) {
    if (!node) return {nullptr, nullptr};
    else if (key < node->key) {
        pair<Node *, Node *> query = split(node->left, key);
        node->left = query.second;
        return {query.first, update(node)};
    } else {
        pair<Node *, Node *> query = split(node->right, key);
        node->right = query.first;
        return {update(node), query.second};
    }
}

Node *insert(Node *node, int key, int priority) {
    if (!node) return new Node(key, priority);

    if (priority > node->priority) {
        Node *ret = new Node(key, priority);
        pair<Node *, Node *> query = split(node, key);
        ret->left = query.first;
        ret->right = query.second;
        return update(ret);
    } else if (key < node->key) {
        node->left = insert(node->left, key, priority);
    } else {
        node->right = insert(node->right, key, priority);
    }

    return update(node);
}

int rev_order_of_key(Node *node, int key) {
    if (!node) return -1;

    if (key == node->key) {
        int query = rev_order_of_key(node->right, key);
        return query == -1 ? size(node->right) : query;
    } else if (key < node->key) {
        int query = rev_order_of_key(node->left, key);
        return query == -1 ? -1 : size(node->right) + 1 + query;
    } else {
        return rev_order_of_key(node->right, key);
    }
}

int main() {
    srand(time(nullptr));
    scan(T);

    double ans = 0;

    for (int i = 0; i < T; i++) {
        int key;
        scan(key);
        root = insert(root, key, rand());
        ans += rev_order_of_key(root, key) + 1;
    }

    printf("%.2lf\n", ans / T);

    return 0;
}
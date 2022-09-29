#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, M, K;

struct Node {
    int key, value, size, priority, cnt[20];
    Node *left, *right;
    Node(int key, int value, int priority) : key{ key }, value{ value }, size{ value }, priority{ priority }, cnt{}, left{ nullptr }, right{ nullptr } {
        cnt[key] = value;
    }
} *root = nullptr;

int get_size(Node *node) {
    return node ? node->size : 0;
}

Node *update(Node *node) {
    if (node) {
        node->size = get_size(node->left) + node->value + get_size(node->right);

        for (int i = 0; i < 20; i++)
            node->cnt[i] = 0;

        node->cnt[node->key] = node->value;

        if (node->left && node->right) {
            for (int i = 0; i < 20; i++)
                node->cnt[i] += node->left->cnt[i] + node->right->cnt[i];
        } else if (node->left) {
            for (int i = 0; i < 20; i++)
                node->cnt[i] += node->left->cnt[i];
        } else if (node->right) {
            for (int i = 0; i < 20; i++)
                node->cnt[i] += node->right->cnt[i];
        }
    }

    return node;
}

Node *insert_back(Node *node, int key, int value, int priority) {
    if (!node) return new Node(key, value, priority);

    if (node->priority < priority) {
        Node *ret = new Node(key, value, priority);
        ret->left = node;
        return update(ret);
    } else {
        node->right = insert_back(node->right, key, value, priority);
        return update(node);
    }
}

void split(Node *node, int index, Node *&left, Node *&right) { // 0-indexed
    if (!node)
        left = right = nullptr;
    else if (index <= get_size(node->left))
        split(node->left, index, left, node->left), right = update(node);
    else if (get_size(node->left) + node->value <= index)
        split(node->right, index - get_size(node->left) - node->value, node->right, right), left = update(node);
    else {
        index -= get_size(node->left);
        Node *l = new Node(node->key, index, node->priority), *r = new Node(node->key, node->value - index, node->priority);
        l->left = node->left, r->right = node->right;
        left = update(l);
        right = update(r);
    }
}

Node *merge(Node *left, Node *right) {
    if (!left || !right) {
        return update(left ? left : right);
    } else if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return update(left);
    } else {
        right->left = merge(left, right->left);
        return update(right);
    }
}

void print_treap(Node *node) {
    if (node) {
        print_treap(node->left);

        for (int i = 0; i < node->value; i++)
            printf("%d ", node->key + 1);

        print_treap(node->right);
    }
}

int main() {
    scan(N);
    scan(M);
    scan(K);

    for (int i = 0; i < N; i++) {
        int a;
        scan(a);
        --a;
        root = insert_back(root, a, 1, rand());
    }

    while (M--) {
        int l, r;
        scan(l);
        scan(r);
        r = r - l + 1;
        --l;
        Node *left, *middle, *right;
        split(root, l, left, middle);
        split(middle, r, middle, right);

        Node *new_middle = nullptr;

        for (int i = 0; i < K; i++) {
            int p;
            scan(p);
            --p;
            if (middle->cnt[p])
                new_middle = insert_back(new_middle, p, middle->cnt[p], rand());
        }

        root = merge(merge(left, new_middle), right);
    }

    print_treap(root);
    printf("\n");

    return 0;
}
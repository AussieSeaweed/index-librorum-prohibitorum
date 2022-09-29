#include <iostream>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

struct Node {
    int key, person;
    int size, priority;
    Node *left, *right;

    Node(int key, int person, int priority) : key{ key }, person{ person }, priority{ priority }, size{ 1 },
                                                    left{ nullptr }, right{ nullptr } {}
} *root = nullptr;

int N, ratings[1000001];

int size(Node *node) {
    return node ? node->size : 0;
}

Node *update(Node *node) {
    if (node) node->size = size(node->left) + 1 + size(node->right);
    return node;
}

Node *merge(Node *left, Node *right) {
    if (!left || !right) return left ? left : right;
    else if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return update(left);
    } else {
        right->left = merge(left, right->left);
        return update(right);
    }
}

void split(Node *node, int key, Node *&left, Node *&right) {
    if (!node)
        left = right = nullptr;
    else if (key > node->key)
        split(node->left, key, left, node->left), right = update(node);
    else
        split(node->right, key, node->right, right), left = update(node);
}

Node *insert(Node *node, int key, int person, int priority) {
    if (!node) return new Node(key, person, priority);
    else if (priority > node->priority) {
        Node *ret = new Node(key, person, priority);
        split(node, key, ret->left, ret->right);
        return update(ret);
    } else if (key > node->key) {
        node->left = insert(node->left, key, person, priority);
    } else {
        node->right = insert(node->right, key, person, priority);
    }

    return update(node);
}

Node *erase(Node *node, int key) {
    if (!node) return node;

    if (key == node->key) {
        Node *left = node->left, *right = node->right;
        delete node;
        return merge(left, right);
    } else if (key > node->key) {
        node->left = erase(node->left, key);
    } else {
        node->right = erase(node->right, key);
    }

    return update(node);
}

int query(Node *node, int index) {
    if (size(node->left) == index) {
        return node->person;
    } else if (index < size(node->left)) {
        return query(node->left, index);
    } else {
        return query(node->right, index - size(node->left) - 1);
    }
}

int main() {
    scan(N);

    while (N--) {
        char t;
        scanf(" %c", &t);

        switch (t) {
            case 'N': {
                int x, r;
                scan(x); scan(r);
                root = insert(root, r, x, rand());
                ratings[x] = r;
            }
                break;
            case 'M': {
                int x, r;
                scan(x); scan(r);
                root = erase(root, ratings[x]);
                root = insert(root, r, x, rand());
                ratings[x] = r;
            }
                break;
            case 'Q': {
                int K;
                scan(K);
                printf("%d\n", query(root, K - 1));
            }
                break;
            default: break;
        }
    }

    return 0;
}
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Node {
    int key, freq, lazy, priority;
    long long sum, size;
    Node *left, *right;
    Node(int key, int priority) : key{ key }, priority{ priority }, sum{ key }, freq{ 1 }, size{ 1 }, lazy{ 0 },
                                  left{ nullptr }, right{ nullptr } {}
} *left_root = nullptr, *right_root = nullptr;

inline void handle_lazy(Node *node) {
    if (node) {
        if (node->lazy) {
            node->key += node->lazy;
            node->sum += node->lazy * node->size;

            if (node->left) node->left->lazy += node->lazy;
            if (node->right) node->right->lazy += node->lazy;

            node->lazy = 0;
        }
    }
}

inline long long sum(Node *node) {
    if (node) handle_lazy(node);
    return node ? node->sum : 0;
}

inline long long size(Node *node) {
    if (node) handle_lazy(node);
    return node ? node->size : 0;
}

inline bool is_lazy(Node *node) {
    return node ? node->lazy != 0 : false;
}

inline void lazily_update(Node *node, long long lazy) {
    if (node) {
        node->lazy += lazy;
        handle_lazy(node);
    }
}

inline bool ordered(Node *a, Node *b) {
    return b ? a->priority > b->priority : true;
}

inline Node *rotate_left(Node *node) {
    Node *right = node->right;
    node->right = right->left;
    right->left = node;

    node->sum = sum(node->left) + node->freq * node->key + sum(node->right);
    node->size = size(node->left) + node->freq + size(node->right);

    right->sum = sum(right->left) + right->freq * right->key + sum(right->right);
    right->size = size(right->left) + right->freq + size(right->right);

    return right;
}

inline Node *rotate_right(Node *node) {
    Node *left = node->left;
    node->left = left->right;
    left->right = node;

    node->sum = sum(node->left) + node->freq * node->key + sum(node->right);
    node->size = size(node->left) + node->freq + size(node->right);

    left->sum = sum(left->left) + left->freq * left->key + sum(left->right);
    left->size = size(left->left) + left->freq + size(left->right);

    return left;
}

inline Node *update(Node *node) {
    if (node) {
        if (is_lazy(node->left)) handle_lazy(node->left);
        if (is_lazy(node->right)) handle_lazy(node->right);

        node->sum = sum(node->left) + node->freq * node->key + sum(node->right);
        node->size = size(node->left) + node->freq + size(node->right);

        if (!ordered(node, node->left)) node = rotate_right(node);
        if (!ordered(node, node->right)) node = rotate_left(node);
    }

    return node;
}

Node *merge(Node *left, Node *right) {
    if (is_lazy(left)) handle_lazy(left);
    if (is_lazy(right)) handle_lazy(right);

    if (!left || !right) {
        return left ? left : right;
    } if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return update(left);
    } else {
        right->left = merge(left, right->left);
        return update(right);
    }
}

Node *insert(Node *node, int key) {
    if (is_lazy(node)) handle_lazy(node);
    if (!node) return new Node(key, rand());

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (node->key < key) {
        node->right = insert(node->right, key);
    } else {
        node->freq++;
    }

    return update(node);
}

Node *erase(Node *node, int key) {
    if (is_lazy(node)) handle_lazy(node);
    if (!node) return nullptr;

    if (node->key == key) {
        node->freq--;

        if (!node->freq) {
            Node *left = node->left, *right = node->right;
            delete node;
            return merge(left, right);
        }
    } else if (key < node->key) {
        node->left = erase(node->left, key);
    } else {
        node->right = erase(node->right, key);
    }

    return update(node);
}

long long lower_sum(Node *node, int key) {
    if (is_lazy(node)) handle_lazy(node);
    if (!node) return 0;

    if (node->key <= key) {
        return sum(node->left) + node->freq * node->key + lower_sum(node->right, key);
    } else {
        return lower_sum(node->left, key);
    }
}

long long lower_size(Node *node, int key) {
    if (is_lazy(node)) handle_lazy(node);
    if (!node) return 0;

    if (node->key <= key) {
        return size(node->left) + node->freq + lower_size(node->right, key);
    } else {
        return lower_size(node->left, key);
    }
}

long long upper_sum(Node *node, int key) {
    if (is_lazy(node)) handle_lazy(node);
    if (!node) return 0;

    if (key <= node->key) {
        return sum(node->right) + node->freq * node->key + upper_sum(node->left, key);
    } else {
        return upper_sum(node->right, key);
    }
}

long long upper_size(Node *node, int key) {
    if (is_lazy(node)) handle_lazy(node);
    if (!node) return 0;

    if (key <= node->key) {
        return size(node->right) + node->freq + upper_size(node->left, key);
    } else {
        return upper_size(node->right, key);
    }
}

long long get_min(Node *node) {
    if (node->left) return get_min(node->left);
    return node->key;
}

long long get_max(Node *node) {
    if (node->right) return get_max(node->right);
    return node->key;
}

inline long long get_left(int i) {
    return i * lower_size(left_root, i - 1) - lower_sum(left_root, i - 1) +
           upper_sum(left_root, i + 1) - i * upper_size(left_root, i + 1);
}

inline long long get_right(int i) {
    return i * lower_size(right_root, i - 1) - lower_sum(right_root, i - 1) +
           upper_sum(right_root, i + 1) - i * upper_size(right_root, i + 1);
}

inline long long get_value(int i) {
    return get_left(i) + get_right(i);
}

int N, K, values[200000];

int main() {
    scan(N);
    scan(K);

    long long ans = INF;

    for (int i = 0; i < N; i++) {
        scan(values[i]);

        right_root = insert(right_root, values[i]);
        lazily_update(right_root, -1);

        if (!(i & 1)) {
            int value = values[i >> 1] - ((i >> 1) + 1);

            right_root = erase(right_root, value);
            left_root = insert(left_root, value);
        }

        if (i < K - 1 || i & 1) continue;

        int lo = min(left_root ? get_min(left_root) : INF, right_root ? get_min(right_root) : INF),
                hi = max(left_root ? get_max(left_root) : -INF, right_root ? get_max(right_root) : -INF);

        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            long long lower = lower_size(left_root, mid) + lower_size(right_root, mid),
                    upper = size(left_root) + size(right_root) - lower;

            if (lower > upper) {
                hi = mid - 1;
            } else if (lower < upper) {
                lo = mid + 1;
            } else {
                lo = mid;
                break;
            }
        }

        ans = min(ans, get_value(lo));
    }

    printf("%lld\n", ans == INF ? -1 : ans);

    return 0;
}
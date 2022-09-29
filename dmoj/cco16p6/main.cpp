#include <iostream>

struct Node {
    long long value, sum, priority;
    Node *left, *right;
    int count, freq;

    // value and freq is within the node
    // count and sum is the whole subtree below the node

    Node(long long value, int freq, long long priority) : value{ value }, freq{ freq }, priority{ priority },
                                                          sum{ value * freq }, count{ freq },
                                                          left{ nullptr }, right{ nullptr } {}
};

Node *root = nullptr;
int N;
long long zero = 0, K;
int V[1000001];

int get_count(Node *node) {
    return node ? node->count : 0;
}

long long get_sum(Node *node) {
    return node ? node->sum : 0;
}

Node *update(Node *node) {
    if (node) {
        node->count = get_count(node->left) + node->freq + get_count(node->right);
        node->sum = get_sum(node->left) + node->freq * node->value + get_sum(node->right);
    }
    return node;
}

long long first_k_sum(Node *node, int k) {
    if (!k || !node) return 0;

    if (k <= get_count(node->left)) {
        return first_k_sum(node->left, k);
    } else if (get_count(node->left) + node->freq < k) {
        return get_sum(node->left) + node->value * node->freq +
                first_k_sum(node->right, k - get_count(node->left) - node->freq);
    } else {
        return get_sum(node->left) + node->value * (k - get_count(node->left));
    }
}

/*
 * Ignore the memory leak
 */

Node *remove_obsolete(Node *node, int k) {
    if (!k || !node) return nullptr;

    if (k <= get_count(node->left)) {
        return remove_obsolete(node->left, k);
    } else if (get_count(node->left) + node->freq < k) {
        node->right = remove_obsolete(node->right, k - get_count(node->left) - node->freq);
    } else {
        node->freq = k - get_count(node->left);
        node->right = nullptr;
    }

    return update(node);
}

void split(Node *node, long long value, Node *&left, Node *&right) {
    if (!node)
        left = right = nullptr;
    else if (value < node->value)
        split(node->left, value, left, node->left), right = update(node);
    else
        split(node->right, value, node->right, right), left = update(node);
}

Node *insert(Node *node, long long value, int freq, long long priority) {
    if (!node) return new Node(value, freq, priority);

    if (priority > node->priority) {
        Node *ret = new Node(value, freq, priority);
        split(node, value, ret->left, ret->right);
        return update(ret);
    } else if (value < node->value) {
        node->left = insert(node->left, value, freq, priority);
    } else {
        node->right = insert(node->right, value, freq, priority);
    }

    return update(node);
}

void solve() {
    for (int i = 1; i <= N; i++) --V[i];

    root = insert(root, K, 1, rand());
    printf("%lld\n", K);
    for (int i = 2; i <= N; i++) {
        long long required = first_k_sum(root, V[i]) - (V[i] * zero) + V[i];
        if (required > K) {
            root = insert(root, zero - 1, 1, rand());
        } else {
            --zero;
            root = remove_obsolete(root, V[i]);
            root = insert(root, zero, i - V[i] - 1, rand());
            root = insert(root, K - required + zero, 1, rand());
        }
        printf("%lld\n", required <= K ? K - required : -1);
    }
}

int main() {
    scanf("%d%lld", &N, &K);
    for (int i = 1; i <= N; i++) scanf("%d", V + i);
    solve();
    return 0;
}
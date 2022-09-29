#include <iostream>

struct Node {
    Node *left, *right;
    int sum, prefix, suffix;

    Node(int value) {
        left = nullptr;
        right = nullptr;
        sum = value;
        prefix = value;
        suffix = value;
    }

    Node(Node *left, Node *right) : left{ left }, right{ right } {
        if (left == nullptr) {
            sum = right->sum;
            prefix = right->prefix;
            suffix = right->suffix;
        } else if (right == nullptr) {
            sum = left->sum;
            prefix = left->prefix;
            suffix = left->suffix;
        } else {
            sum = left->sum + right->sum;
            prefix = std::max(left->prefix, left->sum + right->prefix);
            suffix = std::max(right->suffix, left->suffix + right->sum);
        }
    }
};

Node *versions[500001], *tmp[50];
int array[100001], V, N, Q, T;

Node *build(int lo, int hi) {
    if (lo == hi) {
        return new Node {array[lo]};
    } else {
        int mid = lo + (hi - lo) / 2;
        return new Node {build(lo, mid), build(mid + 1, hi)};
    }
}

Node *update(Node *node, int lo, int hi, int index, int value) {
    if (index < lo || hi < index) return node;

    if (lo == hi) {
        return new Node {value};
    } else {
        int mid = lo + (hi - lo) / 2;
        return new Node {update(node->left, lo, mid, index, value), update(node->right, mid + 1, hi, index, value)};
    }
}

Node *query(Node *node, int lo, int hi, int left, int right) {
    if (right < lo || hi < left) return nullptr;
    if (left <= lo && hi <= right) return node;

    int mid = lo + (hi - lo) / 2;
    Node *ret = new Node {query(node->left, lo, mid, left, right), query(node->right, mid + 1, hi, left, right)};
    tmp[T++] = ret;
    return ret;
}

int main() {
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) scanf("%d", array + i);

    versions[V = 0] = build(1, N);

    scanf("%d", &Q);

    while (Q--) {
        char t;
        scanf(" %c", &t);

        switch (t) {
            case 'U': {
                int poz, val;
                scanf("%d%d", &poz, &val);
                versions[V + 1] = update(versions[V], 1, N, poz, val);
                ++V;
            }
                break;
            case 'G': {
                int x;
                scanf("%d", &x);
                versions[V + 1] = versions[x];
                ++V;
            }
                break;
            case 'P': {
                int x, y;
                scanf("%d%d", &x, &y);
                T = 0;
                printf("%d\n", query(versions[V], 1, N, x, y)->prefix);
                for (int i = 0; i < T; i++) delete tmp[i];
            }
                break;
            case 'S': {
                int x, y;
                scanf("%d%d", &x, &y);
                T = 0;
                printf("%d\n", query(versions[V], 1, N, x, y)->suffix);
                for (int i = 0; i < T; i++) delete tmp[i];
            }
                break;
            default: break;
        }
    }
    return 0;
}
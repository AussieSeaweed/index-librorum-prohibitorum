#include <iostream>
#include <cmath>

int N, Q;
unsigned int arr[100001], tree[262144];

void build_tree(int node, int lo, int hi) {
    if (lo == hi) {
        tree[node] = arr[lo];
    } else {
        int mid = (lo + hi) / 2;
        build_tree(node * 2, lo, mid);
        build_tree(node * 2 + 1, mid + 1, hi);

        tree[node] = tree[node * 2] & tree[node * 2 + 1];
    }
}

unsigned int query_tree(int node, int lo, int hi, int left, int right) {
    if (right < lo || hi < left) return 0b11111111111111111111111111111111;
    if (left <= lo && hi <= right) return tree[node];

    int mid = (lo + hi) / 2;
    unsigned int l = query_tree(node * 2, lo, mid, left, right);
    unsigned int r = query_tree(node * 2 + 1, mid + 1, hi, left, right);

    return l & r;
}

void update_tree(int node, int lo, int hi, int index, unsigned int value) {
    if (index < lo || hi < index) return;

    if (lo == hi) {
        tree[node] = value;
    } else {
        int mid = (lo + hi) / 2;
        update_tree(node * 2, lo, mid, index, value);
        update_tree(node * 2 + 1, mid + 1, hi, index, value);

        tree[node] = tree[node * 2] & tree[node * 2 + 1];
    }
}

int main() {
    scanf("%d%d", &N, &Q);

    for (int i = 1; i <= N; i++)
        scanf("%u", arr + i);

    build_tree(1, 1, N);

    while (Q--) {
        char t;
        scanf(" %c", &t);

        if (t == 'U') {
            unsigned int x, val;
            scanf("%u%u", &x, &val);
            update_tree(1, 1, N, x, val);
        } else {
            unsigned int x, y, val;
            scanf("%u%u%u", &x, &y, &val);
            printf("%u\n", val & query_tree(1, 1, N, x, y));
        }
    }
    return 0;
}
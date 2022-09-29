#include <iostream>

int N, M, P, base_array[1048577], seg_tree[2097152];

void build_tree(int node, int lo, int hi) {
    if (lo == hi) {
        seg_tree[node] = lo;
    } else {
        int mid = lo + (hi - lo) / 2;
        build_tree(node * 2, lo, mid);
        build_tree(node * 2 + 1, mid + 1, hi);
        seg_tree[node] = base_array[seg_tree[node * 2]] < base_array[seg_tree[node * 2 + 1]] ? seg_tree[node * 2 + 1] : seg_tree[node * 2];
    }
}

void update(int node, int lo, int hi, int index, int value) {
    if (index < lo || hi < index) return;

    if (lo == hi) {
        base_array[index] = value;
    } else {
        int mid = lo + (hi - lo) / 2;
        update(node * 2, lo, mid, index, value);
        update(node * 2 + 1, mid + 1, hi, index, value);
        seg_tree[node] = base_array[seg_tree[node * 2]] < base_array[seg_tree[node * 2 + 1]] ? seg_tree[node * 2 + 1] : seg_tree[node * 2];
    }
}

int query(int node, int lo, int hi, int index, int depth) {
    if (lo == hi || seg_tree[node] == index) return N - depth;
    else {
        int mid = lo + (hi - lo) / 2;
        if (index <= mid) {
            return query(node * 2, lo, mid, index, depth + 1);
        } else {
            return query(node * 2 + 1, mid + 1, hi, index, depth + 1);
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    P = 1 << N;

    for (int i = 1; i <= P; i++) {
        scanf("%d", base_array + i);
    }

    build_tree(1, 1, P);

    while (M--) {
        char t;
        scanf(" %c", &t);

        switch (t) {
            case 'R': {
                int i, S;
                scanf("%d%d", &i, &S);
                update(1, 1, P, i, S);
            }
                break;
            case 'W': {
                printf("%d\n", seg_tree[1]);
            }
                break;
            case 'S': {
                int i;
                scanf("%d", &i);
                printf("%d\n", query(1, 1, P, i, 0));
            }
                break;
            default: break;
        }
    }

    return 0;
}
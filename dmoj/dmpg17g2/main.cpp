#include <iostream>
#include <cmath>
#include <vector>
#define INFINITY 999999999999
using namespace std;

struct Node {
    long long sum, prefixSum, suffixSum, maxSum;

    Node (long long val) :sum{val}, prefixSum{val}, suffixSum{val}, maxSum{val} {}

    Node (Node& left, Node& right) {
        sum = left.sum + right.sum;
        prefixSum = max(left.prefixSum, left.sum + right.prefixSum);
        suffixSum = max(right.suffixSum, right.sum + left.suffixSum);
        maxSum = max(prefixSum, suffixSum);
        maxSum = max(maxSum, left.maxSum);
        maxSum = max(maxSum, right.maxSum);
        maxSum = max(maxSum, left.suffixSum + right.prefixSum);
    }
};

vector<Node> segment_tree;

void init_seg_tree(int N) {
    int length = (int) (2 * pow(2.0, floor(log((double) N) / log(2.0)) + 1));
    segment_tree.resize(length, Node {0});
}

void build_segment_tree(vector<long long>& elems, int index, int lo, int hi) {
    if (lo == hi) {
        segment_tree[index] = Node {elems[lo]};
    } else {
        build_segment_tree(elems, index * 2, lo, (lo + hi) / 2);
        build_segment_tree(elems, index * 2 + 1, (lo + hi) / 2 + 1, hi);
        segment_tree[index] = Node {segment_tree[index * 2], segment_tree[index * 2 + 1]};
    }
}

Node query(int index, int lo, int hi, int left, int right) {
    if (right < lo || hi < left) return {-INFINITY};
    if (left <= lo && hi <= right) return segment_tree[index];

    Node qLeft = query(index * 2, lo, (lo + hi) / 2, left, right);
    Node qRight = query(index * 2 + 1, (lo + hi) / 2 + 1, hi, left, right);

    return Node {qLeft, qRight};
}

void update(int index, int lo, int hi, int i, long long val) {
    if (lo == hi) {
        segment_tree[index] = Node {val};
    } else {
        int mid = (lo + hi) / 2;
        if (i <= mid) {
            update(index * 2, lo, mid, i, val);
        } else {
            update(index * 2 + 1, mid + 1, hi, i, val);
        }
        segment_tree[index] = Node {segment_tree[index * 2], segment_tree[index * 2 + 1]};
    }
}

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);

    init_seg_tree(N);

    vector<long long> elems(N + 1);
    for (int i = 1; i <= N; i++)
        scanf("%lld", &elems[i]);

    build_segment_tree(elems, 1, 1, N);

    while (Q--) {
        char ch;
        scanf(" %c", &ch);

        if (ch == 'S') {
            int i;
            long long val;
            scanf("%d%lld", &i, &val);
            update(1, 1, N, i, val);
        } else {
            int left, right;
            scanf("%d%d", &left, &right);
            printf("%lld\n", query(1, 1, N, left, right).maxSum);
        }
    }

    return 0;
}
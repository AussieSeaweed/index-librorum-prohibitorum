#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void handle_lazy(vector<unsigned long long>& seg_tree, vector<unsigned long long>& lazy, int index, int lo, int hi) {
    seg_tree[index] += lazy[index] * (hi - lo + 1);

    if (lo != hi) {
        lazy[index * 2] += lazy[index];
        lazy[index * 2 + 1] += lazy[index];
    }

    lazy[index] = 0;
}

unsigned long long query(vector<unsigned long long>& seg_tree, vector<unsigned long long>& lazy, int index, int lo, int hi, int left, int right) {
    if (lazy[index]) handle_lazy(seg_tree, lazy, index, lo, hi);

    if (right < lo || hi < left) return 0;
    if (left <= lo && hi <= right) return seg_tree[index];

    unsigned long long qleft = query(seg_tree, lazy, index * 2, lo, (lo + hi) / 2, left, right);
    unsigned long long qright = query(seg_tree, lazy, index * 2 + 1, (lo + hi) / 2 + 1, hi, left, right);

    return qleft + qright;
}

void update(vector<unsigned long long>& seg_tree, vector<unsigned long long>& lazy, int index, int lo, int hi, int left, int right, unsigned long long val) {
    if (lazy[index]) handle_lazy(seg_tree, lazy, index, lo, hi);
    if (right < lo || hi < left) return;

    if (left <= lo && hi <= right) {
        lazy[index] += val;
        handle_lazy(seg_tree, lazy, index, lo, hi);
    } else {
        update(seg_tree, lazy, index * 2, lo, (lo + hi) / 2, left, right, val);
        update(seg_tree, lazy, index * 2 + 1, (lo + hi) / 2 + 1, hi, left, right, val);

        seg_tree[index] = seg_tree[index * 2] + seg_tree[index * 2 + 1];
    }
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int N, C;
        scanf("%d%d", &N, &C);
        auto length = (unsigned int) (2.0 * pow(2.0, floor(log((double) N) / log(2.0)) + 1));
        vector<unsigned long long> seg_tree(length, 0);
        vector<unsigned long long> lazy(length, 0);

        while (C--) {
            int t;
            scanf("%d", &t);
            if (t) {
                int p, q;
                scanf("%d%d", &p, &q);
                printf("%llu\n", query(seg_tree, lazy, 1, 1, N, p, q));
            } else {
                int p, q; unsigned long long v;
                scanf("%d%d%llu", &p, &q, &v);
                update(seg_tree, lazy, 1, 1, N, p, q, v);
            }
        }
    }
    return 0;
}
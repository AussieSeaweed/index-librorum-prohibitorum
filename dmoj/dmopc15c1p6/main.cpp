#include <iostream>
#include <cmath>
using namespace std;

const auto size = (unsigned int) pow(2., ceil(log(200001.) / log(2.)) + 1);
unsigned long long elems[200001];
unsigned long long sum[size];
unsigned long long lazy[size];
int N, M, Q;

void build_tree(int index, int lo, int hi) {
    if (lo == hi) {
        sum[index] = elems[lo] % M;
    } else {
        int mid = (lo + hi) / 2;
        build_tree(index * 2, lo, mid);
        build_tree(index * 2 + 1, mid + 1, hi);

        sum[index] = (sum[index * 2] + sum[index * 2 + 1]) % M;
    }
}

void handle_lazy(int index, int lo, int hi) {
    sum[index] = (sum[index] + (hi - lo + 1) * lazy[index]) % M;

    if (lo != hi) {
        lazy[index * 2] += lazy[index];
        lazy[index * 2 + 1] += lazy[index];
    }

    lazy[index] = 0;
}

void add(int index, int lo, int hi, int left, int right, unsigned long long val) {
    if (lazy[index]) handle_lazy(index, lo, hi);
    if (right < lo || hi < left) return;

    if (left <= lo && hi <= right) {
        lazy[index] = val;
        handle_lazy(index, lo, hi);
    } else {
        int mid = (lo + hi) / 2;
        add(index * 2, lo, mid, left, right, val);
        add(index * 2 + 1, mid + 1, hi, left, right, val);

        sum[index] = (sum[index * 2] + sum[index * 2 + 1]) % M;
    }
}

unsigned long long query(int index, int lo, int hi, int left, int right) {
   if (lazy[index]) handle_lazy(index, lo, hi);
   if (right < lo || hi < left) return 0;

   if (left <= lo && hi <= right) {
       return sum[index];
   } else {
       int mid = (lo + hi) / 2;
       return (query(index * 2, lo, mid, left, right) + query(index * 2 + 1, mid + 1, hi, left, right)) % M;
   }
}

int main() {
    scanf("%d%d%d", &M, &N, &Q);

    for (int i = 1; i <= N; i++)
        scanf("%llu", elems + i);

    build_tree(1, 1, N);

    while (Q--) {
        int t, l, r; unsigned long long x;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1) {
            scanf("%llu", &x);
            add(1, 1, N, l, r, x);
        } else {
            printf("%llu\n", query(1, 1, N, l, r));
        }
    }

    return 0;
}
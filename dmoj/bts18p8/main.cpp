#include <iostream>
#include <bitset>

int N, Q; long long K;
long long a_lst[] {2, 3, 5, 7, 11, 13, 17};
bool prime[5001];

inline unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long modulus) {
    unsigned long long x = 0, y = a % modulus;
    while (b) {
        if (b & 1) x = (x + y) % modulus;
        y = (y << 1) % modulus;
        b >>= 1;
    }
    return x % modulus;
}

inline unsigned long long powmod(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    if (modulus == 1) return 0;
    unsigned long long result = 1;
    base %= modulus;
    while (exponent) {
        if (exponent & 1)
            result = mulmod(result, base, modulus);
        exponent >>= 1;
        base = mulmod(base, base, modulus);
    }
    return result;
}

inline bool miller_rabin(unsigned long long num) {
    if (num == 2) return true;
    if (num < 2 || (num % 2 == 0)) return false;
    unsigned long long d = num - 1;
    while (d % 2 == 0)
        d /= 2;
    for (long long a : a_lst) {
        unsigned long long tmp = d, x = powmod(a % (num - 1) + 1, d, num);
        while (tmp != num - 1 && x != 1 && x != num - 1) {
            x = mulmod(x, x, num);
            tmp *= 2;
        }
        if (x != num - 1 && tmp % 2 == 0) return false;
    }
    return true;
}

void get_primes() {
    for (int k = 0; k <= 5000; k++)
        prime[k] = miller_rabin(K + k);
}

int base_array[100001];
int highpt[262144], lowpt[262144];
std::bitset<5001> seg_tree[262144];
int lazy[262144];

void handle_lazy(int node, int lo, int hi) {
    if (lazy[node] > 0)
        seg_tree[node] <<= lazy[node];
    else
        seg_tree[node] >>= -lazy[node];

    highpt[node] += lazy[node];
    lowpt[node] += lazy[node];

    if (lo != hi) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }

    lazy[node] = 0;
}

void build_tree(int node, int lo, int hi) {
    if (lo == hi) {
        seg_tree[node][base_array[lo]] = true;
        highpt[node] = base_array[lo];
        lowpt[node] = base_array[lo];
    } else {
        int mid = lo + (hi - lo) / 2;
        build_tree(node * 2, lo, mid);
        build_tree(node * 2 + 1, mid + 1, hi);

        seg_tree[node] = seg_tree[node * 2] | seg_tree[node * 2 + 1];
        highpt[node] = std::max(highpt[node * 2], highpt[node * 2 + 1]);
        lowpt[node] = std::min(lowpt[node * 2], lowpt[node * 2 + 1]);
    }
}

int query(int node, int lo, int hi, int left, int right) {
    if (lazy[node]) handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return -1;
    if (left <= lo && hi <= right) {
        for (int i = highpt[node]; i >= lowpt[node]; i--)
            if (seg_tree[node][i] && prime[i]) return i;
        return -1;
    }

    int mid = lo + (hi - lo) / 2;
    int query_left = query(node * 2, lo, mid, left, right);
    int query_right = query(node * 2 + 1, mid + 1, hi, left, right);

    return std::max(query_left, query_right);
}

void update_range(int node, int lo, int hi, int left, int right, int value) {
    if (lazy[node]) handle_lazy(node, lo, hi);
    if (right < lo || hi < left) return;

    if (left <= lo && hi <= right) {
        lazy[node] = value;
        handle_lazy(node, lo, hi);
    } else {
        int mid = lo + (hi - lo) / 2;
        update_range(node * 2, lo, mid, left, right, value);
        update_range(node * 2 + 1, mid + 1, hi, left, right, value);

        seg_tree[node] = seg_tree[node * 2] | seg_tree[node * 2 + 1];
        highpt[node] = std::max(highpt[node * 2], highpt[node * 2 + 1]);
        lowpt[node] = std::min(lowpt[node * 2], lowpt[node * 2 + 1]);
    }
}

int main() {
    scanf("%d%d%lld", &N, &Q, &K);
    get_primes();

    for (int i = 1; i <= N; i++) {
        long long value;
        scanf("%lld", &value);
        base_array[i] = (int) (value - K);
    }

    build_tree(1, 1, N);

    while (Q--) {
        int t;
        scanf("%d", &t);

        switch (t) {
            case 1: {
                int l, r;
                scanf("%d%d", &l, &r);
                int q = query(1, 1, N, l, r);
                printf("%lld\n", q == -1 ? q : q + K);
            }
                break;
            case 2: {
                int l, r, v;
                scanf("%d%d%d", &l, &r, &v);
                update_range(1, 1, N, l, r, v);
            }
                break;
            default: break;
        }
    }

    return 0;
}
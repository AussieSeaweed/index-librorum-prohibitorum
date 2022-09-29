#include <iostream>
#include <cmath>
using namespace std;

const int N = 2000001;
const unsigned int len = (unsigned int) (2.0 * pow(2.0, floor(log((double) (N + 1)) / log(2.0)) + 1));
long long size[len];
long long cost[len];
long long add_lazy[len];
bool buy_lazy[len];

long long range_sum(long long a, long long b) {
    return (b - a + 1) * (a + b) / 2;
}

inline void handle_lazy(int index, int lo, int hi) {
    if (buy_lazy[index]) {
        size[index] = 0;
        cost[index] = 0;

        if (lo != hi) {
            add_lazy[index * 2] = 0;
            buy_lazy[index * 2] = true;
            add_lazy[index * 2 + 1] = 0;
            buy_lazy[index * 2 + 1] = true;
        }

        buy_lazy[index] = false;
    }

    if (add_lazy[index]) {
        size[index] += add_lazy[index] * (hi - lo + 1);
        cost[index] += add_lazy[index] * range_sum(lo, hi);

        if (lo != hi) {
            add_lazy[index * 2] += add_lazy[index];
            add_lazy[index * 2 + 1] += add_lazy[index];
        }

        add_lazy[index] = 0;
    }
}

inline void update(int index) {
    size[index] = size[index * 2] + size[index * 2 + 1];
    cost[index] = cost[index * 2] + cost[index * 2 + 1];
}

void add(int index, int lo, int hi, int i, long long val) {
    handle_lazy(index, lo, hi);
    if (i < lo || hi < i) return;

    if (lo == hi) {
        size[index] += val;
        cost[index] = size[index] * lo;
    } else {
        int mid = (lo + hi) / 2;
        add(index * 2, lo, mid, i, val);
        add(index * 2 + 1, mid + 1, hi, i, val);
        update(index);
    }
}

void add_range(int index, int lo, int hi, int left, int right) {
    handle_lazy(index, lo, hi);
    if (right < lo || hi < left) return;

    if (left <= lo && hi <= right) {
        add_lazy[index]++;
        handle_lazy(index, lo, hi);
    } else {
        int mid = (lo + hi) / 2;
        add_range(index * 2, lo, mid, left, right);
        add_range(index * 2 + 1, mid + 1, hi, left, right);
        update(index);
    }
}

long long get_size(int index, int lo, int hi, int left, int right) {
    handle_lazy(index, lo, hi);
    if (right < lo || hi < left) return 0;

    if (left <= lo && hi <= right) return size[index];
    else {
        int mid = (lo + hi) / 2;
        return get_size(index * 2, lo, mid, left, right) + get_size(index * 2 + 1, mid + 1, hi, left, right);
    }
}


long long get_cost(int index, int lo, int hi, int left, int right) {
    handle_lazy(index, lo, hi);
    if (right < lo || hi < left) return 0;

    if (left <= lo && hi <= right) return cost[index];
    else {
        int mid = (lo + hi) / 2;
        return get_cost(index * 2, lo, mid, left, right) + get_cost(index * 2 + 1, mid + 1, hi, left, right);
    }
}

long long buy_amt(int index, int lo, int hi, long long money) {
    handle_lazy(index, lo, hi);
    if (!money) return 0;

    if (lo == hi) {
        long long num = min(size[index], money / lo);
        size[index] -= num;
        cost[index] = size[index] * lo;
        return num;
    } else if (cost[index] <= money) {
        buy_lazy[index] = true;
        add_lazy[index] = 0;
        long long num = size[index];
        handle_lazy(index, lo, hi);
        return num;
    } else {
        int mid = (lo + hi) / 2;
        long long left_cost = get_cost(index * 2, lo, mid, lo, mid);
        long long num = 0;
        num += buy_amt(index * 2, lo, mid, min(left_cost, money));
        num += buy_amt(index * 2 + 1, mid + 1, hi, max(0ll, money - left_cost));
        update(index);
        return num;
    }
}

long long buy_low(int index, int lo, int hi, long long num) {
    handle_lazy(index, lo, hi);
    if (!num) return 0;

    if (lo == hi) {
        num = min(num, size[index]);
        size[index] -= num;
        cost[index] = size[index] * lo;
        return num * lo;
    } else if (size[index] <= num) {
        buy_lazy[index] = true;
        add_lazy[index] = 0;
        long long c = cost[index];
        handle_lazy(index, lo, hi);
        return c;
    } else {
        int mid = (lo + hi) / 2;
        long long left_size = get_size(index * 2, lo, mid, lo, mid);
        long long c = 0;
        c += buy_low(index * 2, lo, mid, min(num, left_size));
        c += buy_low(index * 2 + 1, mid + 1, hi, max(0ll, num - left_size));
        update(index);
        return c;
    }
}

long long buy_high(int index, int lo, int hi, long long num) {
    handle_lazy(index, lo, hi);
    if (!num) return 0;

    if (lo == hi) {
        num = min(num, size[index]);
        size[index] -= num;
        cost[index] = size[index] * lo;
        return num * lo;
    } else if (size[index] <= num) {
        buy_lazy[index] = true;
        add_lazy[index] = 0;
        long long c = cost[index];
        handle_lazy(index, lo, hi);
        return c;
    } else {
        int mid = (lo + hi) / 2;
        long long right_size = get_size(index * 2 + 1, mid + 1, hi, mid + 1, hi);
        long long c = 0;
        c += buy_high(index * 2, lo, mid, max(0ll, num - right_size));
        c += buy_high(index * 2 + 1, mid + 1, hi, min(num, right_size));
        update(index);
        return c;
    }
}

int get_nth_cost(int index, int lo, int hi, long long n) {
    handle_lazy(index, lo, hi);

    if (n > size[index]) return -1;
    else if (lo == hi) return lo;
    else {
        int mid = (lo + hi) / 2;
        long long left_size = get_size(index * 2, lo, mid, lo, mid);

        if (n <= left_size) {
            return get_nth_cost(index * 2, lo, mid, n);
        } else {
            return get_nth_cost(index * 2 + 1, mid + 1, hi, n - left_size);
        }
    }
}

int main() {
    long long _;
    cin >> _;

    while (_--) {
        string str;
        cin >> str;

        if (str == "ADD") {
            int K, P;
            scanf("%d%d", &K, &P);
            add(1, 0, N, P, K);
        } else if (str == "ADDRANGE") {
            int A, B;
            scanf("%d%d", &A, &B);
            add_range(1, 0, N, A, B);
        } else if (str == "BUYAMT") {
            long long Q;
            scanf("%lld", &Q);
            cout << buy_amt(1, 0, N, Q) << "\n";
        } else if (str == "BUYLOW") {
            long long L;
            scanf("%lld", &L);
            cout << buy_low(1, 0, N, L) << "\n";
        } else if (str == "BUYHIGH") {
            long long L;
            scanf("%lld", &L);
            cout << buy_high(1, 0, N, L) << "\n";
        } else if (str == "COST") {
            long long L;
            scanf("%lld", &L);
            cout << get_nth_cost(1, 0, N, L) << "\n";
        } else if (str == "NUMCONES") {
            cout << get_size(1, 0, N, 1, N) << "\n";
        } else {
            cout << get_cost(1, 0, N, 1, N) << "\n";
        }
    }

    return 0;
}
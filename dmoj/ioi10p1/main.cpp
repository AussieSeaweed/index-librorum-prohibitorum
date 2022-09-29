#include <iostream>

int Theory(int M, int L, int W);

int query(int m, int l, int w) {
    return Theory(m + 1, l + 1, w + 1);
}

void solve() {
    int m = 0, l = 0, w = 0, r;

    while (r = query(m, l, w)) {
        switch (r) {
            case 1:
                ++m;
                break;
            case 2:
                ++l;
                break;
            case 3:
                ++w;
                break;
            default:
                break;
        }
    }
}

void Solve() {
    solve();
}
#include <iostream>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

inline long long int ace(int n) {
    static const int lookup[3]{10, 12, 14};
    long long int base = 1, i = 0;

    while (n >= 0) {
        std::lldiv_t div = std::lldiv(n, 3);
        i += lookup[div.rem] * base;
        n = div.quot - 1;
        base <<= 4;
    }

    return i;
}

inline int lowerBound(long long int x) {
    int lo = 0, hi = 1;

    while (ace(hi) < x) hi <<= 1;

    while (lo < hi) {
        int mid = (lo + hi) >> 1;

        if (ace(mid) < x)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
}

inline int upperBound(long long int x) {
    int lo = 0, hi = 1;

    while (ace(hi) <= x) hi <<= 1;

    while (lo < hi) {
        int mid = (lo + hi) >> 1;

        if (ace(mid) <= x)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
}

long long int a, b;

int main() {
    pscan(a);
    pscan(b);

    printf("%d", upperBound(b) - lowerBound(a));

    return 0;
}
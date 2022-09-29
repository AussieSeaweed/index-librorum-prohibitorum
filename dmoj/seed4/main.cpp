#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Vector {
    long long x, y, z;

    Vector() : x{}, y{}, z{} {}
    Vector(long long x, long long y, long long z) : x{ x }, y{ y }, z{ z } {}

    void simplify() {
        long long gcd = abs(__gcd(x, __gcd(y, z)));

        x /= gcd;
        y /= gcd;
        z /= gcd;
    }

    bool operator<(const Vector &that) const {
        return x == that.x ? (y == that.y ? z < that.z : y < that.y) : x < that.x;
    }
};

set<Vector> vectors;
Vector source;
int N;

int main() {
    scanf("%lld%lld%lld", &source.x, &source.y, &source.z);
    scan(N);

    while (N--) {
        long long x, y, z;
        scanf("%lld%lld%lld", &x, &y, &z);

        Vector vec(x - source.x, y - source.y, z - source.z);
        vec.simplify();

        vectors.insert(vec);
    }

    printf("%d\n", vectors.size());

    return 0;
}
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, S;

struct Bebilith {
    int b, d, c, i;

    Bebilith() {}
    Bebilith(int b, int d, int c, int i) : b{ b }, d{ d }, c{ c }, i{ i } {}

    bool operator<(const Bebilith &other) const {
        if (b == other.b) {
            if (b >= S) {
                return c == other.c ? i < other.i : c > other.c;
            } else {
                return d == other.d ? i < other.i : d > other.d;
            }
        } else {
            return b > other.b;
        }
    }
} bebiliths[50000];

int main() {
    scan(S);
    scan(N);

    for (int i = 0; i < N; i++) {
        scan(bebiliths[i].b);
        scan(bebiliths[i].d);
        scan(bebiliths[i].c);
        bebiliths[i].i = i;
    }

    sort(bebiliths, bebiliths + N);

    int Q;
    scan(Q);

    while (Q--) {
        int i;
        scan(i);
        --i;
        printf("%d\n", bebiliths[i].i + 1);
    }

    return 0;
}
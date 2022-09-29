#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int P;
int minx = inf, maxx = -inf, miny = inf, maxy = -inf;

int main() {
    scan(P);

    while (P--) {
        int x, y;
        scanf("%d%d", &x, &y);
        minx = min(minx, x);
        maxx = max(maxx, x);
        miny = min(miny, y);
        maxy = max(maxy, y);
    }

    printf("%d\n", 2 * (maxy - miny) + 2 * (maxx - minx));

    return 0;
}
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int main() {
    int __ = 10;

    while (__--) {
        int x, y;
        scanf("%d%d", &x, &y);

        long long minx = 0, maxx = 1, miny = -1, maxy = 0;
        int i = 0;

        while (!(minx <= x && x <= maxx && miny <= y && y <= maxy)) {
            int step = i % 4;

            if (step == 0) {
                minx -= maxy - miny;
            } else if (step == 1) {
                maxy += maxx - minx;
            } else if (step == 2) {
                maxx += maxy - miny;
            } else {
                miny -= maxx - minx;
            }

            i++;
        }

        printf("%d\n", i + 1);
    }
    return 0;
}
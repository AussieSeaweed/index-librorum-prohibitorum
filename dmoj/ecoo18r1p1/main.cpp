#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;



int main() {
    int __ = 10;

    while (__--) {
        int T, N;
        scan(T);
        scan(N);

        int days_remaining = 0;

        for (int i = 0; i < N; i++) {
            char ch;
            scanf(" %c", &ch);
            if (ch == 'B') {
                days_remaining += T;
            }

            days_remaining = max(days_remaining - 1, 0);
        }

        printf("%d\n", days_remaining);
    }

    return 0;
}
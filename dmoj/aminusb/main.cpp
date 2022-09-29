#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N;

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", a - b);
    }
    return 0;
}
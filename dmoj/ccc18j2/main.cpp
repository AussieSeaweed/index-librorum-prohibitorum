#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N;
char a[105], b[105];

int main() {
    scan(N);
    scanf("%s%s", a, b);
    int ans = 0;

    for (int i = 0; i < N; i++)
        if (a[i] == 'C' && b[i] == 'C')
            ans++;

    printf("%d\n", ans);
    return 0;
}
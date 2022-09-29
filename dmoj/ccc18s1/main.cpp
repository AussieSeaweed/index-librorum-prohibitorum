#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

long long N, pos[100];

int main() {
    scan(N);

    for (int i = 0; i < N; i++)
        scanf("%lld", &pos[i]);

    sort(pos, pos + N);

    double prev_loc = (pos[0] + pos[1]) / 2., ans = INF;

    for (int i = 1; i < N - 1; i++) {
        ans = min(ans, (pos[i] + pos[i + 1]) / 2. - prev_loc);
        prev_loc = (pos[i] + pos[i + 1]) / 2.;
    }

    printf("%.1lf\n", ans);

    return 0;
}
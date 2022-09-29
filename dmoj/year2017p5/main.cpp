#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K, dist[100010], cnt = 0;
char buffer[100010];
bool bits[100010];

int solve() {
    cnt = 0;

    for (int i = 1; i <= N; i++) {
        if (bits[i]) {
            cnt++;
            dist[cnt] = dist[cnt - 1] + i - cnt;
        }
    }

    int ans = 0;

    for (int l = 1, r = 1; r <= cnt; r++) {
        int mid = l + (r - l) / 2;
        while ((mid - l + 1) * (dist[mid] - dist[mid - 1]) - (dist[mid] - dist[l - 1]) +
               (dist[r] - dist[mid - 1]) - (r - mid + 1) * (dist[mid] - dist[mid - 1]) > K && l <= r)
            l++;
        ans = max(ans, r - l + 1);
    }

    return ans;
}

int main() {
    scan(N);
    scan(K);
    scanf("%s", buffer);

    for (int i = 0; i < N; i++)
        bits[i + 1] = buffer[i] - '0';

    printf("%d ", solve());

    for (int i = 1; i <= N; i++)
        bits[i] = !bits[i];

    printf("%d\n", solve());

    return 0;
}
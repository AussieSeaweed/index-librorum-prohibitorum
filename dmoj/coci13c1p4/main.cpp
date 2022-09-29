#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K;
pair<int, int> VM[300000];
multiset<int> cap;

int main() {
    scan(N);
    scan(K);

    for (int i = 0; i < N; i++)
        scanf("%d%d", &VM[i].second, &VM[i].first);

    for (int i = 0; i < K; i++) {
        int c;
        scanf("%d", &c);
        cap.insert(c);
    }

    sort(VM, VM + N, greater<pair<int, int>>());

    long long ans = 0;

    int i = 0;
    while (i < N && !cap.empty()) {
        auto it = cap.lower_bound(VM[i].second);

        if (it != cap.end()) {
            ans += VM[i].first;
            cap.erase(it);
        }

        i++;
    }

    printf("%lld\n", ans);

    return 0;
}
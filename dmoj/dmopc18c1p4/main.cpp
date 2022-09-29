#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

long long N, M, K, X, ans[200001];
pair<long long, int> values[200001];

inline bool works(int index) {
    long long before = values[index + X - 2].first - values[index - 1].first;
    long long after = values[index + X - 1].first - values[index - 1].first;
    return before < K && K <= after;
}

int main() {
    scan(N);
    scan(M);
    scan(K);
    scan(X);

    for (int i = 1; i <= N; i++) {
        scan(values[i].first);
        values[i].second = i;
    }

    sort(values + 1, values + N + 1);

    for (int i = 1; i <= N; i++) {
        values[i].first += values[i - 1].first;
    }

    bool found = false;

    for (long long i = 1; i <= N - X + 1; i++) {
        if (works(i)) {
            long long cur = 1;
            for (long long j = i; j < i + X; j++) {
                ans[values[j].second] = cur++;
            }
            for (long long j = 1; j < i; j++) {
                ans[values[j].second] = cur++;
            }
            for (long long j = i + X; j <= N; j++) {
                ans[values[j].second] = cur++;
            }
            found = true;
            break;
        }
    }

    if (found)
        for (int i = 1; i <= N; i++)
            printf("%lld ", ans[i]);
    else
        printf("-1");

    return 0;
}
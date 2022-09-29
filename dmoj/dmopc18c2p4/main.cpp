#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

long long N, M;

int main() {
    scan(N);
    scan(M);

    int ans = inf;
    long long cur = 0;
    deque<long long> elems;

    while (N--) {
        long long i;
        scan(i);
        elems.push_back(i);
        cur += i;
        while (cur >= M && !elems.empty()) {
            ans = min(ans, (int) elems.size());
            cur -= elems.front();
            elems.pop_front();
        }
    }

    printf("%d\n", ans == inf ? -1 : ans);

    return 0;
}
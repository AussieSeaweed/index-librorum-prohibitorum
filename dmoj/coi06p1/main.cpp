#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N;
vector<int> ppl;

int main() {
    scan(N);

    long long cnt = 0;

    while (N--) {
        int cur;
        scan(cur);

        if (!ppl.empty()) {
            int lo = 0, hi = ppl.size() - 1;

            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (ppl[mid] <= cur) {
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }

            hi = max(hi, 0);

            cnt += ppl.size() - hi;
        }

        while (!ppl.empty() && ppl.back() < cur) ppl.pop_back();
        ppl.push_back(cur);
    }

    printf("%lld\n", cnt);

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int N, K;
vector<int> a, b;
vector<int> as, bs;
unordered_map<int, int> cache;

void add(vector<int>& nums, vector<int>& sums) {
    sums.reserve(1 << nums.size());
    sums.push_back(0);

    for (int i = 0; i < nums.size(); i++) {
        int lim = sums.size();
        for (int j = 0; j < lim; j++) {
            sums.push_back(sums[j] + nums[i]);
        }
    }
}

int main() {
    scanf("%d%d", &N, &K);

    for (int i = 0; i < N / 2; i++) {
        int n;
        scanf("%d", &n);
        a.push_back(n);
    }

    for (int i = N / 2; i < N; i++) {
        int n;
        scanf("%d", &n);
        b.push_back(n);
    }

    add(a, as);
    add(b, bs);

    sort(bs.begin(), bs.end());

    long long ans = 0;

    for (int i = 0; i < as.size(); i++) {
        int lo = 0, hi = bs.size(); int target = K - as[i];
        if (cache.count(as[i])) { ans += cache[as[i]]; continue; }
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (bs[mid] <= target) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        ans += hi;
        cache[as[i]] = hi;
    }

    printf("%lld", ans);

    return 0;
}
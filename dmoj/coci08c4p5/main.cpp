#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int A, B, L;
vector<int> prime_factors[4001];
long long insecure = 0, secure = 0, super_secure = 0;

void get_prime_factors() {
    bool marked[4001];
    fill(marked, marked + 4001, true);
    marked[0] = false;
    marked[1] = false;

    for (int i = 2; i <= 4000; i++)
        if (marked[i])
            for (int j = i; j <= 4000; j += i) {
                marked[j] = false;
                prime_factors[j].push_back(i);
            }
}

long long get_visible(vector<int> factors) {
    long long ret = 0, prev[1 << factors.size()];
    prev[0] = -1;

    for (int i = 1; i < (1 << factors.size()); i++) {
        prev[i] = -prev[i - (i & -i)] * factors[__builtin_ctz(i)];
        ret += L / prev[i];
    }

    return L - ret;
}

long long get_visible(int i) {
    if (i == 0) return 1;
    if (i == 1) return L;
    return get_visible(prime_factors[i]);
}

long long get_visible(int a, int b) {
    if (a == 0 || b == 0) return 1;
    if (a == 1) return get_visible(b);
    if (b == 1) return get_visible(a);

    set<int> total {prime_factors[a].begin(), prime_factors[a].end()};
    total.insert(prime_factors[b].begin(), prime_factors[b].end());
    return get_visible(vector<int> {total.begin(), total.end()});
}

int main() {
    get_prime_factors();

    scan(A);
    scan(B);
    scan(L);

    for (int i = -A; i <= B; i++) {
        long long a_cnt = get_visible(i + A);
        long long b_cnt = get_visible(B - i);
        long long both_cnt = get_visible(i + A, B - i);

        insecure += L - a_cnt - b_cnt + both_cnt;
        secure += a_cnt + b_cnt - (both_cnt << 1);
        super_secure += both_cnt;
    }

    printf("%lld\n%lld\n%lld\n", insecure, secure, super_secure);

    return 0;
}
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, X, Y, Z;

string input[20];
string output[20];
string solns[20];

string solve(string &in) {
    vector<int> nums;

    for (int i = 0; i < in.size(); i++) {
        int cur = in[i] - '0';

        if (cur & 1) {
            cur = max(cur - Y, 0);
        } else if (!cur) {
            cur = Z;
        } else {
            cur += X;
        }

        nums.push_back(cur);
    }

    ostringstream oss;

    for (int i : nums)
        oss << i;

    return oss.str();
}

void solve() {
    for (int i = 0; i < N; i++) {
        output[i] = solve(input[i]);
    }
}

int main() {
    int __ = 10;

    while (__--) {
        scan(N);
        scan(X);
        scan(Y);
        scan(Z);

        char ch;

        for (int i = 0; i < N; i++)
            cin >> input[i];

        scanf(" %c", &ch);

        for (int i = 0; i < N; i++)
            cin >> solns[i];

        scanf(" %c", &ch);

        solve();

        vector<int> fails;

        for (int i = 0; i < N; i++)
            if (output[i] != solns[i])
                fails.push_back(i + 1);

        if (fails.empty()) {
            printf("MATCH\n");
        } else {
            printf("FAIL: %d", fails[0]);
            for (int i = 1; i < fails.size(); i++)
                printf(",%d", fails[i]);
            printf("\n");
        }
    }

    return 0;
}
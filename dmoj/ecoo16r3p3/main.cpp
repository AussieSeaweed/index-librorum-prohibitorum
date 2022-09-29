#include <iostream>
#include <unordered_set>
#define inf 99999999
using namespace std;

unordered_set<string> words;
string pattern;
int dp[2001];
int N;

int solve() {
    dp[0] = 0;

    for (int n = 1; n <= pattern.size(); n++) {
        dp[n] = inf;
        for (int i = 0; i < n; i++) {
            if (words.count(pattern.substr(i, n - i)))
                dp[n] = min(dp[n], (i == 0 ? 0 : 1) + dp[i]);
        }
    }

    return dp[pattern.size()];
}

int main() {
    scanf("%d", &N);
    while (N--) {
        string str;
        cin >> str;
        words.insert(str);
    }
    for (int _ = 0; _ < 10; _++) {
        cin >> pattern;
        printf("%d\n", solve());
    }
    return 0;
}
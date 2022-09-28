#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<long long> dp(5001);
string str;

int main() {
    while (cin >> str) {
        if (str == "0") break;
        fill(dp.begin(), dp.begin() + str.size() + 1, 0);

        dp[1] = 1;
        dp[0] = 1;

        for (int i = 2; i <= str.size(); i++) {
            if (str[i - 1] != '0') dp[i] = dp[i - 1];
            if (str[i - 2] != '0' && (str[i - 2] - '0') * 10 + str[i - 1] - '0' <= 26) dp[i] += dp[i - 2];
        }

        printf("%lld\n", dp[str.size()]);
    }
    return 0;
}
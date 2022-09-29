#include <iostream>
#include <cstring>

using namespace std;

string str;
string nums[] {"ook", "ookook", "oog", "ooga", "ug", "mook", "mookmook", "oogam", "oogum", "ugug"};
int dp[500];

int solve(int i) {
    if (dp[i] != -1) return dp[i];
    if (i == str.size()) return dp[i] = 1;
    dp[i] = 0;

    for (string n : nums) {
        if (str.size() - i >= n.size() && str.substr(i, n.size()) == n) {
            dp[i] += solve(i + n.size());
        }
    }

    return dp[i];
}

int main() {
    for (int _ = 0; _ < 10; _++) {
        cin >> str;
        memset(dp, -1, sizeof dp);
        printf("%d\n", solve(0));
    }
    return 0;
}
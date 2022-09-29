#include <iostream>
#include <cstring>
#define inf 999999999
using namespace std;

int N, dp[26][4][26], del[26][4][26]; bool visited[26][4][26];
string pattern {"ohmy"};
string str;

pair<int, int> solve(int i, int o, int last) {
    if (visited[i][o][last]) return {dp[i][o][last], del[i][o][last]};
    visited[i][o][last] = true;
    if (i == N) return {dp[i][o][last] = 0, del[i][o][last] = last};
    dp[i][o][last] = 0;
    del[i][o][last] = inf;

    if (str[i] == pattern[o]) {
        pair<int, int> soln1 = solve(i + 1, o, last + 1);
        pair<int, int> soln2 = solve(i + 1, (o + 1) % 4, o == 3 ? 0 : last + 1);
        if (o == 3) soln2.first++;

        if (soln1.first > dp[i][o][last]) {
            dp[i][o][last] = soln1.first;
            del[i][o][last] = soln1.second;
        } else if (soln1.first == dp[i][o][last]) {
            del[i][o][last] = min(del[i][o][last], soln1.second);
        }

        if (soln2.first > dp[i][o][last]) {
            dp[i][o][last] = soln2.first;
            del[i][o][last] = soln2.second;
        } else if (soln2.first == dp[i][o][last]) {
            del[i][o][last] = min(del[i][o][last], soln2.second);
        }
    } else { // delete
        pair<int, int> soln = solve(i + 1, o, last);
        soln.second++;

        if (soln.first > dp[i][o][last]) {
            dp[i][o][last] = soln.first;
            del[i][o][last] = soln.second;
        } else if (soln.first == dp[i][o][last]) {
            del[i][o][last] = min(del[i][o][last], soln.second);
        }
    }

    return {dp[i][o][last], del[i][o][last]};
}

int main() {
    scanf("%d", &N);
    cin >> str;
    pair<int, int> soln = solve(0, 0, 0);
    printf("o");
    while (soln.first--)
        printf("h");
    printf("m");
    while (soln.second--)
        printf("y");
    printf("\n");
    return 0;
}
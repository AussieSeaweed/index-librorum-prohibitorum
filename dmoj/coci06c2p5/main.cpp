#include <iostream>
#include <vector>
using namespace std;

int dp[400][400];
bool mat[400][400];
char buffer[400];
int R, C;

int continuous(bool arr[]) {
    int cur = 0, longest = 0;

    for (int i = 0; i < R; i++) {
        if (arr[i]) {
            cur++;
        } else {
            cur = 0;
        }

        longest = max(longest, cur);
    }

    return longest;
}

int solve() {
    bool arr[R];
    int longest = 0;

    for (int i = 0; i < C; i++) {
        fill(arr, arr + R, true);
        for (int j = i; j < C; j++) {
            for (int k = 0; k < R; k++) {
                arr[k] &= mat[k][j];
            }
            int len = continuous(arr);
            if (len) longest = max(longest, 2 * ((j - i + 1) + len));
        }
    }

    return longest;
}

int main() {
    scanf("%d%d", &R, &C);

    for (int r = 0; r < R; r++) {
        scanf("%s", buffer);
        for (int c = 0; c < C; c++)
            mat[r][c] = buffer[c] == '.';
    }

    printf("%d", solve() - 1);

    return 0;
}
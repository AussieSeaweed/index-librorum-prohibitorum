#include <iostream>
#include <vector>

using namespace std;

string pattern[2];


char get_match(int i, int j) {
    if (0 <= i && i < pattern[0].size() && 0 <= j && j < pattern[0].size()) {
        if (j - i + 1 == 3) {
            if (pattern[0][i] == 'x' && pattern[0][i + 1] == '.' && pattern[0][i + 2] == 'x' &&
                    pattern[1][i] == 'x' && pattern[1][i + 1] == 'x' && pattern[1][i + 2] == 'x') {
                return 'C';
            } else if (pattern[0][i] == 'x' && pattern[0][i + 1] == 'x' && pattern[0][i + 2] == 'x' &&
                       pattern[1][i] == '.' && pattern[1][i + 1] == 'x' && pattern[1][i + 2] == 'x') {
                return 'E';
            }
        } else if (j - i + 1 == 2) {
            if (pattern[0][i] == 'x' && pattern[0][i + 1] == '.' &&
                    pattern[1][i] == 'x' && pattern[1][i + 1] == 'x') {
                return 'A';
            } else if (pattern[0][i] == 'x' && pattern[0][i + 1] == 'x' &&
                       pattern[1][i] == 'x' && pattern[1][i + 1] == 'x') {
                return 'B';
            } else if (pattern[0][i] == 'x' && pattern[0][i + 1] == 'x' &&
                       pattern[1][i] == '.' && pattern[1][i + 1] == 'x') {
                return 'D';
            }
        }
    }

    return 0;
}

int main() {
    int _ = 5;

    while (_--) {
        cin >> pattern[0];
        cin >> pattern[1];
        int N = pattern[0].size();

        bool dp[N + 1];
        char ch[N + 1];
        int pred[N + 1];
        dp[0] = true;

        for (int i = 2; i <= N; i++) {
            char match1 = get_match(i - 2, i - 1), match2 = get_match(i - 3, i - 1);
            if (match1 && dp[i - 2]) {
                dp[i] = true;
                ch[i] = match1;
                pred[i] = i - 2;
            } else if (match2 && dp[i - 3]) {
                dp[i] = true;
                ch[i] = match2;
                pred[i] = i - 3;
            }
        }

        vector<char> carr;

        int i = N;
        while (i) {
            carr.push_back(ch[i]);
            i = pred[i];
        }

        for (char c : vector<char>(carr.rbegin(), carr.rend()))
            cout << c;
        cout << "\n";
    }

    return 0;
}
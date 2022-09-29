#include <iostream>
using namespace std;

string S, T;

void trim() {
    int i = 0;
    for (; i < S.size(); i++)
        if (S[i] != '0') break;
    S = S.substr(i, S.size() - i);
    i = 0;
    for (; i < T.size(); i++)
        if (T[i] != '0') break;
    T = T.substr(i, T.size() - i);
}

int main() {
    cin.sync_with_stdio(false); cout.tie(nullptr);
    cin >> S >> T;
    trim();
    if (S.size() > T.size()) {
        printf("S");
    } else if (T.size() > S.size()) {
        printf("T");
    } else {
        int i = 0;
        for (; i < T.size(); i++) {
            if (S[i] > T[i]) {
                printf("S");
                break;
            } else if (T[i] > S[i]) {
                printf("T");
                break;
            }
        }
        if (i == T.size()) printf("E");
    }
    return 0;
}
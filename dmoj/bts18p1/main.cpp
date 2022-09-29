#include <iostream>
#define inf 2000000000
using namespace std;

string a, b;
int K, N;

int main() {
    getline(cin, a);
    getline(cin, b);
    cin >> K;
    N = 0;

    for (int i = 0; i < a.size(); i++) {
        if (a[i] == ' ' || b[i] == ' ') {
            if (a[i] != b[i]) {
                N = inf;
                break;
            }
        } else if (a[i] != b[i]) {
            N++;
        }
    }

    if (N <= K) {
        cout << "Plagiarized" << '\n';
    } else {
        cout << "No plagiarism" << '\n';
    }

    return 0;
}
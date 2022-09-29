#include <iostream>

using namespace std;

int main() {
    int x;
    cin >> x;
    long first;
    long second;
    for (int i = 0; i < x; i++) {
        cin >> first;
        cin >> second;
        cout << first + second << endl;
    }
    return 0;
}
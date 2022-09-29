#include <iostream>
using namespace std;

int main() {
    long long lo = 1, hi = 2000000000;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        cout << mid << endl;
        string str;
        cin >> str;
        if (str == "SINKS") {
            lo = mid + 1;
        } else if (str == "FLOATS") {
            hi = mid - 1;
        } else break;
    }
    return 0;
}
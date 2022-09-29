#include <iostream>
#include <vector>
#define INFINITY 99999999
using namespace std;

vector<int> coins(101, -1);
vector<int> have;

int get(int amt) {
    if (amt < 0) return INFINITY;
    if (coins[amt] != -1) return coins[amt];
    int minVal = INFINITY;

    for (int h : have)
        minVal = min(minVal, get(amt - h));

    return coins[amt] = minVal + 1;
}

int main() {
    for (int i = 0; i < 5; i++) {
        fill(coins.begin(), coins.end(), -1);
        have.clear();
        coins[0] = 0;

        int target, c;
        scanf("%d%d", &target, &c);

        while (c--) {
            int v;
            scanf("%d", &v);
            have.push_back(v);
        }

        printf("%d\n", get(target));
    }
    return 0;
}
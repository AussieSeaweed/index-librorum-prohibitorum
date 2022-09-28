#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> barns(100000);
int N, C;

int canPut(int dist) {
    int count = 1;
    int last = barns[0];
    for (int i = 1; i < N; i++) {
        if (barns[i] - last >= dist) {
            count++;
            last = barns[i];
        }
    }

    return count;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &C);

        for (int i = 0; i < N; i++)
            scanf("%d", &barns[i]);

        sort(barns.begin(), barns.begin() + N);

        int lo = 0, hi = 1000000000, mid = (lo + hi) / 2;;
        while (lo <= hi) {
            if (canPut(mid) < C) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
            mid = (hi + lo) / 2;
        }

        printf("%d\n", mid);
    }
    return 0;
}
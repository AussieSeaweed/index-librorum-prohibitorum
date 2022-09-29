#include <bits/stdc++.h>

int tides[100];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &tides[i]);

    std::sort(tides, tides+N);

    int low, high;

    low = (N-1 >> 1);
    high = low + 1;

    while (true) {
        if (low >= 0) {
            std::cout << tides[low] << " ";
            low--;
        }

        if (high < N) {
            std::cout << tides[high] << " ";
            high++;
        }

        if (low < 0 && high >= N)
            break;
    }
}
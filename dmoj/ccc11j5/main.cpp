#include <iostream>

int N;
int x;
int cases[7] = {1,1,1,1,1,1,1};

int main() {
    std::cin >> N;
    for (int i = 1; i < N; i++) {
        std::cin >> x;
        cases[x] = cases[x] * (1 + cases[i]);
    }

    printf("%d", cases[N]);
    return 0;
}
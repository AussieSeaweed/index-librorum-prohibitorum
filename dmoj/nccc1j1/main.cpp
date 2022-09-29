#include <iostream>

bool containsZero(int num) {
    while (num > 0) {
        if (num % 10 == 0)
            return true;
        num /= 10;
    }
    return false;
}

int N;

int main() {
    scanf("%d", &N);
    N++;
    while (true) {
        if (!containsZero(N))
            break;
        N++;
    }

    printf("%d\n", N);
}
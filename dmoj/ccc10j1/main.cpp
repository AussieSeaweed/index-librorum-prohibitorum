#include <iostream>

int main() {
    int I;
    scanf("%d", &I);
    int N = 0;

    for (int i = 0; i <= 5; i++) {
        for (int j = i; j <= 5; j++) {
            if (i + j == I) N++;
        }
    }

    printf("%d", N);
    return 0;
}
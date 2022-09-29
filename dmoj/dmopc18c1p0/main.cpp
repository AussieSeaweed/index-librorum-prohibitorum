#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;

    if (a <= b && b <= c) {
        printf("Good job!\n");
    } else {
        printf("Try again!\n");
    }
    return 0;
}
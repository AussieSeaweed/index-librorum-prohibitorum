#include <iostream>

int main() {
    int digit[4];

    scanf("%d%d%d%d", digit, digit + 1, digit + 2, digit + 3);

    printf((digit[0] == 8 || digit[0] == 9) && (digit[3] == 8 || digit[3] == 9) && digit[1] == digit[2] ? "ignore\n" : "answer\n");

    return 0;
}
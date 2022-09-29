#include <iostream>
#include <vector>

unsigned long long factorial(unsigned long long num) {
    if (33 < num) return 0;
    unsigned long long product = 1;
    for (int i = 2; i <= num; i++)
        product = product * i % 4294967296;

    return product;
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        unsigned long long num;
        scanf("%llu", &num);
        printf("%llu\n", factorial(num));
    }
    return 0;
}
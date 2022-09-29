#include <iostream>

int main() {
    long long a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld", std::max(std::abs(a - b), std::max(a + b, a * b)));
    return 0;
}
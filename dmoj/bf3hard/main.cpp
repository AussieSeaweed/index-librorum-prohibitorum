#include <iostream>
#include <ctime>
using namespace std;

inline unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long modulus) {
    unsigned long long x = 0, y = a % modulus;
    while (b) {
        if (b & 1) x = (x + y) % modulus;
        y = (y << 1) % modulus;
        b >>= 1;
    }
    return x % modulus;
}

inline unsigned long long powmod(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    if (modulus == 1) return 0;
    unsigned long long result = 1;
    base %= modulus;
    while (exponent) {
        if (exponent & 1)
            result = mulmod(result, base, modulus);
        exponent >>= 1;
        base = mulmod(base, base, modulus);
    }
    return result;
}

inline bool miller_rabin(unsigned long long num, int k) {
    if (num == 2) return true;
    if (num < 2 || (num % 2 == 0)) return false;
    srand(time(nullptr));
    unsigned long long d = num - 1;
    while (d % 2 == 0)
        d /= 2;
    while (k--) {
        unsigned long long tmp = d, x = powmod(rand() % (num - 1) + 1, d, num);
        while (tmp != num - 1 && x != 1 && x != num - 1) {
            x = mulmod(x, x, num);
            tmp *= 2;
        }
        if (x != num - 1 && tmp % 2 == 0) return false;
    }
    return true;
}


int main() {
    unsigned long long initial;
    scanf("%llu", &initial);

    if (initial <= 2) {
        printf("2");
        return 0;
    }

    if (!(initial & 1)) initial++;
    for (;;initial += 2) {
        if (miller_rabin(initial, 3)) {
            printf("%llu", initial);
            break;
        }
    }
    return 0;
}
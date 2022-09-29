#include <iostream>
#include <cstring>

char s[1000002];
unsigned int n;

unsigned int hash1() {
    unsigned int ret = 0;

    for (unsigned int i = 0; i < n; ++i)
        ret += (i + 1) * (n - i) * s[i];

    return ret;
}

unsigned int hash2() {
    static unsigned int mod = 2147483647;
    unsigned int ret = 0;

    for (unsigned int i = 0; i < n; ++i)
        ret += s[i];

    for (unsigned int i = 1; i < n; ++i)
        ret = 2 * ret % mod;

    return ret;
}

unsigned int hash() {
    return hash1() + hash2();
}

int main() {
    fgets(s, 1000002, stdin);
    n = strlen(s) - 1;

    printf("%08X", hash());

    return 0;
}
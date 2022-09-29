int setbits(unsigned long long n) {
    return __builtin_popcountll(n);
}
#include <iostream>

int N, masks[1 << 10];
long long int count;

int main() {
    std::cin >> N;

    while (N--) {
        long long int n;
        std::cin >> n;

        int set = 0;

        while (n)
            set |= 1 << (n % 10), n /= 10;

        for (int subset = set; subset; subset = (subset - 1) & set)
            count += (__builtin_popcount(subset) & 1 ? 1 : -1) * masks[subset]++;
    }

    std::cout << count << std::endl;

    return 0;
}
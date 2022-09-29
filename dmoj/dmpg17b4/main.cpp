#include <bits/stdc++.h>

int main() {
    std::vector<int> nums(1024);

    for (int count = 1024, i = 511, j = 512; i >= 0; i--, j++) {
        nums[j] = count--;
        nums[i] = count--;
    }

    for (int n : nums)
        printf("%d\n", n);

    return 0;
}
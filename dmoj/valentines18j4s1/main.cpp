#include <bits/stdc++.h>

bool isPalindrome(int n) {
    std::vector<int> nums;
    while (n > 0) {
        nums.push_back(n % 10);
        n /= 10;
    }

    for (int i = 0, j = nums.size() - 1; i < nums.size() && j >= 0 && i <= j; i++, j--) {
        if (nums[i] != nums[j]) {
            return false;
        }
    }

    return true;
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);

    bool flag = false;
    int num;
    for (int i = (N+M)/2, j = (N+M)/2;; i++, j--) {
        flag = false;
        if (i <= M) {
            if (isPalindrome(i)) {
                flag = true;
                num = i;
            }
        }
        if (j >= N) {
            if (isPalindrome(j)) {
                flag = true;
                num = j;
            }
        }
        if (flag) break;
    }

    printf("%d", num);

    return 0;
}
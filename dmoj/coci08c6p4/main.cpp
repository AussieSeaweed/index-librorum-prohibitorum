#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> nums[3];

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int value;
        scanf("%d", &value);
        nums[value % 3].push_back(value);
    }

    int zero = nums[0].size(), one = nums[1].size(), two = nums[2].size();

    if (one && two && zero && one + two + 1 >= zero) {
        int reserve = nums[0].back();
        nums[0].pop_back();

        while (!nums[1].empty()) {
            if (!nums[0].empty()) {
                printf("%d ", nums[0].back());
                nums[0].pop_back();
            }
            printf("%d ", nums[1].back());
            nums[1].pop_back();
        }

        printf("%d ", reserve);

        while (!nums[2].empty()) {
            printf("%d ", nums[2].back());
            nums[2].pop_back();
            if (!nums[0].empty()) {
                printf("%d ", nums[0].back());
                nums[0].pop_back();
            }
        }
    } else if (one && !two && one + 1 >= zero) {
        if (!nums[0].empty()) {
            printf("%d ", nums[0].back());
            nums[0].pop_back();
        }

        while (!nums[1].empty()) {
            printf("%d ", nums[1].back());
            nums[1  ].pop_back();
            if (!nums[0].empty()) {
                printf("%d ", nums[0].back());
                nums[0].pop_back();
            }
        }
    } else if (two && !one && two + 1 >= zero) {
        if (!nums[0].empty()) {
            printf("%d ", nums[0].back());
            nums[0].pop_back();
        }

        while (!nums[2].empty()) {
            printf("%d ", nums[2].back());
            nums[2].pop_back();
            if (!nums[0].empty()) {
                printf("%d ", nums[0].back());
                nums[0].pop_back();
            }
        }
    } else {
        printf("impossible");
    }

    printf("\n");

    return 0;
}
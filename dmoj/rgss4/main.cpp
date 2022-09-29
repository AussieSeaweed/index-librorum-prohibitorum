#include <iostream>
#include <vector>
using namespace std;

vector<int> nums(1000);
vector<int> most(1000);
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);
        nums[i] = num;
        most[i] = num;
    }
    int ans = most[0];
    for (int i = 1; i < N; i++) {
        int high = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (nums[i] > nums[j]) {
                high = max(high, most[j]);
            }
        }
        most[i] += high;
        ans = max(ans, most[i]);
    }

    printf("%d", ans);
    return 0;
}
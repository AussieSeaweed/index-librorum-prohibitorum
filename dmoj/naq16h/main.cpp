#include <iostream>
#include <vector>
#define INFINITY 99999999
using namespace std;

int H, B, hsum = 0, bsum = 0, target;
vector<int> hotdog(100), bun(100);
vector<int> hotdogs(100001, INFINITY);
vector<int> buns(100001, INFINITY);

int main() {
    scanf("%d", &H);

    for (int i = 0; i < H; i++) {
        scanf("%d", &hotdog[i]);
        hsum += hotdog[i];
    }

    scanf("%d", &B);

    for (int i = 0; i < B; i++) {
        scanf("%d", &bun[i]);
        bsum += bun[i];
    }

    target = min(hsum, bsum);
    hotdogs[0] = 0;
    buns[0] = 0;

    for (int h : hotdog) {
        for (int n = target - h; n >= 0; n--) {
            if (hotdogs[n] != INFINITY) {
                hotdogs[n + h] = min(hotdogs[n + h], hotdogs[n] + 1);
            }
        }
    }

    for (int b : bun) {
        for (int n = target - b; n >= 0; n--) {
            if (buns[n] != INFINITY) {
                buns[n + b] = min(buns[n + b], buns[n] + 1);
            }
        }
    }

    int ans = INFINITY;

    for (int i = 1; i <= target; i++) {
        if (hotdogs[i] != INFINITY && buns[i] != INFINITY) {
            ans = min(ans, hotdogs[i] + buns[i]);
        }
    }

    if (ans != INFINITY) {
        printf("%d", ans);
    } else {
        printf("impossible");
    }

    return 0;
}
#include <bits/stdc++.h>

int isColored(int level, int x, int y) {
    int unit = std::pow(5, level-1);
    if ((unit <= x && x < 2*unit && 0 <= y && y < unit) ||
            (2*unit <= x && x < 3*unit && 0 <= y && y < unit) ||
            (3*unit <= x && x < 4*unit && 0 <= y && y < unit) ||
            (2*unit <= x && x < 3*unit && unit <= y && y < 2*unit)) {
        return true;
    } else if (((unit <= x && x < 2*unit && unit <= y && y < 2*unit) ||
               (2*unit <= x && x < 3*unit && 2*unit <= y && y < 3*unit) ||
               (3*unit <= x && x < 4*unit && unit <= y && y < 2*unit)) && level != 1) {
        return isColored(level-1,x%unit,y%unit);
    } else {
        return false;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    int m,x,y;
    while (N--) {
        scanf("%d%d%d", &m, &x, &y);
        if (isColored(m,x,y))
            printf("crystal\n");
        else
            printf("empty\n");
    }
}
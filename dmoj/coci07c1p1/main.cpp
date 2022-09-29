#include <bits/stdc++.h>

int main() {
    int x1, y1, x2, y2, x3, y3;
    scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);

    int xans;
    int yans;

    if (x1 == x3) xans = x2;
    else if (x1 == x2) xans = x3;
    else if (x2 == x3) xans = x1;
    if (y1 == y3) yans = y2;
    else if (y1 == y2) yans = y3;
    else if (y2 == y3) yans = y1;

    printf("%d %d", xans, yans);
}
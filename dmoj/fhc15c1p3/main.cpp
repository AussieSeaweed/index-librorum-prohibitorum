#include <iostream>
#include <cstring>

long long sfree[2001][2001], sful[2001][2001], A, B;

long long stress_free(int a, int b) {
    if (a > A || b > B) return 0;
    if (~sfree[a][b]) return sfree[a][b];
    if (a == A && b == B) return sfree[a][b] = 1;
    if (a <= b) return sfree[a][b] = 0;

    return sfree[a][b] = (stress_free(a + 1, b) + stress_free(a, b + 1)) % 1000000007;
}

long long stressful(int a, int b) {
    if (a > A || b > B) return 0;
    if (~sful[a][b]) return sful[a][b];
    if (b == B) return sful[a][b] = 1;
    if (a > b) return sful[a][b] = 0;

    return sful[a][b] = (stressful(a + 1, b) + stressful(a, b + 1)) % 1000000007;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        A = 0, B = 0;
        char ch;
        scanf(" %c", &ch);

        while (ch != '-') {
            A *= 10;
            A += ch - '0';
            scanf("%c", &ch);
        }

        scanf("%c", &ch);

        while (ch != '\n') {
            B *= 10;
            B += ch - '0';
            scanf("%c", &ch);
        }

        memset(sfree, -1, sizeof sfree);
        memset(sful, -1, sizeof sful);

        printf("Case #%d: %lld %lld\n", t, stress_free(1, 0), stressful(0, 0));
    }

    return 0;
}
#include <iostream>

unsigned int Q;
unsigned short int N, permutation[300], indices[300], values[300], x, y;
char c;

int main() {
    scanf("%hu %u", &N, &Q);

    for (unsigned short i = 0; i < N; ++i)
        permutation[i] = indices[i] = i;

    while (Q--) {
        scanf(" %c", &c);

        switch (c) {
            case 'B':
                scanf("%hu %hu", &x, &y);
                --x, --y;
                std::swap(permutation[indices[x]], permutation[indices[y]]);
                std::swap(indices[x], indices[y]);
                break;
            case 'E':
                scanf("%hu %hu", &x, &y);
                --x, --y;
                std::swap(indices[permutation[x]], indices[permutation[y]]);
                std::swap(permutation[x], permutation[y]);
                break;
            case 'Q':
                for (unsigned short i = 0; i < N; ++i)
                    scanf("%hu", values + i);

                printf("%hu", values[indices[0]]);
                for (unsigned short i = 1; i < N; ++i)
                    printf(" %hu", values[indices[i]]);
                printf("\n");
                break;
            default:
                break;
        }
    }

    return 0;
}
#include <iostream>

int gstring[100001];
std::string rawgstring;
int N;
int Q;

int main() {
    std::cin >> rawgstring;
    N = rawgstring.length();
    gstring[-1] = 0;


    for (int i = 0; i < N; i++)
        if (rawgstring[i] == 'G')
            gstring[i] = gstring[i - 1] + 1;
        else
            gstring[i] = gstring[i - 1];

    scanf("%d", &Q);

    int i, j;

    for (int _ = 0; _ < Q; _++) {
        scanf("%d%d", &i, &j);
        printf("%d\n", gstring[j] - gstring[i-1]);
    }

    return 0;
}
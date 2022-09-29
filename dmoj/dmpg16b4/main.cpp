#include <bits/stdc++.h>

int f(int m) {
    int mcopy = m;

    std::deque<int> num;

    while (mcopy > 0) {
        num.push_front(mcopy % 10);
        mcopy /= 10;
    }

    int logval = ((int) log10(m)) + 1;

    for(int i = 0; i < num.size(); i++)
        num[i] = (int) round(pow(num[i], logval));

    int returnval = 0;

    for (int i = 0; i < num.size(); i++)
        returnval += num[i];

    return returnval;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int M;
        scanf("%d", &M);

        std::map<int, int> visited;

        visited.insert(std::make_pair(M, 0));


        bool eq = false;

        int i;

        for(i = 1;; i++) {
            int newM = f(M);

            if (visited.count(newM)) {
                M = newM;
                break;
            }

            visited.insert(std::make_pair(newM, i));
            M = newM;
        }

        if (i - visited[M] == 1) eq = true;

        if (eq)
            printf("Equilibrium: Bob's investment becomes $%d after %d second(s)!\n", M, i - 1);
        else
            printf("Instability: Loop of length %d encountered after %d second(s)!\n", i - visited[M], i - (i - visited[M]));
    }

    return 0;
}
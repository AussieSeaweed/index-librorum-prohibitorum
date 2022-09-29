#include <bits/stdc++.h>

std::vector<int> friends(10000, 0);

int main() {
    int N;
    scanf("%d", &N);

    while (N--) {
        int x, y;
        scanf("%d%d", &x, &y);

        friends[x] = y;
    }

    while (true) {
        int x, y;
        scanf("%d%d", &x, &y);

        if (!x && !y) break;

        std::set<int> visited;
        int person = friends[x];
        int degree = 0;
        while (true) {
            if (person == 0 || visited.count(person)) {
                degree = -1;
                break;
            } else if (person == y) {
                break;
            }

            visited.insert(person);
            person = friends[person];
            degree++;
        }

        if (degree == -1) {
            printf("No\n");
        } else {
            printf("Yes %d\n", degree);
        }
    }
    return 0;
}
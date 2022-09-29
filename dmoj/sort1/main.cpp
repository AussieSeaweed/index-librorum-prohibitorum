#include <iostream>
#include <vector>

std::vector<int> vec;
int T;

void printVec() {
    for (int i : vec) printf("%d ", i);
    printf("\n");
}

int main() {
    scanf("%d", &T);
    vec.resize(T);
    for (int i = 0; i < T; i++)
        scanf("%d", &vec[i]);

    bool modified;

    printVec();

    do {
        modified = false;
        for (int i = 0; i < T - 1; i++) {
            if (vec[i] > vec[i + 1]) {
                int tmp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = tmp;
                printVec();
                modified = true;
            }
        }
    } while (modified);

    return 0;
}
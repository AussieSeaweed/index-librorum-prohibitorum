#include <iostream>

char faceup(int C);

int count;

int query(int index) {
    ++count;

    return faceup(index + 1) - 'A';
}

void play() {
    bool flag[25];
    int indices[25];

    std::fill(flag, flag + 25, false);
    std::fill(indices, indices + 25, 0);

    for (int i = 0; i < 50; ++i) {
        int c = query(i);

        if (flag[c] && (count & 1 || indices[c] != i - 1)) {
            if (!(count & 1))
                query(i);

            query(indices[c]);
        } else if (!flag[c]) {
            flag[c] = true;
            indices[c] = i;
        }
    }
}
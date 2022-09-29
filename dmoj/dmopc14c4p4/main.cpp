#include <iostream>
#include <vector>

using namespace std;

vector<int> candidates;
char count[26], dict[30]; int decrypter[30];
string str;

int main() {
    cin >> str;

    for (int i = 0; i <= str.size() - 9; i++) {
        fill(count, count + 26, 0);
        for (int j = i; j < i + 9; j++) {
            count[str[j] - 'A']++;
        }
        bool unique_chars_exist = true;
        int multiple_count = 0;

        for (int j = 0; j < 26 && unique_chars_exist; j++) {
            if (count[j] == 2 && ++multiple_count > 2)
                unique_chars_exist = false;
            else if (count[j] > 2)
                unique_chars_exist = false;
        }

        if (unique_chars_exist && str[i] == str[i + 4] && str[i + 1] == str[i + 8]) {
            candidates.push_back(i);
        }
    }

    if (candidates.empty()) {
        printf("KeyNotFoundError\n");
        return 0;
    }

    int N;
    scanf("%d", &N);

    while (N--) {
        scanf("%s", dict);
        for (int i = 0; i < 26; i++) {
            decrypter[dict[i] - 'A'] = i;
        }

        for (int i : candidates) {
            if ('H' == 'A' + decrypter[str[i] - 'A'] &&
                'A' == 'A' + decrypter[str[i + 1] - 'A'] &&
                'I' == 'A' + decrypter[str[i + 2] - 'A'] &&
                'L' == 'A' + decrypter[str[i + 3] - 'A'] &&
                'Y' == 'A' + decrypter[str[i + 5] - 'A'] &&
                'D' == 'A' + decrypter[str[i + 6] - 'A'] &&
                'R' == 'A' + decrypter[str[i + 7] - 'A']) {

                for (char ch : str) {
                    printf("%c", 'A' + decrypter[ch - 'A']);
                }

                printf("\n");
                return 0;
            }
        }
    }

    printf("KeyNotFoundError\n");

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string str;
vector<int> indices['z' + 1];
int Q;

int main() {
    getline(cin, str);
    for (int i = 0; i < str.size(); i++)
        if (str[i] != ' ')
            indices[str[i]].push_back(i);

    cin >> Q;

    while (Q--) {
        int i, j; char c;
        scanf(" %d %d %c", &i, &j, &c);
        i--, j--;

        auto a = lower_bound(indices[c].begin(), indices[c].end(), i), b = upper_bound(indices[c].begin(), indices[c].end(), j);

        printf("%d\n", b - a);
    }

    return 0;
}
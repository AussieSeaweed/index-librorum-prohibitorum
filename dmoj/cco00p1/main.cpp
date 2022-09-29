#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

unordered_map<char, vector<int>> graph;
unordered_map<char, vector<int>> sets;
set<char> names;

void get_aux(char ch, unordered_map<char, bool>& visited, set<int>& elems) {
    visited[ch] = true;
    elems.insert(sets[ch].begin(), sets[ch].end());

    for (char adj : graph[ch]) {
        if (!visited[adj]) {
            get_aux(adj, visited, elems);
        }
    }
}

set<int> get(char ch) {
    unordered_map<char, bool> visited;
    set<int> elems;

    get_aux(ch, visited, elems);

    return elems;
}

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        char a, b, str[9];
        scanf(" %c%s %c", &a, str, &b);
        if (isupper(a)) names.insert(a);
        if (isupper(b)) names.insert(b);
        if (islower(b))
            sets[a].push_back(b);
        else
            graph[a].push_back(b);
    }

    for (char ch : names) {
        printf("%c = {", ch);
        set<int> elems = get(ch);
        if (!elems.empty()) {
            printf("%c", *elems.begin());
            for (auto i = ++elems.begin(); i != elems.end(); i++)
                printf(",%c", *i);
        }
        printf("}\n");
    }
    return 0;
}
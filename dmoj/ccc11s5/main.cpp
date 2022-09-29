#include <bits/stdc++.h>

std::vector<bool> turnOff(std::vector<bool> str, int index) {
    str[index] = 1;
    int i, consec;
    for (i = 0, consec = 0; i < str.size(); i++) {
        if (str[i] == 1) {
            consec++;
        } else {
            if (consec >= 4) {
                for (int j = i-consec; j < i; j++) {
                    str[j] = 0;
                }
            }
            consec = 0;
        }
    }
    if (consec >= 4) {
        for (int j = i-consec; j < i; j++) {
            str[j] = 0;
        }
    }
    return str;
}

int main() {
    int N;
    scanf("%d", &N);
    std::vector<bool> lights;
    int intVal;
    while (N--) {
        scanf("%d", &intVal);
        lights.push_back(intVal);
    }

    std::queue<std::pair<std::vector<bool>, int>> q;
    std::set<std::vector<bool>> visited;
    q.push(std::make_pair(lights, 0));
    visited.insert(lights);
    int ans;
    while (!q.empty()) {
        std::pair<std::vector<bool>, int> cur = q.front(); q.pop();
        std::vector<bool> curStr = cur.first;
        int step = cur.second;

        bool isAllZero = true;
        for (int i = 0; i < curStr.size(); i++)
            if (curStr[i] != 0) {
                isAllZero = false;
                break;
            }

        if (isAllZero) {
            ans = step;
            break;
        }

        for (int i = 0; i < curStr.size(); i++) {
            if (curStr[i] == 0 && ((i != 0 && curStr[i - 1] == 1) || (i != curStr.size() - 1 && curStr[i + 1] == 1))) {
                std::vector<bool> newStr = turnOff(curStr, i);
                if (!visited.count(newStr)) {
                    q.push(std::make_pair(newStr, step+1));
                    visited.insert(newStr);
                }
            }
        }
    }
    printf("%d", ans);
}
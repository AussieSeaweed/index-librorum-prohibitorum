#include <iostream>

bool valid(std::string str) {
    if (str.size() == 0) {
        return false;
    } else if (str.size() == 1) {
        if (str[0] == 'A')
            return true;
        else
            return false;
    } else if (str[0] == 'A') {
        if (str[1] == 'N') {
            return valid(str.substr(2, str.size() - 2));
        } else {
            return false;
        }
    } else if (str[0] == 'B') {
        int S_index = -1;
        int depth = 0;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == 'B') depth++;
            else if (str[i] == 'S') {
                depth--;
                if (!depth) {
                    S_index = i;
                    break;
                }
            }
        }

        if (S_index != str.size() - 1) {
            if (str[S_index + 1] == 'N') {
                return valid(str.substr(1, S_index - 1)) && valid(str.substr(S_index + 2, str.size() - S_index - 2));
            } else {
                return false;
            }
        } else {
            return valid(str.substr(1, S_index - 1));
        }
    } else {
        return false;
    }
}

int main() {
    while (true) {
        std::string str;
        std::cin >> str;

        if (str == "X") break;

        std::cout << (valid(str) ? "YES\n" : "NO\n");
    }

    return 0;
}
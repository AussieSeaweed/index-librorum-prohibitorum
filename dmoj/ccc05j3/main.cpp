#include <bits/stdc++.h>

std::vector<std::string> instructions;

int main() {
    instructions.push_back("HOME");

    while (true) {
        std::string str;
        std::cin >> str;

        if (str == "SCHOOL") break;

        instructions.push_back(str);
    }

    for (int i = instructions.size() - 1; i >= 0; i-=2) {
        std::string dir = instructions[i];
        std::string place = instructions[i-1];

        if (place != "HOME") place += " street";

        if (dir == "L")
            dir = "RIGHT";
        else
            dir = "LEFT";

        std::cout << "Turn " << dir << (place == "HOME" ? " into your " : " onto ") << place << ".\n";
    }
}
#include <iostream>

bool isPalindrome(std::string str) {
    int i, j;
    for (i = 0, j = str.size()-1; i <= j; i++, j--)
        if (str[i] != str[j])
            return false;
    return true;
}

std::string in;

int main() {
    std::cin >> in;

    bool odd = true;
    for (int i = 0; i < in.size(); i++)
        for (int j = 1; j <= in.size()-i; j++)
            if (isPalindrome(in.substr(i,j)))
                if (!(j & 1)) {
                    odd = false;
                    break;
                }

    printf(odd ? "Odd\n" : "Even\n");
    return 0;
}
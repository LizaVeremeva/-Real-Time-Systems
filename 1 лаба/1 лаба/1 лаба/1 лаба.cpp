#include <iostream>
#include <string>

int main() {
    std::string s = "01234";
    for (unsigned int i = s.size() - 1; i >= 0; i--) {
        std::cout << s[i] << std::endl;
    }
    return 0;
}
#include <format>
#include <iostream>
#include <string>

int main() {
    std::string name = "";
    std::cout << "What's your name?" << std::endl;
    std::cin >> name;
    std::cout << std::format("Hello, {}!\n", name);
    return 0;
}
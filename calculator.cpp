#include <format>
#include <iostream>
#include <string>

int main() {
    std::string menu = "Choose one of the following options:\n";
    std::cout << std::format("{}\n", menu);
    return 0;
}
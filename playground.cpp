#include <iostream>
#include <cstring>

int main() {
    char buffer[100];
    strcpy(buffer, "Hi");

    std::cout << buffer << " Length is " << strlen(buffer) << std::endl;
}
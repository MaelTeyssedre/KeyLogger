#include "Keylogger.hpp"
#include <iostream>
#include <filesystem>


Keylogger::Keylogger(std::string &outputPath)
    : _output(outputPath)
{
    std::cout << "Starting program at " << std::filesystem::current_path().c_str() << std::endl;
    std::cout << "Output path : " << _output << std::endl;
}


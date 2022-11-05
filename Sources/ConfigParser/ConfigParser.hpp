#ifndef CONFIGPARSER_HPP_
#define CONFIGPARSER_HPP_

#include <map>
#include <vector>
#include <any>

class ConfigParser {
    public:
        ConfigParser(const std::string &);
        virtual ~ConfigParser() = default;
        std::string getField(const std::string &) const;
        std::vector<std::string> getListField(const std::string &) const;
    private:
        std::vector<std::string> _getFile(const std::string &) const;
        void _addStr(std::pair<std::string, std::string> &);
        std::pair<std::string, std::string> _split(std::string &, char) const;
        std::string _removeBorder(std::string) const;
        void _dispContent();
        std::pair<std::string, std::vector<std::string>> _parseList(std::pair<std::string, std::string> &) const;
    private:
        std::map<std::string, std::string> _strMap;
        std::map<std::string, std::vector<std::string>> _listMap;
        bool _debug;
};

#endif /* !CONFIGPARSER_HPP_ */

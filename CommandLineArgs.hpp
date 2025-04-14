#ifndef COMMAND_LINE_ARGS_HPP
#define COMMAND_LINE_ARGS_HPP

#include <string>
#include <unordered_map>

class CommandLineArgs {

    public:

        CommandLineArgs(int argc, char* argv[]);

        std::string getString(const std::string& key, const std::string& defaultValue = "") const;
        char getChar(const std::string& key, char defaultValue = ',') const;
        int getInt(const std::string& key, int defaultValue = 0) const;
        bool has(const std::string& key) const;

    private:

        std::unordered_map<std::string, std::string> args;
};

#endif

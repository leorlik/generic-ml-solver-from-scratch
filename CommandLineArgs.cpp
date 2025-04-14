#include "CommandLineArgs.hpp"
#include <stdexcept>

CommandLineArgs::CommandLineArgs(int argc, char* argv[]) {

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        size_t eq_pos = arg.find('=');  //Acha o sinal de igual

        // Se o argumento começa com "--" e contém um sinal de igual
        if (arg.substr(0, 2) == "--" && eq_pos != std::string::npos) {

            //Pega chave e valor
            std::string key = arg.substr(2, eq_pos - 2);
            std::string value = arg.substr(eq_pos + 1);
            args[key] = value;
        }
    }
}

std::string CommandLineArgs::getString(const std::string& key, const std::string& defaultValue) const {

    auto it = args.find(key);
    if (it != args.end()) 
        return it->second;

    return defaultValue;

}

char CommandLineArgs::getChar(const std::string& key, char defaultValue) const {

    std::string val = getString(key);

    return val.empty() ? defaultValue : val[0];
}

int CommandLineArgs::getInt(const std::string& key, int defaultValue) const {

    std::string val = getString(key);

    return val.empty() ? defaultValue : std::stoi(val);
}

bool CommandLineArgs::has(const std::string& key) const {

    return args.find(key) != args.end();
    
}

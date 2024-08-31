#include <fstream>
#include <string>
#include <regex>
#include <vector>

#include "Token.hpp"


int main(int argc, char **argv) {
    std::regex all_regex(R"(([a-zA-Z_]\w*\b)|(\b\d+(\.\d+)?\b)|("(\\.|[^\\"])*")|([\+\-\*/%=<>&\|!~^]+)|([;,\(\)\{\}\[\]])|(//.*|/\*[\s\S]*?\*/))");

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<Token> tokens;

    while (std::getline(file, line)) {
        std::string::const_iterator searchStart(line.cbegin());

        while (searchStart != line.cend()) {
            std::smatch match;
            
            if (std::regex_search(searchStart, line.cend(), match, all_regex))
            {
                tokens.push_back(Token(match.str()));
            }
            else
            {
                std::cout << "no match\n";
                ++searchStart;
                continue;
            }
            searchStart = match.suffix().first;
        }
    }

    file.close();

    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }
    std::cout << tokens.size() << std::endl;

    return 0;
}

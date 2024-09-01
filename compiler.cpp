#include <fstream>
#include <string>
#include <regex>
#include <vector>

#include "Token.hpp"

std::vector<Token> get_tokens_from_file(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }

    std::regex all_regex(R"(([a-zA-Z_]\w*\b)|(\b\d+(\.\d+)?\b)|("(\\.|[^\\"])*")|([\+\-\*/%=<>&\|!~^]+)|([;,\(\)\{\}\[\]])|(//.*|/\*[\s\S]*?\*/))");
    std::string line;
    std::vector<Token> tokens;

    while (std::getline(file, line))
    {
        std::string::const_iterator search_start(line.cbegin());

        while (search_start != line.cend()) {
            std::smatch match;
            
            if (std::regex_search(search_start, line.cend(), match, all_regex))
            {
                auto token = Token(match.str());
                tokens.push_back(token);

                if (token.type() == TokenType::Constant)
                {
                    std::cout << "Constant! Prefix=" << match.prefix() << " " << "Sufix=" << match.suffix() << std::endl;
                }
            }
            else
            {
                std::cerr << "Invalid token\n";
                exit(1);
            }
            search_start = match.suffix().first;
        }
    }
    file.close();
    return tokens;
}

int main(int argc, char **argv)
{
    // Stage 1: lexer
    const auto tokens = get_tokens_from_file(argv[1]);
    for (const auto& token : tokens)
    {
        std::cout << token << std::endl;
    }
    // Stage 2: building the AST
    return 0;
}

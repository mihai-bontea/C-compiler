#include <fstream>
#include <string>
#include <regex>
#include <vector>

#include "Token.hpp"
#include "SyntaxTree.hpp"

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

    size_t line_count = 0;
    while (std::getline(file, line))
    {
        std::string::const_iterator search_start(line.cbegin());

        while (search_start != line.cend()) {
            std::smatch match;
            
            if (std::regex_search(search_start, line.cend(), match, all_regex))
            {
                try
                {
                    tokens.push_back(Token(match));
                }
                catch(const std::runtime_error& e)
                {
                    std::cerr << "Error at line " << line_count << ": " << e.what() << std::endl;
                    exit(-1);
                }
            }
            else
            {
                std::cerr << "Invalid token\n";
                exit(1);
            }
            search_start = match.suffix().first;
        }
        ++line_count;
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
    // Use the tokens to build the syntax tree
    std::cout << "All good\n";
    
    return 0;
}

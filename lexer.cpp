#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

struct Token {
    std::string type;
    std::string value;
};

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "[" << token.type << "] " << token.value;
    return os;
}

int main(int argc, char **argv) {


    // Define the regular expressions for different token types
    // std::regex keyword_regex(R"(\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\b)");
    // std::regex identifier_regex(R"(\b[a-zA-Z_][a-zA-Z0-9_]*\b)");
	std::regex identifier_regex(R"([a-zA-Z_]\w*\b)");
    std::regex constant_regex(R"(\b\d+(\.\d+)?\b)");
    std::regex string_literal_regex(R"("(\\.|[^\\"])*")");
    std::regex operator_regex(R"([\+\-\*/%=<>&\|!~^]+)");
    std::regex delimiter_regex(R"([;,\(\)\{\}\[\]])");
	// std::regex delimiter_regex(R"([;,(\)\{\}\[\]])");
    std::regex comment_regex(R"(//.*|/\*[\s\S]*?\*/)");
	std::regex paranteza(R"(\()");

    // Open the C source file
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

            // if (std::regex_search(searchStart, line.cend(), match, keyword_regex)) {
            //     tokens.push_back({"Keyword", match.str()});
			if (std::regex_search(searchStart, line.cend(), match, paranteza)){
				tokens.push_back({"Paranteza", match.str()});
			
            } else if (std::regex_search(searchStart, line.cend(), match, identifier_regex)) {
                tokens.push_back({"Identifier", match.str()});
            } else if (std::regex_search(searchStart, line.cend(), match, constant_regex)) {
                tokens.push_back({"Constant", match.str()});
            } else if (std::regex_search(searchStart, line.cend(), match, string_literal_regex)) {
                tokens.push_back({"String Literal", match.str()});
            } else if (std::regex_search(searchStart, line.cend(), match, operator_regex)) {
                tokens.push_back({"Operator", match.str()});
            } else if (std::regex_search(searchStart, line.cend(), match, delimiter_regex)) {
                tokens.push_back({"Delimiter", match.str()});
            } else if (std::regex_search(searchStart, line.cend(), match, comment_regex)) {
                tokens.push_back({"Comment", match.str()});
            } else {
                // ++searchStart;
                continue;
            }
			// std::cout << match.str() << " ";
            searchStart = match.suffix().first;
        }
    }

    file.close();

    // Print the tokens in order
    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}

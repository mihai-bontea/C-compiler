#include <iostream>
#include <regex>

enum class TokenType {
    Keyword,
    Identifier,
    Constant,
    StringLiteral,
    Operator,
    Delimiter,
    Comment
};

std::string enum_to_str(TokenType type)
{
    switch (type)
    {
    case TokenType::Keyword:
        return "keyword";
    case TokenType::Identifier:
        return "identifier";
    case TokenType::Constant:
        return "constant";
    case TokenType::StringLiteral:
        return "string literal";
    case TokenType::Operator:
        return "operator";
    case TokenType::Delimiter:
        return "delimiter";
    case TokenType::Comment:
        return "comment";
    default:
        return "invalid token";
    }
}


struct Token {
private:
    static std::regex keyword_;
    static std::regex identifier_;
    static std::regex constant_;
    static std::regex string_literal_;
    static std::regex operator_;
    static std::regex delimiter_;
    static std::regex comment_;

    TokenType type_;
    std::string value_;
public:
    explicit Token(const std::string &str): value_{str}
    {
        std::smatch match;
        if (std::regex_search(str.cbegin(), str.cend(), match, keyword_))
        {
            type_ = TokenType::Keyword;
        }
        else if (std::regex_search(str.cbegin(), str.cend(), match, identifier_))
        {
            type_ = TokenType::Identifier;
        }
        else if (std::regex_search(str.cbegin(), str.cend(), match, constant_))
        {
            type_ = TokenType::Constant;
        }
        else if (std::regex_search(str.cbegin(), str.cend(), match, string_literal_))
        {
            type_ = TokenType::StringLiteral;
        }
        else if (std::regex_search(str.cbegin(), str.cend(), match, operator_))
        {
            type_ = TokenType::Operator;
        }
        else if (std::regex_search(str.cbegin(), str.cend(), match, delimiter_))
        {
            type_ = TokenType::Delimiter;
        }
        else if (std::regex_search(str.cbegin(), str.cend(), match, comment_))
        {
            type_ = TokenType::Comment;
        }
        else
        {
            std::cerr << "This shouldn't happen!\n";
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

std::regex Token::keyword_(R"(\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\b)");
std::regex Token::identifier_(R"([a-zA-Z_]\w*\b)");
std::regex Token::constant_(R"(\b\d+(\.\d+)?\b)");
std::regex Token::string_literal_(R"("(\\.|[^\\"])*")");
std::regex Token::operator_(R"([\+\-\*/%=<>&\|!~^]+)");
std::regex Token::delimiter_(R"([;,\(\)\{\}\[\]])");
std::regex Token::comment_(R"(//.*|/\*[\s\S]*?\*/)");

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "[" << enum_to_str(token.type_) << "] " << token.value_;
    return os;
}
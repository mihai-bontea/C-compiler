#include <iostream>
#include <regex>
#include <functional>

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

    void validate_context(const std::smatch &original_match)
    {
        // Get the matching string, and its suffix and prefix
        const auto str = original_match.str();
        auto suffix = original_match.suffix().str();
        auto prefix = original_match.prefix().str();
        // Ignore everything after space for suffix
        suffix = suffix.substr(0, suffix.find(' '));
        // Ignore everything before space for prefix
        prefix = prefix.substr(prefix.find(' ') + 1);

        auto is_str_empty_or_delimiter = [](const std::string &str){
            if (str == "")
                return true;
            
            auto is_char_delimiter = [](char c){
                std::string delim = "([;,(){}[]]) ";
                return delim.find(c) != std::string::npos;
            };
            return std::all_of(str.cbegin(), str.cend(), is_char_delimiter);
        };

        switch(type_)
        {
        case TokenType::Constant:
            if (!is_str_empty_or_delimiter(suffix))
            {
                throw std::runtime_error("Expected delimiter after constant: " + str + suffix);
            }
            break;
        case TokenType::Identifier:
            if (!is_str_empty_or_delimiter(prefix))
            {
                throw std::runtime_error("Unexpected character before identifier: " + prefix + str);
            }
            break;
        case TokenType::Keyword:
            break;
        case TokenType::StringLiteral:
            break;
        case TokenType::Operator:
            break;
        case TokenType::Delimiter:
            break;
        case TokenType::Comment:
            break;
        default:
            break;
        }
    }

public:
    explicit Token(const std::smatch &original_match): value_{original_match.str()}
    {
        std::smatch match;
        if (std::regex_search(value_.cbegin(), value_.cend(), match, keyword_))
        {
            type_ = TokenType::Keyword;
        }
        else if (std::regex_search(value_.cbegin(), value_.cend(), match, identifier_))
        {
            type_ = TokenType::Identifier;
        }
        else if (std::regex_search(value_.cbegin(), value_.cend(), match, constant_))
        {
            type_ = TokenType::Constant;
        }
        else if (std::regex_search(value_.cbegin(), value_.cend(), match, string_literal_))
        {
            type_ = TokenType::StringLiteral;
        }
        else if (std::regex_search(value_.cbegin(), value_.cend(), match, operator_))
        {
            type_ = TokenType::Operator;
        }
        else if (std::regex_search(value_.cbegin(), value_.cend(), match, delimiter_))
        {
            type_ = TokenType::Delimiter;
        }
        else if (std::regex_search(value_.cbegin(), value_.cend(), match, comment_))
        {
            type_ = TokenType::Comment;
        }
        else
        {
            throw std::runtime_error(value_ + " doesn't match any token type!");
        }
        validate_context(original_match);
    }
    TokenType type() const
    {
        return type_;
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
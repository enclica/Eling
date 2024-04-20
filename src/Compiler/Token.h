#pragma once
#include <string>

enum TokenType {
    KEYWORD, IDENTIFIER, NUMBER, STRING, OPERATOR, END
};

struct Token {
    TokenType type;
    std::string value;
};

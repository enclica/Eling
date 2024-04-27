#pragma once
#include "Token.h"
#include <string>
#include <vector>
#include <cctype>

class Lexer {
private:
    std::string input;
    size_t pos = 0;

public:
    Lexer(const std::string &input);
    Token getNextToken();
    bool matchKeyword(const std::string& keyword, TokenType type);
};
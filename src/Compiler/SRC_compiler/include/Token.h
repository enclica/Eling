#pragma once
#include <string>

enum class TokenType {
    FUNC, EXPLICIT, IMPLICIT, CLASS, PRINT, INIT, MAIN_FUNC,
    INCLUDE, C_INCLUDE, PLATFORM_SPEC, CONST, VAR, PRIVATE, PUBLIC,
    IDENTIFIER, STRING, NUMBER, END, PLUS, MINUS, MULT, DIV, UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value= "") : type(type), value(value) {}
};
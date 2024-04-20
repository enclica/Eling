#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& source) : source(source), position(0) {}

Token Lexer::getNextToken() {
    while (position < source.length() && isspace(source[position])) {
        position++;
    }
    if (position >= source.length()) return {END, ""};

    char currentChar = source[position];
    if (isalpha(currentChar)) {
        std::string value;
        while (position < source.length() && isalnum(source[position])) {
            value += source[position++];
        }
        return {IDENTIFIER, value};
    }
    return {END, ""};
}

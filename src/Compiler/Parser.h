#pragma once
#include "Lexer.h"
#include <string>  // Include for std::string

class Parser {
public:
    Parser(Lexer& lexer);
    void parse();
    std::string parseToCpp();  // Method to generate C++ code

private:
    Lexer& lexer;
    Token currentToken;
};

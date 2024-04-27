#pragma once
#include "Lexer.h"
#include <sstream>

class Parser {
private:
    Lexer lexer;
    Token currentToken;
    std::ostringstream output;

    void eat(TokenType type);
    void program();
    void includeStatement();
    void functionDefinition();
    void classDefinition();
    void printStatement();

public:
    Parser(Lexer lexer);
    std::string parse();
};

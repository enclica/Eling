#include "include/Lexer.h"

Lexer::Lexer(const std::string &input) : input(input) {}

Token Lexer::getNextToken() {
    while (pos < input.length() && isspace(input[pos])) pos++;

    if (pos >= input.length()) return Token(TokenType::END, "");

    if (isdigit(input[pos])) {
        std::string number;
        while (pos < input.length() && isdigit(input[pos])) number += input[pos++];
        return Token(TokenType::NUMBER, number);
    }

    if (isalpha(input[pos])) {
        std::string identifier;
        while (pos < input.length() && isalnum(input[pos]) || input[pos] == '_') identifier += input[pos++];
        
        // Keywords matching
        if (identifier == "func") return Token(TokenType::FUNC);
        if (identifier == "explicit") return Token(TokenType::EXPLICIT);
        if (identifier == "implicit") return Token(TokenType::IMPLICIT);
        if (identifier == "class") return Token(TokenType::CLASS);
        if (identifier == "print") return Token(TokenType::PRINT);
        if (identifier == "init") return Token(TokenType::INIT);
        if (identifier == "Main") return Token(TokenType::MAIN_FUNC);
        if (identifier == "include") return Token(TokenType::INCLUDE);
        if (identifier == "cinclude") return Token(TokenType::C_INCLUDE);
        if (identifier == "const") return Token(TokenType::CONST);
        if (identifier == "var") return Token(TokenType::VAR);
        if (identifier == "private") return Token(TokenType::PRIVATE);
        if (identifier == "public") return Token(TokenType::PUBLIC);

        return Token(TokenType::IDENTIFIER, identifier);
    }

    std::string value; 
    switch (input[pos++]) {
        case '"':
            // Parsing a string literal
            value = ""; // Initialize the variable before the switch statement
            while (pos < input.length() && input[pos] != '"') value += input[pos++];
            if (input[pos] == '"') pos++;
            return Token(TokenType::STRING, value);
        default:
            return Token(TokenType::UNKNOWN);
    }

   
}

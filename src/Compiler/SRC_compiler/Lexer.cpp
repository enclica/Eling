#pragma once

#include <string>
#include <cctype>
#include <unordered_map>

// Define token types
enum TokenType {
    END,
    IDENTIFIER,
    NUMBER,
    STRING,
    KEYWORD,
    OPERATOR,
    COMMENT,
    ERROR
};

// Token structure to represent tokens
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& source); // Constructor

    Token getNextToken(); // Get the next token

private:
    std::string source; // Input source code
    size_t position; // Current position in the source code

    // Check if a character is a valid identifier character
    bool isIdentifierChar(char c) const {
        return isalnum(c) || c == '_';
    }

    // Check if a character is a valid number character
    bool isNumberChar(char c) const {
        return isdigit(c) || c == '.';
    }

    // Skip whitespace characters
    void skipWhitespace();

    // Get the next identifier token
    Token getIdentifierToken();

    // Get the next number token
    Token getNumberToken();

    // Get the next string token
    Token getStringToken();

    // Get the next operator token
    Token getOperatorToken();

    // Get the next comment token
    Token getCommentToken();
};

// Constructor
Lexer::Lexer(const std::string& source) : source(source), position(0) {}

// Get the next token
Token Lexer::getNextToken() {
    skipWhitespace();

    // If reached end of source, return END token
    if (position >= source.length()) {
        return {END, ""};
    }

    char currentChar = source[position];

    // Handle different token types
    if (isalpha(currentChar) || currentChar == '_') {
        return getIdentifierToken();
    } else if (isdigit(currentChar) || currentChar == '.') {
        return getNumberToken();
    } else if (currentChar == '"') {
        return getStringToken();
    } else if (currentChar == '/' && position + 1 < source.length() && source[position + 1] == '/') {
        return getCommentToken();
    } else if (currentChar == ':' || currentChar == '(' || currentChar == ')' || currentChar == '{' || currentChar == '}' || currentChar == ';' || currentChar == ',') {
        position++;
        return {OPERATOR, std::string(1, currentChar)};
    } else {
        // Return error token for unknown characters
        position++;
        return {ERROR, std::string(1, currentChar)};
    }
}

// Skip whitespace characters
void Lexer::skipWhitespace() {
    while (position < source.length() && isspace(source[position])) {
        position++;
    }
}

// Get the next identifier token
Token Lexer::getIdentifierToken() {
    std::string value;
    while (position < source.length() && isIdentifierChar(source[position])) {
        value += source[position++];
    }

    // Check if the identifier is a keyword
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"include", KEYWORD},
        {"init", KEYWORD},
        {"print", KEYWORD},
        {"Operation", KEYWORD},
        {"Main", KEYWORD},
        {"Condition", KEYWORD},
        {"Eling", KEYWORD},
        {"redo", KEYWORD},
        {"class", KEYWORD}
    };

    auto it = keywords.find(value);
    if (it != keywords.end()) {
        return {it->second, value};
    } else {
        return {IDENTIFIER, value};
    }
}

// Get the next number token
Token Lexer::getNumberToken() {
    std::string value;
    while (position < source.length() && isNumberChar(source[position])) {
        value += source[position++];
    }
    return {NUMBER, value};
}

// Get the next string token
Token Lexer::getStringToken() {
    std::string value;
    position++; // Skip the opening quote
    while (position < source.length() && source[position] != '"') {
        value += source[position++];
    }
    if (position < source.length()) {
        position++; // Skip the closing quote
    }
    return {STRING, value};
}

// Get the next comment token
Token Lexer::getCommentToken() {
    std::string value;
    position += 2; // Skip the '//'
    while (position < source.length() && source[position] != '\n') {
        value += source[position++];
    }
    return {COMMENT, value};
}

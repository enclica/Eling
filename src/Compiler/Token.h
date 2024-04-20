#pragma once
#include <string>

// Enumeration for different types of tokens recognized in the ELING language.
enum TokenType {
    KEYWORD,        // Reserved words with specific meaning in ELING.
    IDENTIFIER,     // User-defined names for variables, functions, etc.
    NUMBER,         // Numeric literals, both integers and floating point.
    STRING,         // Text literals enclosed in quotes.
    OPERATOR,       // Arithmetic, logical, or other operators.
    BOOLEAN,        // Boolean literals: true, false.
    COMMENT,        // Comments in the code.
    FUNCTION,       // Represents 'Operation' in ELING, a function definition.
    CONDITIONAL,    // Handles 'Condition', used for conditional logic like if-statements.
    LOOP,           // For looping constructs such as 'while', 'for'.
    END,            // Marker for end of file or end of input.
    ERROR           // For unrecognized tokens or errors in scanning.
};

// Struct to represent a single token in the ELING language.
struct Token {
    TokenType type;   // Type of the token.
    std::string value; // The value or content of the token.
};

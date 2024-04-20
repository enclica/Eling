#pragma once
#include "Lexer.h"
#include <string>
#include <sstream>  // Include for std::ostringstream

class Parser {
public:
    Parser(Lexer& lexer);
    void parse();  // Outputs generated C++ code to standard output
    std::string parseToCpp();  // Generates C++ code based on ELING syntax

private:
    Lexer& lexer;
    Token currentToken;
    void handleKeyword(std::ostringstream& cppCodeStream);  // Handles ELING keywords
    void handleVariable(std::ostringstream& cppCodeStream);  // Handles ELING variable declarations
    void handleInclude(std::ostringstream& cppCodeStream);  // Handles ELING include directives
    void handleInit(std::ostringstream& cppCodeStream);  // Handles ELING initialization statements
    
};

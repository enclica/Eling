#include "Parser.h"
#include <iostream>
#include <sstream>

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.getNextToken()) {}

void Parser::parse() {
    std::string cppCode = parseToCpp();
    std::cout << cppCode;  // Output the generated C++ code
}

std::string Parser::parseToCpp() {
    std::ostringstream cppCodeStream;
    while (currentToken.type != END) {
        switch (currentToken.type) {
            case IDENTIFIER:
                cppCodeStream << "std::cout << \"" << currentToken.value << "\";";
                break;
            case KEYWORD:
                if (currentToken.value == "printl") {
                    cppCodeStream << "std::cout << std::endl;";
                } else if (currentToken.value == "print") {
                    // Next token expected to be the content to print
                    currentToken = lexer.getNextToken();
                    cppCodeStream << "std::cout << " << currentToken.value << ";";
                } else if (currentToken.value == "var") {
                    // Handle variable declaration
                    currentToken = lexer.getNextToken(); // Variable name
                    std::string varName = currentToken.value;
                    cppCodeStream << "auto " << varName << " = "; // Use 'auto' for type inference
                    currentToken = lexer.getNextToken(); // Assuming next token is the initial value
                    cppCodeStream << currentToken.value << ";";
                }
                break;
            default:
                cppCodeStream << "// Token type not handled: " << currentToken.value << std::endl;
        }
        currentToken = lexer.getNextToken();
    }
    return cppCodeStream.str();
}

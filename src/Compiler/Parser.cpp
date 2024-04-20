#include "Parser.h"
#include <iostream>
#include <sstream>
#include <algorithm>  

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
                handleKeyword(cppCodeStream);
                break;
            default:
                cppCodeStream << "// Token type not handled: " << currentToken.value << std::endl;
        }
        currentToken = lexer.getNextToken();
    }
    return cppCodeStream.str();
}

void Parser::handleKeyword(std::ostringstream& cppCodeStream) {
    if (currentToken.value == "Operation") {
        cppCodeStream << "void "; // Assuming the next tokens handle function naming and parameters
    } else if (currentToken.value == "Condition") {
        cppCodeStream << "if "; // Assuming similar handling for conditions
    } else if (currentToken.value == "printl") {
        cppCodeStream << "std::cout << std::endl;";
    } else if (currentToken.value == "print") {
        currentToken = lexer.getNextToken();
        cppCodeStream << "std::cout << " << currentToken.value << ";";
    } else if (currentToken.value == "var") {
        handleVariable(cppCodeStream);
    } else if (currentToken.value == "Include") {
        handleInclude(cppCodeStream);
    } else if (currentToken.value == "init") {
        handleInit(cppCodeStream);
    }
}

void Parser::handleVariable(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken(); // Variable name, expecting it starts with '$'
    std::string varName = currentToken.value.substr(1); // Remove the '$' from the variable name
    cppCodeStream << "auto " << varName << " = "; // Use 'auto' for type inference
    currentToken = lexer.getNextToken(); // Assuming next token is the initial value
    cppCodeStream << currentToken.value << ";";
}

void Parser::handleInclude(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();  // Get the library path
    std::string includePath = currentToken.value;  // This will have the path with dots


    size_t pos = includePath.rfind('.');  // Find the last dot
    if (pos != std::string::npos) {
        includePath.replace(pos, 1, ".h");  // Replace the last dot with ".h"
        std::replace(includePath.begin(), includePath.begin() + pos, '.', '/');  // Replace other dots with slashes
    }
    
    cppCodeStream << "#include \"" << includePath << "\"\n";
}

void Parser::handleInit(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken(); 
    std::string varType = currentToken.value; 
    currentToken = lexer.getNextToken();
    std::string varName = currentToken.value;
    cppCodeStream << varType << " " << varName << ";\n";
}

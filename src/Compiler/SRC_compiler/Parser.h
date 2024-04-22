
#pragma once

#include "Lexer.h"
#include <string>
#include <sstream>

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.getNextToken()) {}
    void parse();
    std::string parseToCpp();

private:
    Lexer& lexer;
    Token currentToken;

    void handleKeyword(std::ostringstream& cppCodeStream);
    void handleVariable(std::ostringstream& cppCodeStream);
    void handleInclude(std::ostringstream& cppCodeStream);
    void handleInit(std::ostringstream& cppCodeStream);
    void handlePrint(std::ostringstream& cppCodeStream);
    void handleOperation(std::ostringstream& cppCodeStream);
    void handleIf(std::ostringstream& cppCodeStream);
    void handleElse(std::ostringstream& cppCodeStream);
    void handleWhile(std::ostringstream& cppCodeStream);
    void handleReturn(std::ostringstream& cppCodeStream);
    void handleFunction(std::ostringstream& cppCodeStream);
    void handleClass(std::ostringstream& cppCodeStream);
    void handleComment(std::ostringstream& cppCodeStream);
    void handleEnd(std::ostringstream& cppCodeStream);
    void handleIdentifier(std::ostringstream& cppCodeStream);
    void handleString(std::ostringstream& cppCodeStream);
};

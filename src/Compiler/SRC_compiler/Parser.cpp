#include "Parser.h"
#include <algorithm>
#include <sstream>
#include <iostream>

void Parser::parse() {
    std::string cppCode = parseToCpp();
    std::cout << cppCode;  
}

std::string Parser::parseToCpp() {
    std::ostringstream cppCodeStream;
    while (currentToken.type != END) {
        //output token type and value
        if(currentToken.type == ERROR) {
            throw std::runtime_error("Invalid token: " + currentToken.value);

            return "";
        }
        switch (currentToken.type) {
            case KEYWORD:
                handleKeyword(cppCodeStream);
                break;
            case VARIABLE:
                handleVariable(cppCodeStream);
                break;
            case INCLUDE:
                handleInclude(cppCodeStream);
                break;
            case INIT:
                handleInit(cppCodeStream);
                break;
            case PRINT:
                handlePrint(cppCodeStream);
                break;
            case OPERATION:
                handleOperation(cppCodeStream);
                break;
            case IF:
                handleIf(cppCodeStream);
                break;
            case ELSE:
                handleElse(cppCodeStream);
                break;
            case WHILE:
                handleWhile(cppCodeStream);
                break;
            case RETURN:
                handleReturn(cppCodeStream);
                break;
            case FUNCTION:
                handleFunction(cppCodeStream);
                break;
            case CLASS:
                handleClass(cppCodeStream);
                break;
            case COMMENT:
                handleComment(cppCodeStream);
                break;
            case END:
                handleEnd(cppCodeStream);
                break;
            case IDENTIFIER:
                handleIdentifier(cppCodeStream);
                break;
            case STRING:
                handleString(cppCodeStream);
                break;
            default:
                cppCodeStream << "// Token type not handled: " << currentToken.value << "\n";
        }
        currentToken = lexer.getNextToken();
    }
    return cppCodeStream.str();
}

void Parser::handleKeyword(std::ostringstream& cppCodeStream) {
    std::string keyword = currentToken.value;
    if (keyword == "explicit") {
        // Handle explicit keyword
    } else if (keyword == "class") {
        cppCodeStream << "class ";
    } else if (keyword == "Operation") {
        cppCodeStream << "void ";
    } else if (keyword == "print") {
        handlePrint(cppCodeStream);
    } else if (keyword == "Main") {
        cppCodeStream << "int main() {\n";
    } else if (keyword == "Condition") {
        handleIf(cppCodeStream);
    } else if (keyword == "Eling") {
        cppCodeStream << "// Starting an Eling program\n";
    } else if (keyword == "redo") {
        cppCodeStream << "// Redoing code\n";
    } else {
        cppCodeStream << keyword << ";\n";
    }
}

void Parser::handleVariable(std::ostringstream& cppCodeStream) {
    cppCodeStream << currentToken.value << ";\n";
}

void Parser::handleInclude(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    std::string includeType = currentToken.value;
    currentToken = lexer.getNextToken();
    std::string includePath = currentToken.value;

    std::replace(includePath.begin(), includePath.end(), '.', '/');
    size_t lastDotIndex = includePath.find_last_of('/');
    std::string fileName = includePath.substr(lastDotIndex + 1);
    std::string filePath = includePath.substr(0, lastDotIndex);

    if (includeType == "includec") {
        cppCodeStream << "#include \"" << filePath << "/" << fileName << "\"\n";
    } else if (includeType == "include") {
        cppCodeStream << "#include <" << filePath << "/" << fileName << ">\n";
    } else {
        cppCodeStream << "// Unknown include type: " << includeType << "\n";
    }
}

void Parser::handleInit(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    std::string type = currentToken.value;
    currentToken = lexer.getNextToken();
    std::string name = currentToken.value;
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    std::string value = currentToken.value;
    cppCodeStream << type << " " << name << " = " << value << ";\n";
}

void Parser::handlePrint(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    std::string message = currentToken.value;
    cppCodeStream << "std::cout << " << message << ";\n";
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
}

void Parser::handleOperation(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    std::string returnType = currentToken.value;
    currentToken = lexer.getNextToken();
    std::string name = currentToken.value;
    cppCodeStream << returnType << " " << name << "() {\n";
    currentToken = lexer.getNextToken();
}

void Parser::handleIf(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    std::string condition = currentToken.value;
    cppCodeStream << "if (" << condition << ") {\n";
    currentToken = lexer.getNextToken();
    cppCodeStream << "{\n";
}

void Parser::handleElse(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    cppCodeStream << "} else ";
    currentToken = lexer.getNextToken();
    cppCodeStream << "{\n";
}

void Parser::handleWhile(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    std::string condition = currentToken.value;
    cppCodeStream << "while (" << condition << ") {\n";
    currentToken = lexer.getNextToken();
    cppCodeStream << "{\n";
}

void Parser::handleReturn(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    currentToken = lexer.getNextToken();
    std::string value = currentToken.value;
    cppCodeStream << "return " << value << ";\n";
    currentToken = lexer.getNextToken();
}

void Parser::handleFunction(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    std::string returnType = currentToken.value;
    currentToken = lexer.getNextToken();
    std::string name = currentToken.value;
    cppCodeStream << returnType << " " << name << "() {\n";
    currentToken = lexer.getNextToken();
    cppCodeStream << "{\n";
}

void Parser::handleClass(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
    std::string name = currentToken.value;
    cppCodeStream << "class " << name << " {\n";
    currentToken = lexer.getNextToken();
    cppCodeStream << "{\n";
}

void Parser::handleComment(std::ostringstream& cppCodeStream) {
    currentToken = lexer.getNextToken();
}

void Parser::handleEnd(std::ostringstream& cppCodeStream) {
    cppCodeStream << "}\n";
}

void Parser::handleIdentifier(std::ostringstream& cppCodeStream) {
    cppCodeStream << currentToken.value;
}

void Parser::handleString(std::ostringstream& cppCodeStream) {
    cppCodeStream << "\"" << currentToken.value << "\"";
}

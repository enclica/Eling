#include "include/Lexer.h"
#include "include/Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file("Main.eling");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    Lexer lexer(input);
    Parser parser(lexer);
    std::string output = parser.parse();
    std::cout << "Translated C++ Output:\n" << output << std::endl;
    return 0;
}

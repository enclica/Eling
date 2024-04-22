#pragma once

#include "Lexer.h"
#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class ELingCompiler {
public:
    ELingCompiler(const std::string& input, const std::string& output) : inputFile(input), outputFile(output) {}

    void translateToCpp() {
        std::ifstream elingFile(inputFile);
        if (!elingFile.is_open()) {
            std::cerr << "[ERROR] Unable to open ELing file: " << inputFile << std::endl;
            return;
        }

        std::ofstream cppFile(outputFile); // Output C++ file
        if (!cppFile.is_open()) {
            std::cerr << "[ERROR] Unable to create C++ output file: " << outputFile << std::endl;
            elingFile.close();
            return;
        }

        std::cout << "Translating ELing code to C++..." << std::endl;
        std::string line;
        int lineNumber = 0;

        try {
            while (getline(elingFile, line)) {
                lineNumber++;
                Lexer lexer(line);
                Parser parser(lexer);
                std::string cppCode = parser.parseToCpp();
                cppFile << cppCode << std::endl;
                std::cout << "Line " << lineNumber << " translated." << std::endl;
            }
            std::cout << "Translation completed." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Error processing line " << lineNumber << ": " << e.what() << std::endl;
        }

        elingFile.close();
        cppFile.close();
    }

    void compileToBinary() {
        std::string command = "g++ -std=c++11 -o " + outputFile + ".out " + outputFile; // Compile the C++ file to binary
        std::cout << "Compiling C++ code to binary..." << std::endl;
        int result = system(command.c_str());
        if (result == 0) {
            std::cout << "Compilation completed." << std::endl;
        } else {
            std::cerr << "Failed to compile C++ code to binary." << std::endl;
        }
    }

private:
    std::string inputFile, outputFile;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return 1;
    }

    ELingCompiler compiler(argv[1], argv[2]);
    compiler.translateToCpp();
    compiler.compileToBinary();

    return 0;
}

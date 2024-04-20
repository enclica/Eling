#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>

class Compiler {
public:
    Compiler(const std::string& input, const std::string& output) : inputFile(input), outputFile(output) {}

    void generateConfigFile() {
        std::ofstream configFile("config.elc");
        if (configFile.is_open()) {
            configFile << "CC=g++ -o $output $input\n";
            configFile << "PLAT=linux\n";
            configFile.close();
        } else {
            std::cerr << "Failed to create config file." << std::endl;
        }
    }

    std::string getCompilerCommand(std::string inputcfile, std::string outputcfile) {
        std::ifstream configFile("config.elc");
        std::string line, compilerCommand;
        if (!configFile.is_open()) {
            std::cerr << "Config file not found, generating default config." << std::endl;
            generateConfigFile();
            configFile.open("config.elc");
        }
        while (getline(configFile, line)) {
            std::stringstream ss(line);
            std::string key, value;
            if (std::getline(ss, key, '=') && std::getline(ss, value)) {
                if (key == "CC") {
                    compilerCommand = value;
                    replacePlaceholder(compilerCommand, "$input", inputFile);
                    replacePlaceholder(compilerCommand, "$output", outputFile);
                }
            }
        }
        configFile.close();
        return compilerCommand;
    }

    void compileFile() {
        std::ifstream file(inputFile);
        std::ofstream out(outputFile);
        std::string line;
        int lineNumber = 0;

        if (file.is_open() && out.is_open()) {
            try {
                while (getline(file, line)) {
                    lineNumber++;
                    Lexer lexer(line);
                    Parser parser(lexer);
                    std::string cppCode = parser.parseToCpp();
                    out << cppCode << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Error processing line " << lineNumber << ": " << e.what() << std::endl;
            }
            file.close();
            out.close();
        } else {
            std::cerr << "[ERROR] Error opening files!" << std::endl;
        }
    }

    void compileToBinary(std::string inputcfile, std::string outputcfile) {
        std::string command = getCompilerCommand(inputcfile, outputcfile);
        int result = system(command.c_str());
        if (result != 0) {
            std::cerr << "Failed to compile C++ code to binary." << std::endl;
        }
    }

private:
    std::string inputFile, outputFile;

    void replacePlaceholder(std::string& str, const std::string& placeholder, const std::string& value) {
        size_t pos = str.find(placeholder);
        while (pos != std::string::npos) {
            str.replace(pos, placeholder.length(), value);
            pos = str.find(placeholder, pos + value.length());
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output Binary file>" << std::endl;
        return 1;
    }

    if (argc == 2 && (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-version") == 0 || strcmp(argv[1], "-workingdir") == 0)) {
        if (strcmp(argv[1], "-help") == 0) {
            std::cout << "Help information" << std::endl;
            // Provide help information here
        } else if (strcmp(argv[1], "-version") == 0) {
            std::cout << "Version information" << std::endl;
            // Provide version information here
        } else if (strcmp(argv[1], "-workingdir") == 0) {
            std::cout << "Working directory information" << std::endl;
            // Provide working directory information here
        }
        return 0;
    }

    Compiler compiler(argv[1], argv[1]+std::string(".cpp") );
    compiler.compileFile();
    compiler.compileToBinary(argv[1]+std::string(".cpp"), argv[2]);

    return 0;
}

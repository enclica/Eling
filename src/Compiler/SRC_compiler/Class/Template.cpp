

#include "Template.h"
#include <fstream> // Add the necessary include directive for std::ofstream


void Elingtemplate::createTemplate(const std::string& directory) {
   
    std::ofstream file(directory + "/Main.eling");
    if (!file.is_open()) {
        throw std::runtime_error("Unable to create Main.eling file in directory: " + directory);
    }
file << "Class Main { //Main class used to enter the application\n";
file << "    Init {  //init is the initial function with no arguments to tell the compiler where to start the application if multiple init are present it will not compile\n";
file << "       Operator Main(){ //Operators are the eling equiliant of Functions in C++\n";
file << "           Print(\"Hello, World!\"); //Prints \"Hello, World!\" to the console, similar to cout in C++ but with less code\n";
file << "       }\n";
file << "    }\n";
file << "}\n";
 
    // Close the file
    file.close();
}
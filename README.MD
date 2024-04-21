![](/assets/image-resources/Eling.png)

# Eling. 
eling is a language that is made to be simple but powerful with the ability to be used crossplatform or nor.

## How do i use eling.
Eling doesnt follow normal standards and some names are different from traditional languages.
Example 'function' is now 'Operation' and 'if' is now 'Condition'.
But with 'if' you can use 'if' and 'switch' is the same.

## How do i compile ELING's compiler
You can build eling with the make file under src/Compiler where you can fo

`make` to make the compiler and for cleaning the files you go `make clean`


### How do start using eling.

To start you need a Main file for example Main.eling is what all compilers look for at first and you can use Main to refrence other eling files and they can refrence more and if a file is not being used at all the compiler ignores it and puts out a warning saying that it is not in use.

# Usage syntax
./compiler <input_file.eling> <output_file_binary>

# Example command
./compiler example.eling example.cpp

### Config file

Eling has a config for each project which has refrences and packages and other things that are needed to run the project.

you need to the the config.elconf file which is the eling config file for projects many projects using default libs will be blank meaning no config needed but compiling will create a secondary config which is used for publishing.
The publishing file is the comp.elconf file which is the compiler config file.

## Compiler flags

# examples
We have a few examples in the eling examples folder.

# packages

packages in ELING is handled by Baton in a folder called the Baton_libs which handles both c++ and eling libraries which allows for flexibility but also makes it harder to debug if something goes wrong


# ELING TOOK ALL MY RAM

did you modify the eling compiler, expect it, did you not, sorry reprt a issue an we will look into it.

# ELING OUTPUTTED THIS

Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :
Token type: 15, value: :

your eling program is written wrong, if its an example, then its outdated and again report as an issue.

[](/assets/image-rescources/Eling.png)

# Eling. (NO COMPILER IN SRC THIS IS AN EARLY A BASE)
eling is a language that is made to be simple but powerful with the ability to be used crossplatform or nor.

## How do i use eling.
Eling doesnt follow normal standards and some names are different from traditional languages.
Example 'function' is now 'Operation' and 'if' is now 'Condition'.
But with 'if' you can use 'if' and 'switch' is the same.

### How do start using eling.

To start you need a Main file for example Main.eling is what all compilers look for at first and you can use Main to refrence other eling files and they can refrence more and if a file is not being used at all the compiler ignores it and puts out a warning saying that it is not in use.

### Config file

Eling has a config for each project which has refrences and packages and other things that are needed to run the project.

you need to the the config.elconf file which is the eling config file for projects many projects using default libs will be blank meaning no config needed but compiling will create a secondary config which is used for publishing.
The publishing file is the comp.elconf file which is the compiler config file.

## Compiler flags

all console commands look like this

-ca | compile all files (compiles all files even ones that would be ignored)
-c | compile
-d | debug
-e | execute
-i | info
-l | list
-p | print
-r | run
-s | save
-t | test
-v | version
-w | warning
-e | errors

you can combine flags to get different results from the compiler.
`[required field] (optional) . means all files in current directory`
`eling [platform(s)] [flags] (config) [file/folder]`
`eling uni -ca .`


# examples
We have a few examples in the eling examples folder with more being added daily.
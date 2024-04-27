#!/bin/bash

# Define directories
SRC_DIR="./"
OBJ_DIR="./obj"
BIN_DIR="./bin"
INCLUDE_DIR="./include"

# Create obj and bin directories if they do not exist
mkdir -p ${OBJ_DIR}
mkdir -p ${BIN_DIR}

# Compiler flags
CXX="g++"
CXXFLAGS="-Wall -I${INCLUDE_DIR}"

# Clean previous object files and binary
echo "Cleaning..."
rm -f ${OBJ_DIR}/*.o
rm -f ${BIN_DIR}/myProgram

# Compile each source file
echo "Compiling..."
for src_file in ${SRC_DIR}/*.cpp; do
    obj_file="${OBJ_DIR}/$(basename ${src_file%.*}).o"
    echo "Building $obj_file from $src_file"
    ${CXX} ${CXXFLAGS} -c $src_file -o $obj_file
done

# Link all object files to a binary
echo "Linking..."
${CXX} ${OBJ_DIR}/*.o -o ${BIN_DIR}/myProgram
echo "Build complete!"


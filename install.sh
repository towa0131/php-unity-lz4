#!/bin/bash

FLAG="CXXFLAGS=-std=gnu++11"

# Generate configure
phpize

# Generate Makefile
./configure $FLAG

# make and copy .so file to the extension directory
make install

# delete some files
make clean

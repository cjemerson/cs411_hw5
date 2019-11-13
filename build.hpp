// build.hpp
// Charles Emerson
// Created: 21 September 2019
// Updated: 13 November 2019
//
// For CS 411 Fall 2019
// Header for function build
// Solution to Assignment 5, Exercise A
//
// This is a fork from my solution for Assignment 2, Exercise A
// https://github.com/cjemerson/cs411_hw5/


#ifndef FILE_BUILD_H_INCLUDED
#define FILE_BUILD_H_INCLUDED

#include <vector> // For std::vector
#include <algorithm> // For std::sort, std::remove_if
#include <tuple> // For std::forward_as_tuple

// Wrapper function
// Calls build_recurse RECURSIVE
// (See definition for documentation)
int build(int w, int e, std::vector<std::vector<int>> bridges);

#endif // #ifndef FILE_BUILD_H_INCLUDED

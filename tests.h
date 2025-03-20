//
// Created by Emily on 2025-03-20.
//

#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <string>
#include <functional> // For std::function

template <typename T>
class Tests {
public:
    Tests(const std::string& suiteName);

    void runTest(const std::string& testName, const T& expected, const T& actual);

    void printResults() const;

private:
    std::string suiteName_;
    int passed_;
    int failed_;
};

#endif // TESTS_H
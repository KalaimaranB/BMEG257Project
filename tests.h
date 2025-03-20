//
// Created by Emily on 2025-03-20.
//

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

template <typename T>
class tests {
public:
    tests(const std::string& suiteName) : suiteName_(suiteName), passed_(0), failed_(0) {}

    void runTest(const std::string& testName, const T& expected, const T& actual) {
        std::cout << "Test: " << testName << "... ";
        if (expected == actual) {
            std::cout << "Passed" << std::endl;
            passed_++;
        } else {
            std::cout << "Failed" << std::endl;
            std::cout << "  Expected: " << expected << std::endl;
            std::cout << "  Actual:   " << actual << std::endl;
            failed_++;
        }
    }
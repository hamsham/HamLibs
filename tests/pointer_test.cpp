/* 
 * File:   pointer_test.cpp
 * Author: miles
 *
 * Created on Apr 19, 2014, 5:53:00 PM
 */

#include <iostream>
#include <memory>

#include "../include/hamLibs.h"

/*
 * Simple test of the pointer class
 */
using hamLibs::utils::pointer;

int main() {
    pointer<int> pInts{5};
    std::unique_ptr<int> pOthers{new int[5]};
    
    pInts[0] = 1;
    pInts[1] = 2;
    pInts[2] = 3;
    pInts[3] = 4;
    pInts[4] = 5;
    
    std::cout << "Created an integer array of " << pInts.size() << ".\n";
    std::cout << "sizeof pointer<int>: " << sizeof(pInts) << '\n';
    std::cout << "sizeof std::unique_ptr<int>: " << sizeof(pOthers) << '\n';
    
    for (unsigned i = 0; i < pInts.size(); ++i) {
        std::cout << pInts[i] << std::endl;
    }
    
    return 0;
}


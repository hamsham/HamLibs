
// binary tree tests
// g++ -std=c++11 -Wall -Wextra -pedantic -pedantic-errors -pthread -g -O0 btree.cpp -o btree

#include <iostream>
#include <map>
#include <chrono>
#include <limits>
#include <thread>

#include "containers/btree.h"

#define NUM_ITERATIONS 4096
#define NUM_TESTS 4096

const char* loremIpsum = R"***(Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis bibendum purus vel libero scelerisque, eu tincidunt nibh semper. Mauris nibh lectus, ullamcorper et posuere id, congue at mauris. Nunc tempor elit dolor, vel placerat dolor mattis nec. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur tellus diam, sollicitudin a felis vitae, mollis congue mi. Ut in euismod dolor. Mauris placerat egestas tortor quis iaculis. Pellentesque et felis tortor. Mauris massa metus, pellentesque eu orci vulputate, dignissim imperdiet dolor.
Donec bibendum felis quis tellus condimentum, id laoreet orci tempor. Quisque non fermentum risus. Praesent at orci quis felis volutpat condimentum. Morbi sapien dolor, dapibus quis consectetur sit amet, gravida vel orci. Duis nulla mi, placerat vel convallis quis, vestibulum ac nunc. Duis ac sollicitudin purus. Phasellus ullamcorper erat at ante congue ullamcorper at in mauris. Suspendisse quis metus placerat, condimentum sapien eget, elementum justo. Vestibulum tincidunt tempus nisl, at sodales mi varius nec. Donec quis est laoreet, placerat orci eget, tincidunt erat. Nullam pretium gravida neque eget porttitor. In hac habitasse platea dictumst. Integer semper sit amet felis eu feugiat.
Curabitur lobortis, sem at cursus cursus, felis lacus venenatis sapien, euismod pharetra diam dolor sed dolor. Donec dignissim, augue ac ultrices aliquam, metus diam semper ante, id venenatis purus lectus at diam. Nulla a posuere nunc, non aliquet libero. Quisque magna nisi, pulvinar a facilisis pharetra, suscipit sed nisi. Ut porttitor lorem eu eros scelerisque rutrum. Sed iaculis sapien eu elit rutrum venenatis. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.)***";

namespace chrono = std::chrono;

typedef chrono::steady_clock::time_point hr_time;
typedef chrono::milliseconds hr_prec;

void nativeBench() {
    std::cout.sync_with_stdio( false );
    std::cout << "Running Native benchmark." << std::endl;
    
    std::map< int, int > testTree;
    hr_time t1, t2;
    unsigned numRuns = 0;
    t1 = chrono::steady_clock::now();
    
    while ( numRuns < NUM_ITERATIONS ) {
        for ( int i = 0; i < NUM_TESTS; ++i ) {
            testTree[ i ] = i + numRuns;
        }
        ++numRuns;
    }
    
    t2 = chrono::steady_clock::now();
    std::cout.precision( std::numeric_limits<double>::digits10 );
    std::cout
        << "STL Map operation " << numRuns
            << ":\t" << chrono::duration_cast< hr_prec >( t2 - t1 ).count() / 1000.0
            << '\t' << testTree.size() << "\n\n";
}


void bTreeBench() {
    std::cout.sync_with_stdio( false );
    std::cout << "Running bTree benchmark." << std::endl;
    
    hamLibs::containers::bTree< int, int > testTree;
    hr_time t1, t2;
    unsigned numRuns = 0;
    t1 = chrono::steady_clock::now();
    
    while ( numRuns < NUM_ITERATIONS ) {
        for ( int i = 0; i < NUM_TESTS; ++i ) {
            testTree[ i ] = i + numRuns;
        }
        ++numRuns;
    }
    
    t2 = chrono::steady_clock::now();
    std::cout.precision( std::numeric_limits<double>::digits10 );
    std::cout
        << "bTree operation " << numRuns
            << ":\t" << chrono::duration_cast< hr_prec >( t2 - t1 ).count() / 1000.0
            << '\t' << testTree.size() << "\n\n";
}

int main() {
    
    // Benchmarks
    nativeBench();
    bTreeBench();
    
    hamLibs::containers::bTree< const char*, int > strTree;
    strTree[ "Hello World!" ] = 0;
    strTree[ "Supercalifragilisticexpialidocious!" ] = 1;
    strTree[ "One, Two, Three" ] = 2;
    //strTree[ loremIpsum ] = 3;
    
    std::cout << strTree["Hello World!"] << "\n";
    std::cout << strTree["Supercalifragilisticexpialidocious!"] << "\n";
    std::cout << strTree["One, Two, Three"] << "\n";
    //std::cout << strTree[loremIpsum];
    
    return 0;
}


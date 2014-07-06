
// binary tree tests
// g++ -std=c++11 -Wall -Wextra -pedantic -pedantic-errors -pthread -g -O0 btree.cpp -o btree

#include <iostream>
#include <map>
#include <chrono>
#include <limits>
#include <utility>

#include "containers/btree.h"

#define NUM_ITERATIONS 4096
#define NUM_TESTS 4096

const char* testKey1 = "Hello World!";
const char* testKey2 = "Supercalifragilisticexpialidocious!";
const char* testKey3 = "One, Two, Three";
const char* loremIpsum = R"***(Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis bibendum purus vel libero scelerisque, eu tincidunt nibh semper. Mauris nibh lectus, ullamcorper et posuere id, congue at mauris. Nunc tempor elit dolor, vel placerat dolor mattis nec. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur tellus diam, sollicitudin a felis vitae, mollis congue mi. Ut in euismod dolor. Mauris placerat egestas tortor quis iaculis. Pellentesque et felis tortor. Mauris massa metus, pellentesque eu orci vulputate, dignissim imperdiet dolor.
Donec bibendum felis quis tellus condimentum, id laoreet orci tempor. Quisque non fermentum risus. Praesent at orci quis felis volutpat condimentum. Morbi sapien dolor, dapibus quis consectetur sit amet, gravida vel orci. Duis nulla mi, placerat vel convallis quis, vestibulum ac nunc. Duis ac sollicitudin purus. Phasellus ullamcorper erat at ante congue ullamcorper at in mauris. Suspendisse quis metus placerat, condimentum sapien eget, elementum justo. Vestibulum tincidunt tempus nisl, at sodales mi varius nec. Donec quis est laoreet, placerat orci eget, tincidunt erat. Nullam pretium gravida neque eget porttitor. In hac habitasse platea dictumst. Integer semper sit amet felis eu feugiat.
Curabitur lobortis, sem at cursus cursus, felis lacus venenatis sapien, euismod pharetra diam dolor sed dolor. Donec dignissim, augue ac ultrices aliquam, metus diam semper ante, id venenatis purus lectus at diam. Nulla a posuere nunc, non aliquet libero. Quisque magna nisi, pulvinar a facilisis pharetra, suscipit sed nisi. Ut porttitor lorem eu eros scelerisque rutrum. Sed iaculis sapien eu elit rutrum venenatis. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.)***";

namespace chrono = std::chrono;

typedef chrono::steady_clock hr_clock;
typedef hr_clock::time_point hr_time;
typedef chrono::milliseconds hr_prec;

/******************************************************************************
 * STL Map Benchmark
******************************************************************************/
void nativeBench() {
    std::cout.sync_with_stdio( false );
    std::cout << "Running Native benchmark." << std::endl;
    
    std::map< int, int > testTree;
    hr_time t1, t2;
    unsigned numRuns = 0;
    t1 = hr_clock::now();
    
    while ( numRuns < NUM_ITERATIONS ) {
        for ( int i = 0; i < NUM_TESTS; ++i ) {
            testTree[ i ] = i + numRuns;
        }
        ++numRuns;
    }
    
    t2 = hr_clock::now();
    std::cout.precision( std::numeric_limits<double>::digits10 );
    std::cout
        << "STL Map operation " << numRuns
            << ":\t" << chrono::duration_cast< hr_prec >( t2 - t1 ).count() / 1000.0
            << '\t' << testTree.size() << "\n\n";
}

/******************************************************************************
 * B-Tree Benchmark
******************************************************************************/
void bTreeBench() {
    std::cout.sync_with_stdio( false );
    std::cout << "Running bTree benchmark." << std::endl;
    
    hamLibs::containers::bTree< int, int > testTree;
    hr_time t1, t2;
    unsigned numRuns = 0;
    t1 = hr_clock::now();
    
    while ( numRuns < NUM_ITERATIONS ) {
        for ( int i = 0; i < NUM_TESTS; ++i ) {
            testTree[ i ] = i + numRuns;
        }
        ++numRuns;
    }
    
    t2 = hr_clock::now();
    std::cout.precision( std::numeric_limits<double>::digits10 );
    std::cout
        << "bTree operation " << numRuns
            << ":\t" << chrono::duration_cast< hr_prec >( t2 - t1 ).count() / 1000.0
            << '\t' << testTree.size() << "\n\n";
}

/******************************************************************************
 * Test Copy function to return an initialized B-Tree
******************************************************************************/
hamLibs::containers::bTree< const char*, int > getTempTree() {
    hamLibs::containers::bTree< const char*, int > tempTree;
    
    tempTree[ testKey1 ] = 0;
    tempTree[ testKey2 ] = 1;
    tempTree[ testKey3 ] = 2;
    tempTree[ loremIpsum ] = 3;
    
    return tempTree;
}

/******************************************************************************
 * B-Tree Copy Constructor Test
******************************************************************************/
void testCopyCtor() {
    std::cout << "\nTESTING COPY C-TOR" << "\n";
    
    hamLibs::containers::bTree< const char*, int > otherTree( getTempTree() );
    
    std::cout << otherTree[testKey1] << "\n";
    std::cout << otherTree[testKey2] << "\n";
    std::cout << otherTree[testKey3] << "\n";
    std::cout << otherTree[loremIpsum] << "\n";
    
    std::cout << "B-Tree Size: " << otherTree.size() << "\n";
}

/******************************************************************************
 * B-Tree Copy Operator Test
******************************************************************************/
void testCopyOp() {
    std::cout << "\nTESTING COPY OPERATOR" << "\n";
    
    hamLibs::containers::bTree< const char*, int > otherTree;
    otherTree = getTempTree();
    
    std::cout << otherTree[testKey1] << "\n";
    std::cout << otherTree[testKey2] << "\n";
    std::cout << otherTree[testKey3] << "\n";
    std::cout << otherTree[loremIpsum] << "\n";
    
    std::cout << "B-Tree Size: " << otherTree.size() << "\n";
}

/******************************************************************************
 * B-Tree Move Constructor Test
******************************************************************************/
void testMoveCtor() {
    std::cout << "\nTESTING MOVE CONSTRUCTOR" << "\n";
    
    hamLibs::containers::bTree< const char*, int > otherTree(std::move(getTempTree()));
    
    std::cout << otherTree[testKey1] << "\n";
    std::cout << otherTree[testKey2] << "\n";
    std::cout << otherTree[testKey3] << "\n";
    std::cout << otherTree[loremIpsum] << "\n";
    
    std::cout << "B-Tree Size: " << otherTree.size() << "\n";
}

/******************************************************************************
 * B-Tree Move Operator Test
******************************************************************************/
void testMoveOp() {
    std::cout << "\nTESTING MOVE OPERATOR" << "\n";
    
    hamLibs::containers::bTree< const char*, int > otherTree;
    otherTree = std::move(getTempTree());
    
    std::cout << otherTree[testKey1] << "\n";
    std::cout << otherTree[testKey2] << "\n";
    std::cout << otherTree[testKey3] << "\n";
    std::cout << otherTree[loremIpsum] << "\n";
    
    std::cout << "B-Tree Size: " << otherTree.size() << "\n";
}

/******************************************************************************
 * Main
******************************************************************************/
int main() {
    testCopyCtor();
    testCopyOp();
    testMoveCtor();
    testMoveOp();
    
    // Multi-threaded benchmarks
    nativeBench();
    bTreeBench();
}


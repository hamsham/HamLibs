/* 
 * File:   fixed_point_test.cpp
 * Author: hammy
 *
 * Created on Dec 8, 2013, 10:14:54 PM
 */

#include <iostream>
#include <limits>
#include "math/math.h"

using namespace hamLibs::math;

int main() {
    float       testNum     = 492.2f * 539.1f;
    ulowp_t     fixed_t1    = testNum;
    umedp_t     fixed_t2    = testNum / 100.f;
    uhighp_t    fixed_t3    = testNum / 10000.f;
    
    std::cout.precision( std::numeric_limits< float >::digits10 );
    std::cout << std::fixed
        << testNum << '\n'
        << fixed_t1 << '\n'
        << fixed_t2 << '\n'
        << fixed_t3 << std::endl;
    
    return 0;
}


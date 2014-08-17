
#include <chrono>

#include "../include/utils/randomNum.h"
#include "../include/utils/assert.h"

constexpr unsigned long getMaxULong() { return 0UL - 1; }

namespace hamLibs {
namespace utils {

/*
 * Seeded Constructor
 */
randomNum::randomNum(unsigned long s) {
    this->seed(s);
}

/*
 * Default Constructor
 */
randomNum::randomNum() {
    this->seed();
}

/*
 * Copy Constructor
 */
randomNum::randomNum(const randomNum& rn) :
    index{rn.index}
{
    for (unsigned i = 0; i < 16; ++i) {
        state[i] = rn.state[i];
    }
}

/*
 * Move Constructor
 */
randomNum::randomNum(randomNum&& rn) :
    index{rn.index}
{
    for (unsigned i = 0; i < 16; ++i) {
        state[i] = rn.state[i];
    }
}

/*
 * Destructor
 */
randomNum::~randomNum() {
}

/*
 * Copy Operator
 */
randomNum& randomNum::operator=(const randomNum& rn) {
    index = rn.index;
    
    for (unsigned i = 0; i < 16; ++i) {
        state[i] = rn.state[i];
    }
    return *this;
}

/*
 * Move Operator
 */
randomNum& randomNum::operator=(randomNum&& rn) {
    index = rn.index;
    
    for (unsigned i = 0; i < 16; ++i) {
        state[i] = rn.state[i];
    }
    return *this;
}

/*
 * Initialize the random distribution
 */
void randomNum::seed(unsigned long s) {
    for (unsigned int i = 0; i < 16; ++i) {
        state[i] = s++;
        genRandNum(); // initializing the state to random bits
    }
    index = 0;
}

/*
 * Default random distribution initialization
 */
void randomNum::seed() {
    this->seed((long unsigned)std::chrono::system_clock::now().time_since_epoch().count());
}

/*
 * Generate a random number
 */
unsigned long randomNum::genRandNum() {
    unsigned long a, b, c, d;
    a = state[index];
    c = state[(index+13)&15];
    b = a^c^(a<<16)^(c<<15);
    c = state[(index+9)&15];
    c ^= (c>>11);
    a = state[index] = b^c;
    d = a^((a<<5)&0xDA442D24UL);
    index = (index + 15)&15;
    a = state[index];
    state[index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
    return state[index];
}

/*
 * Generate a random float within a an inclusive range
 */
float randomNum::randRangeF(float low, float high) {
    HL_DEBUG_ASSERT(low < high);
    return low + ((float)genRandNum() / ((float)getMaxULong() / (high-low)));
}

/*
 * Generate a random int within an inclusive range.
 */
int randomNum::randRangeI(int low, int high) {
    HL_DEBUG_ASSERT(low < high);
    return static_cast<int>(randRangeF(
        static_cast<float>(low),
        static_cast<float>(high)
   ));
}

} // end utils namespace
} // end hamlibs namespace
        
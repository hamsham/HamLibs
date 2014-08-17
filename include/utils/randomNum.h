
// randomness using the WELLRNC 512 algorithm
// This method was taken from:
// http://www.lomont.org/Math/Papers/Papers.php
// (see: Random Number Generation)
// http://www.lomont.org/Math/Papers/2008/Lomont_PRNG_2008.pdf

#ifndef __HL_RANDON_H__
#define __HL_RANDON_H__

namespace hamLibs {
namespace utils {

class randomNum {
    private:
        unsigned long state[16] = {0};
        unsigned int index = 0;
        
    public:
        randomNum(unsigned long s);
        randomNum();
        randomNum(const randomNum&);
        randomNum(randomNum&&);
        
        ~randomNum();
        
        randomNum& operator=(const randomNum&);
        randomNum& operator=(randomNum&&);
        
        // seeding is not necessary, but may help in case initial
        // random numbers appear with poor distribution
        void seed(unsigned long s);
        void seed();
        
        // Returns a 32-bit random number
        unsigned long genRandNum();
        
        float randRangeF(float low, float high);
        int randRangeI(int low, int high);
};
        
} // end utils namespace
} // end hamLibs namespace

#endif /* __HL_RANDON_H__ */
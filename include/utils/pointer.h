/* 
 * File:   pointer.h
 * Author: miles
 *
 * Created on April 19, 2014, 2:54 PM
 */

#ifndef __HL_POINTER_H__
#define	__HL_POINTER_H__

#include <new>

#include "../defs/preprocessor.h"

namespace hamLibs {
namespace utils {

/**
 * Pointer Class
 * 
 * This class was meant to have a similar functionality to std::unique_ptr.
 * It can be used to automatically allocate an array of memory and destroy it
 * without having to worry about the hassle of calling 'new' or delete'. After
 * looking at the implementation of std::unique_ptr from g++, I made this class
 * in order to better suit my needs in other projects.
 */
template <typename data_t>
class pointer {
    private:
        data_t* pData = nullptr;
        unsigned count = 0;
        
    public:
        /**
         *  Constructor
         *  Dynamically create an array of 'numElements'.
         *  
         *  If the memory allocation fails, the array will contain no elements
         *  and the 'count' member will be set to 0.
         *  
         *  No exceptions will be thrown by this method.
         *  
         *  @param numElements
         *  Determines the number of items in the array.
         */
        pointer(unsigned numElements) :
            pData{new(std::nothrow) data_t[numElements]},
            count{pData != nullptr ? numElements : 0}
        {}
        
        /**
         *  Constructor
         *  Initializes 'pData' to NULL and 'count' to 0.
         *  
         *  If the memory allocation fails, the array will contain no elements
         *  and the 'count' member will be set to 0.
         *  
         *  No exceptions will be thrown by this method.
         */
        constexpr pointer() {}
        
        /**
         *  Copy Constructor
         *  Dynamically create an array of 'data_t' elements and copy the data
         *  contained within another pointer. This method only performs a
         *  shallow copy and will not perform any other allocation besides
         *  what's required to construct 'pData'.
         *  
         *  If the memory allocation fails, the array will contain no elements
         *  and the 'count' member will be set to 0.
         *  
         *  No exceptions will be thrown by this method.
         *  
         *  @param numElements
         *  Determines the number of items in the array.
         */
        pointer(const pointer& p) :
            pData{new(std::nothrow) data_t[p.count]},
            count{pData != nullptr ? p.count : 0}
        {
            // Only loops if pData had successfully allocated memory.
            for (unsigned i = 0; i < count; ++i) {
                pData[i] = p.pData[i];
            }
        }
        
        /**
         *  Move Constructor
         *  This method moves the data from the pointer object passed in,
         *  avoiding any allocation or reallocation operations.
         *  
         *  No exceptions will be thrown by this method.
         *  
         *  @param numElements
         *  Determines the number of items in the array.
         */
        pointer(pointer&& p) :
            pData{p.pData},
            count{p.count}
        {
            p.pData = nullptr;
            p.count = 0;
        }
        
        /**
         *  Destructor
         *  Frees all memory used by *this
         */
        ~pointer() {
            delete [] pData;
            pData = nullptr;
            count = 0;
        }
        
        /**
         *  Copy Operator
         *  Dynamically copy an array of 'data_t' elements and copy the data
         *  contained within another pointer. This method only performs a
         *  shallow copy and will not perform any other allocation besides
         *  what's required to construct 'pData'.
         *  
         *  If the memory allocation fails, the array will contain no elements
         *  and the 'count' member will be set to 0.
         *  
         *  No exceptions will be thrown by this method.
         *  
         *  @param numElements
         *  Determines the number of items in the array.
         *  
         *  @return a reference to *this.
         */
        pointer& operator=(const pointer& p) {
            if (pData != nullptr) {
                delete [] pData;
            }
            
            pData = new(std::nothrow) data_t[p.count];
            count = pData != nullptr ? p.count : 0;
            
            // Only loops if pData had successfully allocated memory.
            for (unsigned i = 0; i < count; ++i) {
                pData[i] = p.pData[i];
            }
            
            return *this;
        }
        
        /**
         *  Move Operator
         *  This method moves the data from the pointer object passed in,
         *  avoiding any allocation or reallocation operations.
         *  
         *  No exceptions will be thrown by this method.
         *  
         *  @param numElements
         *  Determines the number of items in the array.
         *  
         *  @return a reference to *this.
         */
        pointer& operator=(pointer&& p) {
            if (pData != nullptr) {
                delete [] pData;
            }
            
            pData = p.pData;
            p.pData = nullptr;
            
            count = p.count;
            p.count = 0;
            
            return *this;
        }
        
        /**
         *  Casting Operator
         * 
         * Disabled due to a g++ error (ambiguous overload of operator[]).
         *  
         *  @return a raw pointer to the object contained within *this.
         */
        /*
        operator data_t*() const {
            return pData;
        }
        */
        
        /**
         *  Casting Operator
         * 
         * Disabled due to a g++ error (ambiguous overload of operator[]).
         *  
         *  @return a raw pointer to the object contained within *this.
         */
        /*
        operator data_t*() {
            return pData;
        }
        */
        
        /**
         *  Dereference operator
         *  Performs similarly to the dereference operator on a raw pointer
         *  
         *  @return a reference to the first element contained within 'pData'.
         */
        inline data_t& operator *() {
            return *pData;
        }
        
        /**
         *  Dereference operator
         *  Performs similarly to the dereference operator on a raw pointer
         *  
         *  @return a reference to the first element contained within 'pData'.
         */
        inline const data_t& operator *() const {
            return *pData;
        }
        
        /**
         *  Array subscript operator
         *  
         *  @param index
         *  An offset to specify which element in the 'pData' array should be
         *  retrieved.
         *  
         *  @return a reference to the element contained within 'pData' at the
         *  index specified by 'index'.
         */
        inline data_t& operator[] (unsigned index) {
            return pData[index];
        }
        
        /**
         *  Array subscript operator
         *  
         *  @param index
         *  An offset to specify which element in the 'pData' array should be
         *  retrieved.
         *  
         *  @return a reference to the element contained within 'pData' at the
         *  index specified by 'index'.
         */
        inline const data_t& operator[] (unsigned index) const {
            return pData[index];
        }
        
        /**
         *  Get the number of elements contained within 'pData'.
         *  
         *  @return The number of elements contained within 'pData'.
         */
        inline unsigned size() const {
            return count;
        }
};

HL_DECLARE_CLASS_TYPE(void_ptr, pointer, void*);

HL_DECLARE_CLASS_TYPE(char_ptr, pointer, char);
HL_DECLARE_CLASS_TYPE(uchar_ptr, pointer, unsigned char);

HL_DECLARE_CLASS_TYPE(short_ptr, pointer, short);
HL_DECLARE_CLASS_TYPE(ushort_ptr, pointer, unsigned short);

HL_DECLARE_CLASS_TYPE(int_ptr, pointer, int);
HL_DECLARE_CLASS_TYPE(uint_ptr, pointer, unsigned int);

HL_DECLARE_CLASS_TYPE(long_ptr, pointer, long);
HL_DECLARE_CLASS_TYPE(ulong_ptr, pointer, unsigned long);

HL_DECLARE_CLASS_TYPE(long_long_ptr, pointer, long long);
HL_DECLARE_CLASS_TYPE(ulong_long_ptr, pointer, unsigned long long);

HL_DECLARE_CLASS_TYPE(float_ptr, pointer, float);
HL_DECLARE_CLASS_TYPE(double_ptr, pointer, double);
HL_DECLARE_CLASS_TYPE(long_double_ptr, pointer, long double);

} /* end utils namespace */
} /* end hamLibs namespace */

#endif	/* __HL_POINTER_H__ */


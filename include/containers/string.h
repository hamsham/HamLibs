
#ifndef __HL_STRING_H__
#define __HL_STRING_H__

#include <climits>
#include "../utils/assert.h"

namespace hamLibs {
namespace containers {

/******************************************************************************
 * Forward Declarations and Typedefs
******************************************************************************/
template <typename charType>
class string_t;

typedef string<char>        string;
typedef string<char16_t>    string16;
typedef string<char32_t>    string32;

/******************************************************************************
 * HamLibs string class
******************************************************************************/
template <typename charType = char>
class string_t {
    enum : signed int { DEFAULT_GRANULARITY = 1024 };
    
    static inline int getStrLen( const charType* );
        
    private:
        int         numUsed     = 0;
        int         numTotal    = DEFAULT_GRANULARITY;
        int         granularity = DEFAULT_GRANULARITY;
        charType*   data        = nullptr;
        
    public:
        string_t();
        string_t( string_t&& );
        string_t( const string_t& );
        string_t( const charType );
        string_t( const charType* );
        string_t( int charCount, int totalChars, int grainSize, charType* charArray );
        ~string_t();
        
        string_t      operator +      ( const string_t& ) const;
        string_t&     operator +=     ( const string_t& );
        string_t&     operator =      ( string_t&& );
        string_t&     operator =      ( const string_t& s );
        
        string_t      operator +      ( const charType* ) const;
        string_t&     operator +=     ( const charType* );
        string_t&     operator =      ( const charType* );
        
        string_t      operator +      ( charType ) const;
        string_t&     operator +=     ( charType );
        string_t&     operator =      ( charType );
        
        charType    operator []     ( int ) const;
        charType&   operator []     ( int );
        
        // setting the reserve size takes effect on the next reallocation
        void        setReserveSize  ( int r = DEFAULT_GRANULARITY );
        int         getReserveSize  () const { return granularity; }
        
        string_t&     append          ( const string_t& s ) { return operator+=( s ); }
        string_t&     append          ( const charType* s ) { return operator+=( s ); }
        string_t&     append          ( charType c ) { return operator+=( c ); }
        
        void        pushBack        ( charType c ) { operator+=( c ); }
        
        void        clear           ();
        int         size            () const { return numUsed; }
        int         capacity        () const { return numTotal; }
        int         maxSize         () const { return INT_MAX - granularity; }
        const charType* cStr        () const { return data; }
        bool        empty           () const { return data[0] != '\0'; }
        
/* TODO */
//        void        resize          ( int newSize );
//        void        resize          ( int newSize, charType c );
        
//        void        reserve         ( int newSize );
        
//        void        shrinkToFit     ();

//        int         find            ( const string& ) const;
//        int         find            ( const charType* ) const;
//        int         find            ( charType ) const;

//        int         rFind           ( const string& ) const;
//        int         rFind           ( const charType* ) const;
//        int         rFind           ( charType ) const;

//        bool        operator ==     ( const string& ) const;
//        bool        operator !=     ( const string& ) const;
//        bool        operator >      ( const string& ) const;
//        bool        operator <      ( const string& ) const;
//        bool        operator >=     ( const string& ) const;
//        bool        operator <=     ( const string& ) const;
};

/******************************************************************************
    STRING - CON/DESTRUCTION
******************************************************************************/
/*
 *      STRING -- Getting a C-String's length
 */
template <typename charType>
inline int string_t<charType>::getStrLen( const charType* s ) {
    int i = 0;
    while ( s[ i++ ] ) {}
    return i-1;
}

/*
 *      STRING -- Destructor
 */
template <typename charType>
string_t<charType>::~string_t() {
    delete [] data;
    data = nullptr;
    numUsed = 0;
    numTotal = 0;
    granularity = DEFAULT_GRANULARITY;
}

/*
 *      STRING -- Plain Constructor
 */
template <typename charType>
string_t<charType>::string_t() {
    data = new charType[ DEFAULT_GRANULARITY + 1 ]();
}

/*
 *      STRING -- Move Constructor
 */
template <typename charType>
string_t<charType>::string_t( string_t&& s ) :
    numUsed( s.numUsed ),
    numTotal( s.numTotal ),
    granularity( s.granularity ),
    data( s.data )
{
    s.numUsed = s.numTotal = s.granularity = 0;
    s.data = nullptr;
}

/*
 *      STRING -- Copy Constructor using other strings
 */
template <typename charType>
string_t<charType>::string_t( const string_t& s ) {
    *this = s;
}

/*
 *      STRING -- Construction using a regular charType
 */
template <typename charType>
string_t<charType>::string_t( const charType c ) {
    numUsed = 1;
    numTotal = DEFAULT_GRANULARITY + 1;
    
    data = new charType[ numTotal + 1 ]();
    
    data[0] = c;
}

/*
 *      STRING -- Copy Constructor using C-Style arrays
 */
template <typename charType>
string_t<charType>::string_t( const charType* s ) {
    numUsed = getStrLen( s );
    numTotal = numUsed + DEFAULT_GRANULARITY;
    
    data = new charType[ numTotal + 1 ]();
    
    for ( int i = 0; i < numUsed; ++i )
        data[ i ] = s[ i ];
}

/*
 *      STRING -- for Brace-Initialization
 */
template <typename charType>
string_t<charType>::string_t( int charCount, int totalChars, int grainSize, charType* charArray ) :
    numUsed( charCount ),
    numTotal( totalChars ),
    granularity( grainSize ),
    data( charArray )
{}

/******************************************************************************
    STRING - STRING OPERATORS
******************************************************************************/
/*
 *      STRING -- Combining two strings using the '+' operator
 */
template <typename charType>
string_t<charType> string_t<charType>::operator + ( const string_t& s ) const {
    // determine the needed length. Use integer overflow to determine if it's too big
    if ( 0 >= (numUsed + s.numUsed + DEFAULT_GRANULARITY + 1) ) {
        return string_t();
    }
    
    int len = numUsed + s.numUsed;
    charType* temp = new charType[ len + DEFAULT_GRANULARITY + 1 ]();
    
    // populate the new array with data from this
    int i = numUsed;
    while ( i-- )
        temp[ i ] = data[ i ];
    
    // append data from "s"
    i = s.numUsed;
    while ( i-- )
        temp[ i+numUsed ] = s.data[ i ];
    
    return string_t( len, len+DEFAULT_GRANULARITY, DEFAULT_GRANULARITY, temp );
}

/*
 *      STRING -- Appending another string using the '+=' operator
 */
template <typename charType>
string_t<charType>& string_t<charType>::operator += ( const string_t& s ) {
    // determine the needed length. return a blank string if it's too big
    if ( numUsed + s.numUsed < numTotal ) {
        int i = s.numUsed;
        while ( i < s.numUsed )
            data[ numUsed++ ] = s.data[ i++ ];
    }
    else {
        *this = *this + s;
    }
    return *this;
}

/*
 *      STRING -- Assignment operator using another string
 */
template <typename charType>
string_t<charType>& string_t<charType>::operator = ( const string_t& s ) {
    
    // don't reallocate if the current string is of reasonable size
    if ( s.numUsed < granularity ) {
        int i = numTotal;
        while ( i-- )
            data[ i ] = (i < s.numUsed) ? s.data[ i ] : '\0';
    }
    else {
        delete [] data;
        data = new charType[ s.numTotal + 1 ]();

        int i = s.numUsed;
        while ( i-- )
            data[ i ] = s.data[ i ];
    }
    
    numUsed = s.numUsed;
    numTotal = s.numTotal;
    granularity = s.granularity;
    return *this;
}

/*
 *      STRING -- Move operator using another string
 */
template <typename charType>
string_t<charType>& string_t<charType>::operator = ( string_t&& s ) {
    delete [] data;
    
    numUsed = s.numUsed;
    numTotal = s.numTotal;
    granularity = s.granularity;
    data = s.data;
    
    s.numUsed = 0;
    s.numTotal = 0;
    s.granularity = 0;
    s.data = nullptr;
    
    return *this;
}

/******************************************************************************
    STRING - C-STRING OPERATORS
******************************************************************************/
/*
 *      STRING -- Combining a string and C-String string using the '+' operator
 */
template <typename charType>
string_t<charType> string_t<charType>::operator + ( const charType* s ) const {
    // determine the needed length. return a blank string if it's too big
    int len = getStrLen( s );
    
    // use integer overflow to check the string size limit
    if ( 0 >= (numUsed + len + DEFAULT_GRANULARITY + 1) ) {
        return string_t();
    }
    
    charType* temp;
    temp = new charType[ numUsed + len + DEFAULT_GRANULARITY + 1 ]();
    
    // populate the new array with data from this
    int i = numUsed;
    while ( i-- )
        temp[ i ] = data[ i ];
    
    // append data from "s"
    i = len;
    while ( i-- )
        temp[ i + numUsed ] = s[ i ];
    
    return string_t(
        numUsed+len, numUsed+len+DEFAULT_GRANULARITY,
        DEFAULT_GRANULARITY, temp
    );
}

/*
 *      STRING -- Appending C-String using the '+=' operator
 */
template <typename charType>
string_t<charType>& string_t<charType>::operator += ( const charType* s ) {
    // determine the needed length. return a blank string if it's too big
    int len = getStrLen( s );
    if ( numUsed + len < numTotal ) {
        int i = 0;
        while ( i < len )
            data[ numUsed++ ] = s[ i++ ];
    }
    else {
        *this = *this + s;
    }
    
    return *this;
}

/*
 *      STRING -- Assignment operator using a C-string
 */
template <typename charType>
string_t<charType>& string_t<charType>::operator = ( const charType* s ) {
    int len = getStrLen( s );
    
    // don't reallocate if the current string is of reasonable size
    if ( len < granularity ) {
        int i = len;
        while ( i-- )
            data[ i ] = (i < len) ? s[ i ] : '\0';
        
        numUsed = len;
    }
    else {
        delete [] data;
        data = new charType[ len + granularity + 1 ]();

        int i = len;
        while (i--)
            data[i] = s[i];
        
        numUsed = len;
        numTotal = len + granularity;
    }
    
    return *this;
}

/******************************************************************************
    STRING - CHARACTER OPERATORS
******************************************************************************/
/*
 *      STRING -- Combining a string and Character using the '+' operator
 */
template <typename charType>
string_t<charType> string_t<charType>::operator + ( const charType c ) const {
    charType* temp = nullptr;
    
    if ( numUsed < numTotal ) {
        temp = new charType[ numUsed + DEFAULT_GRANULARITY + 1 ]();
        
        temp[ numUsed ] = c;
    }
    else {
        int len = numUsed + DEFAULT_GRANULARITY + 1;
        // return a null string if there was an integer overflow
        if ( len < 0 )
            return string_t();
            
        temp = new charType[ len ]();
        
        for ( int i = 0; i < numUsed; ++i )
            temp[ i ] = data[ i ];
            
        temp[ numUsed ] = c;
    }
    return string_t( numUsed+1, numUsed + DEFAULT_GRANULARITY, DEFAULT_GRANULARITY, temp );
}

/*
 *      STRING -- Appending C-String using the '+=' operator
 */
template <typename charType>
string_t<charType>& string_t<charType>::operator += ( const charType c ) {
    if ( numUsed + 1 < numTotal ) {
        data[ numUsed++ ] = c;
    }
    else {
        numTotal += granularity;
        charType* temp = new charType[ numTotal + 1 ]();
        for ( int i = 0; i < numUsed; ++i )
            temp[ i ] = data[ i ];
        temp[ numUsed++ ] = c;
        delete [] data;
        data = temp;
    }
    
    return *this;
}

/*
 *      STRING -- Assignment operator using a C-string
 */
template <typename charType>
string_t<charType>& string_t<charType>::operator = ( const charType c ) {
    // don't reallocate if the current size equals the granularity value
    if ( numTotal == granularity ) {
        int i = numUsed;
        while ( i-- )
            data[ i ] = '\0';
        numUsed = 1;
    }
    else {
        delete [] data;
        data = new charType[ granularity + 1 ]();
        data[0] = c;
        numUsed = 0;
        numTotal = granularity;
    }
    
    return *this;
}

/******************************************************************************
    STRING - SUBSCRIPT OPERATORS
******************************************************************************/
template <typename charType>
charType string_t<charType>::operator[] ( int i ) const {
    HL_ASSERT( i >= 0 && i < numUsed );
    return data[ i ];
}

template <typename charType>
charType& string_t<charType>::operator[] ( int i ) {
    HL_ASSERT( i >= 0 && i < numUsed );
    return data[ i ];
}


/******************************************************************************
    STRING - MISCELLANEOUS
******************************************************************************/
template <typename charType>
void string_t<charType>::setReserveSize( int r ) {
    granularity = (r > 0) ? r : 1;
}

template <typename charType>
void string_t<charType>::clear() {
    delete [] data;
    
    numUsed = 0;
    numTotal = granularity;
    data = new charType[ granularity + 1 ]();
}



} // end containers namespace
} // end hamLibs namespace

#endif /* __HL_STRING_H__ */


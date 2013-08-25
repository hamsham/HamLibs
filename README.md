HamLibs
=======

A miscellaneous C++11 library being created for use with the Harbinger Game
Engine. Hamlibs was originally created in order to have cross-platform
libraries which could be used across several projects requiring non
game-specific functionality.

So far, it includes:
    1.  A fully templated linear math library with 2D/3D/4D Vectors and
        Matrices, a quaternion class, and various helper functions. It also has
        a fixed-point number class with multiple compile-time operators.
    
    2.  A Simple set of templated object containers which includes a stack,
        list, queue, array, string, and b-tree classes.
    
    3.  Lightweight assertions.
    
    4.  Compile-time string hashing (DJB2, FNV1, and SDBM algorithms) that
        supports ANSII, UTF-8, UTF-16, and UTF-32.
    
    5.  Time Classes (clock, stopwatch, and countdown timer).
    
    6.  Lightweight logging, utilizing redirection to native C++ I/O Streams.
    
    7.  Fast random number generation.
    
    8.  Compile-Time endianness determination.
    
    9.  Identification macros for various operating systems, architectures, and
        compilers.

It's still a huge work in progress, so bear with me as I get this and the Harbinger Engine up and running.

Cheers!
    --Miles

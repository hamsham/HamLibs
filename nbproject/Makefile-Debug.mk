#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW32_Qt-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/assert.o \
	${OBJECTDIR}/src/bits.o \
	${OBJECTDIR}/src/fixed.o \
	${OBJECTDIR}/src/logger.o \
	${OBJECTDIR}/src/mat_utils.o \
	${OBJECTDIR}/src/math.o \
	${OBJECTDIR}/src/matrix2.o \
	${OBJECTDIR}/src/matrix3.o \
	${OBJECTDIR}/src/matrix4.o \
	${OBJECTDIR}/src/pointer.o \
	${OBJECTDIR}/src/quat.o \
	${OBJECTDIR}/src/quat_utils.o \
	${OBJECTDIR}/src/randomNum.o \
	${OBJECTDIR}/src/scalar_utils.o \
	${OBJECTDIR}/src/timeObject.o \
	${OBJECTDIR}/src/vec2.o \
	${OBJECTDIR}/src/vec3.o \
	${OBJECTDIR}/src/vec4.o \
	${OBJECTDIR}/src/vec_utils.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f4

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-mieee-fp -mmmx -msse -msse2 -mfpmath=sse -g -O2 -pedantic-errors -Werror -Wall -Wextra -flto -static-libgcc -static-libstdc++
CXXFLAGS=-mieee-fp -mmmx -msse -msse2 -mfpmath=sse -g -O2 -pedantic-errors -Werror -Wall -Wextra -flto -static-libgcc -static-libstdc++

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhamlibs_d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhamlibs_d.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhamlibs_d.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhamlibs_d.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhamlibs_d.a

${OBJECTDIR}/src/assert.o: nbproject/Makefile-${CND_CONF}.mk src/assert.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/assert.o src/assert.cpp

${OBJECTDIR}/src/bits.o: nbproject/Makefile-${CND_CONF}.mk src/bits.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bits.o src/bits.cpp

${OBJECTDIR}/src/fixed.o: nbproject/Makefile-${CND_CONF}.mk src/fixed.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/fixed.o src/fixed.cpp

${OBJECTDIR}/src/logger.o: nbproject/Makefile-${CND_CONF}.mk src/logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/logger.o src/logger.cpp

${OBJECTDIR}/src/mat_utils.o: nbproject/Makefile-${CND_CONF}.mk src/mat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/mat_utils.o src/mat_utils.cpp

${OBJECTDIR}/src/math.o: nbproject/Makefile-${CND_CONF}.mk src/math.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/math.o src/math.cpp

${OBJECTDIR}/src/matrix2.o: nbproject/Makefile-${CND_CONF}.mk src/matrix2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/matrix2.o src/matrix2.cpp

${OBJECTDIR}/src/matrix3.o: nbproject/Makefile-${CND_CONF}.mk src/matrix3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/matrix3.o src/matrix3.cpp

${OBJECTDIR}/src/matrix4.o: nbproject/Makefile-${CND_CONF}.mk src/matrix4.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/matrix4.o src/matrix4.cpp

${OBJECTDIR}/src/pointer.o: nbproject/Makefile-${CND_CONF}.mk src/pointer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pointer.o src/pointer.cpp

${OBJECTDIR}/src/quat.o: nbproject/Makefile-${CND_CONF}.mk src/quat.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/quat.o src/quat.cpp

${OBJECTDIR}/src/quat_utils.o: nbproject/Makefile-${CND_CONF}.mk src/quat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/quat_utils.o src/quat_utils.cpp

${OBJECTDIR}/src/randomNum.o: nbproject/Makefile-${CND_CONF}.mk src/randomNum.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/randomNum.o src/randomNum.cpp

${OBJECTDIR}/src/scalar_utils.o: nbproject/Makefile-${CND_CONF}.mk src/scalar_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/scalar_utils.o src/scalar_utils.cpp

${OBJECTDIR}/src/timeObject.o: nbproject/Makefile-${CND_CONF}.mk src/timeObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/timeObject.o src/timeObject.cpp

${OBJECTDIR}/src/vec2.o: nbproject/Makefile-${CND_CONF}.mk src/vec2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/vec2.o src/vec2.cpp

${OBJECTDIR}/src/vec3.o: nbproject/Makefile-${CND_CONF}.mk src/vec3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/vec3.o src/vec3.cpp

${OBJECTDIR}/src/vec4.o: nbproject/Makefile-${CND_CONF}.mk src/vec4.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/vec4.o src/vec4.cpp

${OBJECTDIR}/src/vec_utils.o: nbproject/Makefile-${CND_CONF}.mk src/vec_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/vec_utils.o src/vec_utils.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/_ext/2103785198/btree_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/_ext/2103785198/endian_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/_ext/2103785198/mathTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/_ext/2103785198/pointer_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/_ext/2103785198/btree_test.o: ../tests/btree_test.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/2103785198
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -I. -I. -std=c++11 -O1 -lstdthread -lpthread -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/2103785198/btree_test.o ../tests/btree_test.cpp


${TESTDIR}/_ext/2103785198/endian_test.o: ../tests/endian_test.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/2103785198
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/2103785198/endian_test.o ../tests/endian_test.cpp


${TESTDIR}/_ext/2103785198/mathTest.o: ../tests/mathTest.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/2103785198
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -DGLM_FORCE_PURE -Iinclude -I. -std=c++11 -march=native -mfpmath=sse -msse -msse2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/2103785198/mathTest.o ../tests/mathTest.cpp


${TESTDIR}/_ext/2103785198/pointer_test.o: ../tests/pointer_test.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/2103785198
	${RM} "$@.d"
	$(COMPILE.cc) -DHL_DEBUG -Iinclude -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/2103785198/pointer_test.o ../tests/pointer_test.cpp


${OBJECTDIR}/src/assert_nomain.o: ${OBJECTDIR}/src/assert.o src/assert.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/assert.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/assert_nomain.o src/assert.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/assert.o ${OBJECTDIR}/src/assert_nomain.o;\
	fi

${OBJECTDIR}/src/bits_nomain.o: ${OBJECTDIR}/src/bits.o src/bits.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/bits.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bits_nomain.o src/bits.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/bits.o ${OBJECTDIR}/src/bits_nomain.o;\
	fi

${OBJECTDIR}/src/fixed_nomain.o: ${OBJECTDIR}/src/fixed.o src/fixed.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/fixed.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/fixed_nomain.o src/fixed.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/fixed.o ${OBJECTDIR}/src/fixed_nomain.o;\
	fi

${OBJECTDIR}/src/logger_nomain.o: ${OBJECTDIR}/src/logger.o src/logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/logger.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/logger_nomain.o src/logger.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/logger.o ${OBJECTDIR}/src/logger_nomain.o;\
	fi

${OBJECTDIR}/src/mat_utils_nomain.o: ${OBJECTDIR}/src/mat_utils.o src/mat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/mat_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/mat_utils_nomain.o src/mat_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/mat_utils.o ${OBJECTDIR}/src/mat_utils_nomain.o;\
	fi

${OBJECTDIR}/src/math_nomain.o: ${OBJECTDIR}/src/math.o src/math.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/math.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/math_nomain.o src/math.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/math.o ${OBJECTDIR}/src/math_nomain.o;\
	fi

${OBJECTDIR}/src/matrix2_nomain.o: ${OBJECTDIR}/src/matrix2.o src/matrix2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/matrix2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/matrix2_nomain.o src/matrix2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/matrix2.o ${OBJECTDIR}/src/matrix2_nomain.o;\
	fi

${OBJECTDIR}/src/matrix3_nomain.o: ${OBJECTDIR}/src/matrix3.o src/matrix3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/matrix3.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/matrix3_nomain.o src/matrix3.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/matrix3.o ${OBJECTDIR}/src/matrix3_nomain.o;\
	fi

${OBJECTDIR}/src/matrix4_nomain.o: ${OBJECTDIR}/src/matrix4.o src/matrix4.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/matrix4.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/matrix4_nomain.o src/matrix4.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/matrix4.o ${OBJECTDIR}/src/matrix4_nomain.o;\
	fi

${OBJECTDIR}/src/pointer_nomain.o: ${OBJECTDIR}/src/pointer.o src/pointer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pointer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pointer_nomain.o src/pointer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pointer.o ${OBJECTDIR}/src/pointer_nomain.o;\
	fi

${OBJECTDIR}/src/quat_nomain.o: ${OBJECTDIR}/src/quat.o src/quat.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/quat.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/quat_nomain.o src/quat.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/quat.o ${OBJECTDIR}/src/quat_nomain.o;\
	fi

${OBJECTDIR}/src/quat_utils_nomain.o: ${OBJECTDIR}/src/quat_utils.o src/quat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/quat_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/quat_utils_nomain.o src/quat_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/quat_utils.o ${OBJECTDIR}/src/quat_utils_nomain.o;\
	fi

${OBJECTDIR}/src/randomNum_nomain.o: ${OBJECTDIR}/src/randomNum.o src/randomNum.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/randomNum.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/randomNum_nomain.o src/randomNum.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/randomNum.o ${OBJECTDIR}/src/randomNum_nomain.o;\
	fi

${OBJECTDIR}/src/scalar_utils_nomain.o: ${OBJECTDIR}/src/scalar_utils.o src/scalar_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/scalar_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/scalar_utils_nomain.o src/scalar_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/scalar_utils.o ${OBJECTDIR}/src/scalar_utils_nomain.o;\
	fi

${OBJECTDIR}/src/timeObject_nomain.o: ${OBJECTDIR}/src/timeObject.o src/timeObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/timeObject.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/timeObject_nomain.o src/timeObject.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/timeObject.o ${OBJECTDIR}/src/timeObject_nomain.o;\
	fi

${OBJECTDIR}/src/vec2_nomain.o: ${OBJECTDIR}/src/vec2.o src/vec2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/vec2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/vec2_nomain.o src/vec2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/vec2.o ${OBJECTDIR}/src/vec2_nomain.o;\
	fi

${OBJECTDIR}/src/vec3_nomain.o: ${OBJECTDIR}/src/vec3.o src/vec3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/vec3.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/vec3_nomain.o src/vec3.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/vec3.o ${OBJECTDIR}/src/vec3_nomain.o;\
	fi

${OBJECTDIR}/src/vec4_nomain.o: ${OBJECTDIR}/src/vec4.o src/vec4.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/vec4.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/vec4_nomain.o src/vec4.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/vec4.o ${OBJECTDIR}/src/vec4_nomain.o;\
	fi

${OBJECTDIR}/src/vec_utils_nomain.o: ${OBJECTDIR}/src/vec_utils.o src/vec_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/vec_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -DHL_DEBUG -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/vec_utils_nomain.o src/vec_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/vec_utils.o ${OBJECTDIR}/src/vec_utils_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhamlibs_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

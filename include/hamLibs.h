/* 
 * File:   hamLibs.h
 * Author: hammy
 *
 * Created on May 6, 2012, 2:05 PM
 */

#ifndef __HAMLIBS_H__
#define	__HAMLIBS_H__

#ifndef __cplusplus
	#error "A C++11-compliant compiler is required to build Ham's libraries"
#endif

/*	NOTES:
 * Don't forget to call 'hlInit()' before using this library
 */

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>

//---------------------------------------------------------------------
//				Preprocessor Wizardry
//---------------------------------------------------------------------
#include "defs/preprocessor.h"

//---------------------------------------------------------------------
//				Forward Declarations
//---------------------------------------------------------------------
#include "defs/types.h"

//---------------------------------------------------------------------
//				Meat & Potatoes
//---------------------------------------------------------------------
#include "containers/linkedList.h"
#include "containers/stack.h"
#include "containers/queue.h"
#include "containers/dynArr.h"
#include "containers/dictionary.h"
#include "math/math.h"
#include "hamString.h"
#include "logger.h"
#include "filesystem.h"
#include "stringUtils.h"
#include "config.h"
#include "database.h"

//---------------------------------------------------------------------
//				Function prototypes
//---------------------------------------------------------------------
bool	hlInit();

#endif	/* HAMLIBS_H */

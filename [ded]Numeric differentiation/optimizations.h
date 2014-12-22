#ifndef OPTIMIZATIONS_H_INCL
#define OPTIMIZATIONS_H_INCL


#include "TokenTree.h"
#include <math.h>

//==============================================================================
int O1 (node** Node); //Constants
//==============================================================================
int O2 (node** Node); //Delete unmeaning elements like 0*x, x*0, 0*0, 0+0 etc
//==============================================================================

#endif // OPTIMIZATIONS_H_INCL

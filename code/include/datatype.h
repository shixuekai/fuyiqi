//<Date Type Software>
//**********************************************************************************************
//Copyright 2016-12-17  Joer Simi
//All rights reserved
//**********************************************************************************************
#ifndef DATATYPE_H
#define DATATYPE_H

#include <stdio.h>

typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned long  U32;
typedef signed char    S8;
typedef signed short   S16;
typedef signed long    S32;






// NOTE. these have problem with long integer (32-bit) on C51
#ifndef MAX
#define MAX(a, b)        (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a ,b)        (((a) < (b)) ? (a) : (b))
#endif


#define COUNTOF( array )    (sizeof(array) / sizeof((array)[0]))

#endif


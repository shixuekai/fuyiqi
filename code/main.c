//<Date Type Software>
//**********************************************************************************************
//Copyright 2016-12-17  Joer Simi
//All rights reserved
//**********************************************************************************************
#define MAIN_C
#include <stdio.h>

#include "IDateApiImpl.h"

/**********************************************************************************************/
#define MAIN_DBG(x)      //x
/**********************************************************************************************/

int main(void)
{
    MAIN_DBG(printf("welcom to C world\n"));
    printf("\033[31;43m2016/12/3/ is %u\033[0m\n",eventDateGetDayOfWeek(2016, 12, 3));
    return 1;
}

#undef MAIN_C


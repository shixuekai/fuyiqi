//<Date Api Software>
//**********************************************************************************************
//Copyright 2016-12-17  Joer Simi
//All rights reserved
//**********************************************************************************************
#ifndef IDATEAPIIMPL_H
#define IDATEAPIIMPL_H

#include "datatype.h"



/********************************************************************************/
/*                     Macro                    */
/* ******************************************************************************/
#define SECONDS_PER_HALF_MIN    30L
#define SECONDS_PER_MIN         60L
#define SECONDS_PER_HOUR        3600L
#define SECONDS_PER_HALF_HOUR   1800L
#define SECONDS_PER_DAY         86400L
#define SECONDS_PER_30DAYS      (30*SECONDS_PER_DAY)
#define MINS_PER_HOUR           60
#define HOURS_PER_DAY           24
    


U8 eventDateGetDayOfWeek(U16 u16Year, U8 u8Month, U8 u8Day);
U8 eventDateIsLeapYear(U16 u16Year);
U8 eventDateDaysOfThisMonth(U16 u16Year, U8 u8Month);


#endif


//<Date Api Software>
//**********************************************************************************************
//Copyright 2016-12-17  Joer Simi
//All rights reserved
//**********************************************************************************************
#define IDATEAPIIMPL_C

#include "datatype.h"
#include "IDateApiImpl.h"


/*code*/ U8 SolarCal[12] =
{
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/*code*/ U16 SolarDays[28] =
{
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365, 396, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366, 397
};


//*************************************************************************
//Function name:    eventDateIsLeapYear
//Passing parameter:    U16 year :  current solar year
//Return parameter:     U8: Leap year or not
//Description:      Decide leap year
//*******************************************************
U8 eventDateIsLeapYear(U16 u16Year)
{
    if ( u16Year % 400 == 0 )
    {
        return 1;
    }
    else if ( u16Year % 100 == 0 )
    {
        return 0;
    }
    else if ( u16Year % 4 == 0 )
    {
        return 1;
    }
    
    return 0;

}

//*************************************************************************
//Function name:    eventDateGetDayOfWeek
//Passing parameter:    U16 year :  current solar year, U8 month : current solar month, U8 day : current solar day
//Return parameter:     U8: index of week of curren solar year, month, and day
//Description:      index of week
//*******************************************************
U8 eventDateGetDayOfWeek(U16 u16Year, U8 u8Month, U8 u8Day)
{
    U8 i;
    U16 u16days = 0;
    U32 u32sum;
    
    for(i = 1; i<=(u8Month - 1); i++)
    {
        u16days+=SolarCal[i - 1];
    }
    
    if(eventDateIsLeapYear(u16Year)&&u8Month>2)
        u16days+=1;
    
    u16days+=u8Day;
    
    u32sum = u16Year -1 + ((u16Year - 1)/4) - ((u16Year - 1)/100) + ((u16Year - 1)/400) + u16days;
    
   return (U8) (u32sum%7);

}

//*************************************************************************
//Function name:    eventDateGetDaysOfThisMonth
//Passing parameter:    U16 u16Year : specific year
//              U8 u8Month : specific month (1 ~ 12)
//Return parameter:     U8: number of days
//Description:      Get number of days of the specific month
//*************************************************************************
U8 eventDateGetDaysOfThisMonth(U16 u16Year, U8 u8Month)
{
    if ( u8Month >= 1 && u8Month <= 12 )
    {
        return ((eventDateIsLeapYear(u16Year) && u8Month == 2) ? 29 : SolarCal[u8Month - 1]);
    }
    else
    {
        return 0;
    }
}

#undef IDATEAPIIMPL_C


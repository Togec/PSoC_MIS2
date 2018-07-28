#include "stdio.h"
#include "minunit.h"

/*******************************************************************************/
// Reference:
// https://www.codingunit.com/how-to-make-a-calendar-in-c
// Type F = Compound CP32: Date and Time
// http://www.m-bus.com/files/MBDOC48.PDF
/*******************************************************************************/
char rtc_typef[4];

int rtc_sec = 7;
void rtc_set_seconds(int s)
{
    rtc_sec = s;
}


void rtc_set_minutes(int m)
{
    //rtc_min = m;
    rtc_typef[0] = (rtc_typef[0] & (~0x3F)) | (m & 0x3F);
}

//int rtc_min = 59;
#define rtc_min (rtc_typef[0] & 0x3F)

void rtc_set_hour(int h)
{
    //rtc_hour = h;
    rtc_typef[1] = (rtc_typef[1] & (~0x1F)) | (h & 0x1F);
}

//int rtc_hour = 7;
#define rtc_hour (rtc_typef[1] & 0x1F)

void rtc_set_day(int d)
{
    //rtc_day = d;
    rtc_typef[2] = (rtc_typef[2] & (~0x1F)) | (d & 0x1F);
}

//int rtc_day = 5;
#define rtc_day (rtc_typef[2] & 0x1F)

void rtc_set_month(int m)
{
    //rtc_month = m;
    rtc_typef[3] = (rtc_typef[3] & (~0x0F)) | (m & 0x0F);
}

//int rtc_month = 5;
#define rtc_month (rtc_typef[3] & 0x0F)

void rtc_set_years(int y)
{
    //rtc_year = y;
    //y %= 100;
    while (y >= 100) y -= 100;
    rtc_typef[2] = (rtc_typef[2] & (0x1F)) | ((y << 5)  & (~0x1F));
    rtc_typef[3] = (rtc_typef[3] & (0x0F)) | ((y << (4-3))  & (~0x0F));
}

//int rtc_year = 5;
#define rtc_year (2000 + (((rtc_typef[3]>>1) & 0x78) | ((rtc_typef[2] >> 5) & 0x07)))

int rtc_is_leap_year(void)
{
    //if(rtc_year % 4 == 0) && (rtc_year % 100 != 0) || (rtc_year % 400 == 0)
    
    int y4 = rtc_year & 0x3;
    
    int y100 = rtc_year;
    while (y100 >= 100) y100 -= 100;
    
    int y400 = rtc_year;
    while (y400 >= 400) y400 -= 400;
    
    return ((y4 == 0) && (y100 != 0)) || (y400 == 0);
}

int rtc_days_in_month(void)
{
    const int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

    if ((rtc_month == 2) && (rtc_is_leap_year()))
        return days_in_month[rtc_month] + 1;
    else
        return days_in_month[rtc_month];
}

void rtc_tick(void)
{
    rtc_sec++;
    if (rtc_sec>59)
    {
        rtc_sec = 0;
        //rtc_min++;
        rtc_typef[0] = ((rtc_typef[0]+1) & 0x3F) | (rtc_typef[0] & (~0x3F));
        if (rtc_min>59)
        {
            //rtc_min = 0;
            rtc_typef[0] &= ~0x3F;
            //rtc_hour++;
            rtc_typef[1] = (rtc_typef[1] & (~0x1F)) | ((rtc_typef[1]+1) & 0x1F);
            if (rtc_hour>23)
            {
                //rtc_hour=0;
                rtc_typef[1] &= ~0x1F;
                //rtc_day++;
                rtc_typef[2] = (rtc_typef[2] & (~0x1F)) | ((rtc_typef[2]+1) & 0x1F);
                if ((rtc_day == 0) || (rtc_day > rtc_days_in_month()))
                {
                    //rtc_day=1;
                    rtc_typef[2] = (rtc_typef[2] & (~0x1F)) | 1;
                    //rtc_month++;
                    rtc_typef[3] = (rtc_typef[3] & (~0x0F)) | ((rtc_typef[3]+1) & 0x0F);
                    if (rtc_month>12)
                    {
                        //rtc_month = 1;
                        rtc_typef[3] = (rtc_typef[3] & (~0x0F)) | 1;
                        //rtc_year++;
                        rtc_set_years (rtc_year+1);
                    }
                }
            }
        }
    }
}

/*******************************************************************************/
 
char * test_rtc_sec() {
    rtc_set_seconds(0);
    it("initialize RTC seconds to 0", rtc_sec == 0);
    rtc_set_seconds(1);
    it("initialize RTC seconds to 1", rtc_sec == 1);
    rtc_tick();
    it("increment RTC seconds by 1 (1->2)", rtc_sec == 2);
    rtc_set_seconds(59);
    it("initialize RTC seconds to 0", rtc_sec == 59);
    rtc_tick();
    it("handle RTC seconds overflow (59->0)", rtc_sec == 0);
    return 0;
}

char * test_rtc_min() {
    rtc_set_minutes(0);
    it("initialize RTC minutes to 0", rtc_min == 0);
    rtc_set_minutes(1);
    it("initialize RTC minutes to 1", rtc_min == 1);
    rtc_set_seconds(59);
    rtc_tick();
    it("increment RTC minutes by 1 (1->2)", rtc_min == 2);
    rtc_set_minutes(59);
    rtc_set_seconds(59);
    rtc_tick();
    it("handle RTC minutes overflow (59->0)", rtc_min == 0);
    return 0;
}

char * test_rtc_hour() {
    rtc_set_hour(0);
    it("initialize RTC minutes to 0", rtc_hour == 0);
    rtc_set_hour(1);
    it("initialize RTC minutes to 1", rtc_hour == 1);
    rtc_set_minutes(59);
    rtc_set_seconds(59);
    rtc_tick();
    it("increment RTC hours by 1 (1->2)", rtc_hour == 2);
    rtc_set_minutes(59);
    rtc_set_seconds(59);
    rtc_set_hour(23);
    it("initialize RTC hours to 23", rtc_hour == 23);
    rtc_tick();
    it("handle RTC hours overflow (23->0)", rtc_hour == 0);
    return 0;
}

char * test_rtc_days_months() {
    rtc_set_day(0);
    it("initialize RTC minutes to 0", rtc_day == 0);
    rtc_set_day(1);
    it("initialize RTC minutes to 1", rtc_day == 1);
    rtc_set_minutes(59);
    rtc_set_seconds(59);
    rtc_set_hour(23);
    rtc_tick();
    it("increment RTC days by 1 (1->2)", rtc_day == 2);
    rtc_set_minutes(59);
    rtc_set_seconds(59);
    rtc_set_hour(23);
    rtc_set_day(31);
    it("initialize RTC days to 31", rtc_day == 31);
    rtc_set_month(1);
    it("initialize RTC month to 1", rtc_month == 1);
    rtc_tick();
    it("handle RTC days overflow (31->1)", rtc_day == 1);
    it("increment RTC month (1->2)", rtc_month == 2);
    rtc_set_minutes(59);
    rtc_set_seconds(59);
    rtc_set_hour(23);
    rtc_set_day(31);
    rtc_set_month(12);
    it("initialize RTC month to 1", rtc_month == 12);
    rtc_tick();
    it("handle RTC days overflow (31->1)", rtc_day == 1);
    it("increment RTC month (1->2)", rtc_month == 1);
    return 0;
}

char * test_rtc_leap_years() {
    
    const int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    
    int y;
    int m;
    
    int nmin = 1, lmin = 1;
    int nmax = 13, lmax = 13;

    for (y = 2000; y < 2100; y++)
    {
        rtc_set_years(y);
        //it("initialize years to i", rtc_year == i);
        sprintf(text, "initialize years to %d (%d)", y, rtc_year);
        it(text, rtc_year == y);
        
        if( ((rtc_year % 4 == 0) && (rtc_year % 100 != 0)) || (rtc_year % 400 == 0) )
        {
            sprintf(text, "establishe a leap year %d", rtc_year);
            it(text, rtc_is_leap_year() != 0);
            
            for (m = lmin; m < lmax; m++)
            {
                rtc_set_month(m);
                sprintf(text, "initialize year to %d and month to %d", rtc_year, rtc_month);
                it(text, rtc_year == y);
                it(text, rtc_month == m);
                sprintf(text, "establishe days in month %d of leap year %d", rtc_month, rtc_year);
                if (rtc_month == 2)
                {
                   it(text, (days_in_month[rtc_month]+1) == rtc_days_in_month());
                   rtc_set_day(days_in_month[rtc_month]+1);
                }
                else
                {
                   it(text, days_in_month[rtc_month] == rtc_days_in_month());
                   rtc_set_day(days_in_month[rtc_month]);
                }
                rtc_set_seconds(59);
                rtc_set_minutes(59);
                rtc_set_hour(23);
                rtc_tick();
                sprintf(text, "handle end of month overflow, year %d, month %d, day %d, hour %d, minutes %d, seconds %d", rtc_year, rtc_month, rtc_day, rtc_hour, rtc_min, rtc_sec);
                it(text, rtc_sec == 0);
                it(text, rtc_min == 0);
                it(text, rtc_hour == 0);
                it(text, rtc_day == 1);
                if (m < 12)
                {
                   it(text, rtc_month == m+1);
                   it(text, rtc_year == y);
                }
                
                else
                {
                   it(text, rtc_month == 1);
                   it(text, rtc_year == (y+1));
                }
                                
            }
            lmin = 2;
            lmax = 5;
        }
        else
        {
            sprintf(text, "establishe a normal year %d", rtc_year);
            it(text, rtc_is_leap_year() == 0);
            for (m = nmin; m < nmax; m++)
            {
                rtc_set_month(m);
                sprintf(text, "initialize year to %d and month to %d", rtc_year, rtc_month);
                it(text, rtc_year == y);
                it(text, rtc_month == m);
                sprintf(text, "establishe days in month %d of normal year %d", rtc_month, rtc_year);
                it(text, days_in_month[rtc_month] == rtc_days_in_month());
                
                rtc_set_day(days_in_month[rtc_month]);
                rtc_set_seconds(59);
                rtc_set_minutes(59);
                rtc_set_hour(23);
                rtc_tick();
                sprintf(text, "handle end of month overflow, year %d, month %d, day %d, hour %d, minutes %d, seconds %d", rtc_year, rtc_month, rtc_day, rtc_hour, rtc_min, rtc_sec);
                it(text, rtc_sec == 0);
                it(text, rtc_min == 0);
                it(text, rtc_hour == 0);
                it(text, rtc_day == 1);
                if (m < 12)
                {
                   it(text, rtc_month == m+1);
                   it(text, rtc_year == y);
                }
                
                else
                {
                   it(text, rtc_month == 1);
                   it(text, rtc_year == (y+1));
                }
            }
            nmin = 2;
            nmax = 5;
        }
    }
    return 0;
}

char * test_rtc_typef() {
    //http://www.multical.hu/WiredMBus-water.pdf
    rtc_typef[0]=0x0A;
    rtc_typef[1]=0x2D;
    rtc_typef[2]=0x82;
    rtc_typef[3]=0x09;
    it("initialize RTC minutes to 10", rtc_min == 10);
    it("initialize RTC hour to 13", rtc_hour == 13);
    it("initialize RTC day to 2", rtc_day == 2);
    it("initialize RTC month to 9", rtc_month == 9);
    it("initialize RTC year to 2004", rtc_year == 2004);
    return 0;
}

struct Tests TestCollection[] =
{
    {"Real Time Clock Seconds", &test_rtc_sec},
    {"Real Time Clock Minutes", &test_rtc_min},
    {"Real Time Clock Hours", &test_rtc_hour},
    {"Real Time Clock Days & Months", &test_rtc_days_months},
    {"Real Time Clock Leap Years", &test_rtc_leap_years},
    {"Real Time Clock TypeF", &test_rtc_typef}
};

const int testsCount = sizeof(TestCollection)/sizeof(struct Tests);
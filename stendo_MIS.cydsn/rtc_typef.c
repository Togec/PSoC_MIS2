#include "stdio.h"
#include "rtc_typef.h"

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

int rtc_get_seconds(void)
{
    return rtc_sec;
}

void rtc_set_minutes(int m)
{
    rtc_typef[0] = (rtc_typef[0] & (~0x3F)) | (m & 0x3F);
}

int rtc_get_minutes(void)
{
    return (rtc_typef[0] & 0x3F);
}

void rtc_set_hour(int h)
{
    rtc_typef[1] = (rtc_typef[1] & (~0x1F)) | (h & 0x1F);
}

int rtc_get_hour(void)
{
    return (rtc_typef[1] & 0x1F);
}

void rtc_set_day(int d)
{
    rtc_typef[2] = (rtc_typef[2] & (~0x1F)) | (d & 0x1F);
}

int rtc_get_day(void)
{
    return (rtc_typef[2] & 0x1F);
}

void rtc_set_month(int m)
{
    rtc_typef[3] = (rtc_typef[3] & (~0x0F)) | (m & 0x0F);
}

int rtc_get_month(void)
{
    return (rtc_typef[3] & 0x0F);
}

void rtc_set_years(int y)
{
    y %= 100;
    rtc_typef[2] = (rtc_typef[2] & (0x1F)) | ((y << 5)  & (~0x1F));
    rtc_typef[3] = (rtc_typef[3] & (0x0F)) | ((y << (4-3))  & (~0x0F));
}

int rtc_get_years(void)
{
    return ((2000 + (((rtc_typef[3]>>1) & 0x78) | ((rtc_typef[2] >> 5) & 0x07))));
}

int rtc_is_leap_year(void)
{
    return ((rtc_get_years() % 4 == 0) && (rtc_get_years() % 100 != 0)) || (rtc_get_years() % 400 == 0);
}

int rtc_days_in_month(void)
{
    const int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if ((rtc_get_month() == 2) && (rtc_is_leap_year()))
        return days_in_month[rtc_get_month()] + 1;
    else
        return days_in_month[rtc_get_month()];
}

void rtc_tick(void)
{
    rtc_set_seconds(rtc_get_seconds()+1);
    if (rtc_get_seconds()>59)
    {
        rtc_set_seconds(0);
        rtc_set_minutes(rtc_get_minutes()+1);
        if (rtc_get_minutes()>59)
        {
            rtc_set_minutes(0);
            rtc_set_hour(rtc_get_hour()+1);
            if (rtc_get_hour()>23)
            {
                rtc_set_hour(0);
                rtc_set_day(rtc_get_day()+1);
                if ((rtc_get_day() == 0) || (rtc_get_day() > rtc_days_in_month()))
                {
                    rtc_set_day(1);
                    rtc_set_month (rtc_get_month()+1);
                    if (rtc_get_month()>12)
                    {
                        rtc_set_month (1);
                        rtc_set_years (rtc_get_years()+1);
                    }
                }
            }
        }
    }
}

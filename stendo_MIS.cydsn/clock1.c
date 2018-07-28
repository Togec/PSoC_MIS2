#include "stdio.h"
#include "minunit.h"

/*******************************************************************************/

int rtc_sec = 7;
int rtc_min = 59;
int rtc_hrs = 7;

void rtc_set_seconds(int s)
{
    rtc_sec = s;
}

void rtc_set_minutes(int m)
{
    rtc_min = m;
}

void rtc_set_hours(int h)
{
    rtc_hrs = h;
}

void rtc_tick(void)
{
    rtc_sec++;
    if (rtc_sec>59)
    {
        rtc_sec = 0;
        rtc_min++;
        if (rtc_min>59)
        {
            rtc_min = 0;
            rtc_hrs++;
            if (rtc_hrs>23)
            {
                rtc_hrs=0;
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
    it("initialize RTC seconds to 0", rtc_sec == 59);
    rtc_tick();
    it("handle RTC seconds overflow (59->0)", rtc_sec == 0);
    it("increment RTC minutes by 1 (1->2)", rtc_min == 2);
    
    rtc_set_minutes(59);
    it("initialize RTC minutes to 0", rtc_min == 59);
    
    rtc_set_seconds(59);
    it("initialize RTC seconds to 0", rtc_sec == 59);
    
    rtc_tick();
    it("handle RTC minutes overflow (59->0)", rtc_min == 0);
    return 0;
}

char * test_rtc_hrs() {
    rtc_set_hours(0);
    it("initialize RTC minutes to 0", rtc_hrs == 0);
    rtc_set_hours(1);
    it("initialize RTC minutes to 1", rtc_hrs == 1);
    
    rtc_set_minutes(59);
    it("initialize RTC minutes to 0", rtc_min == 59);
    
    rtc_set_seconds(59);
    it("initialize RTC seconds to 0", rtc_sec == 59);
    
    rtc_tick();
    it("handle RTC seconds overflow (59->0)", rtc_sec == 0);
    it("handle RTC minutes overflow (59->0)", rtc_min == 0);
    it("increment RTC hours by 1 (1->2)", rtc_hrs == 2);
    
    rtc_set_minutes(59);
    it("initialize RTC minutes to 0", rtc_min == 59);
    
    rtc_set_seconds(59);
    it("initialize RTC seconds to 0", rtc_sec == 59);
    
    rtc_set_hours(23);
    it("initialize RTC hours to 23", rtc_hrs == 23);
    
    rtc_tick();
    it("handle RTC seconds overflow (59->0)", rtc_sec == 0);
    it("handle RTC minutes overflow (59->0)", rtc_min == 0);
    it("handle RTC hours overflow (23->0)", rtc_hrs == 0);
    return 0;
}

struct Tests TestCollection[] =
{
    {"Real Time Clock Seconds", &test_rtc_sec},
    {"Real Time Clock Minutes", &test_rtc_min},
    {"Real Time Clock Hours", &test_rtc_hrs}
  //  describe("Real Time Clock Seconds", test_rtc_sec);
  //  describe("Real Time Clock Minutes", test_rtc_min);
};

const int testsCount = sizeof(TestCollection)/sizeof(struct Tests);
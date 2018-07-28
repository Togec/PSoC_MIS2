/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>
#include "mis.h"
/******************************************************************************
* Project Name		: MIS1
*******************************************************************************/

uint32 pulseCounter1 = 0;
CY_ISR(isr_PulseCounter_1_handler)
{
   pulseCounter1++;
}


uint32 timestampTimer = 0;

CY_ISR(isr_Timestamp_handler)
{
  timestampTimer--;
}

uint32 capture_1_count;
uint32 capture_1_timestampTimer[2];
uint8  capture_1_Timestamp_hw[2];

CY_ISR(isr_Capture_1)
{
    uint32 hw_old;
    uint32 hw_new;
    if (capture_1_count < sizeof(capture_1_Timestamp_hw))
    {   
        hw_old = Timestamp_ReadCounter();
        capture_1_timestampTimer[capture_1_count] = timestampTimer;
        hw_new = Timestamp_ReadCounter();
        if (hw_new > hw_old)
        {
            //hardware overflow
            capture_1_timestampTimer[capture_1_count]--;
        }
        capture_1_Timestamp_hw[capture_1_count] = hw_new;
        capture_1_count++;
    }
}

uint32 MIS1_ReadCount(void)
{
    return (pulseCounter1<<8) | (0xFF & PulseCounter_1_ReadCounter());
}

uint32 MIS1_ReadTotTime(void)
{
    uint32 result = 0;
    if (capture_1_count == 2)
    {
        result  = (capture_1_timestampTimer[0]<<8) | (0xFF & capture_1_Timestamp_hw[0]); /* timestampTimerStart */
        result -= (capture_1_timestampTimer[1]<<8) | (0xFF & capture_1_Timestamp_hw[1]); /* timestampTimerStop  */
    }
    return result;
}

uint32 MIS1_ReadCurTime(void)
{
    uint32 result = 0;
     uint32 cur_timestampTimer = 0;
    if (capture_1_count == 2)
    {
        result  = (capture_1_timestampTimer[0]<<8) | (0xFF & capture_1_Timestamp_hw[0]); /* timestampTimerStart */
        result -= (capture_1_timestampTimer[1]<<8) | (0xFF & capture_1_Timestamp_hw[1]); /* timestampTimerStop  */
    }
    else if (capture_1_count == 1)
    {
        result  = (capture_1_timestampTimer[0]<<8) | (0xFF & capture_1_Timestamp_hw[0]); /* timestampTimerStart */
        uint8 hw_old;
        uint8 hw_new;
        hw_old = Timestamp_ReadCounter();
        cur_timestampTimer = timestampTimer;
        hw_new = Timestamp_ReadCounter();
        if (hw_new > hw_old)
        {
            //hardware overflow
            cur_timestampTimer--;
        }
        result -= (cur_timestampTimer<<8) | (0xFF & hw_new); /* timestampTimerStop  */
    }
    return result;
}

void MIS1_SetBurstTimeout(uint32 t)
{
    BurstTimeout_1_WritePeriod(t);
}

int MIS1_WaitPacket(void)
{
    while (0 == (1 & MIS_Stat_Read()));
    return 0;
}

int MIS1_Measure(uint32 time_ms)
{
    int result;
    
    MIS_Start();
    
    result = MIS1_WaitPacket();
    if (0 != result) return result;
    
    CyDelay(time_ms);
    
    MIS_Stop();
    result = MIS1_WaitPacket();
    if (0 != result) return result;
    
    return result;
}
/******************************************************************************
*******************************************************************************/

/******************************************************************************
* Project Name		: MIS2
*******************************************************************************/

uint32 pulseCounter2 = 0;
CY_ISR(isr_PulseCounter_2_handler)
{
   pulseCounter2++;
}


uint32 capture_2_count;
uint32 capture_2_timestampTimer[2];
uint8  capture_2_Timestamp_hw[2];

CY_ISR(isr_Capture_2)
{
    uint8 hw_old;
    uint8 hw_new;
    if (capture_2_count < sizeof(capture_2_Timestamp_hw))
    {   
        hw_old = Timestamp_ReadCounter();
        capture_2_timestampTimer[capture_2_count] = timestampTimer;
        hw_new = Timestamp_ReadCounter();
        if (hw_new > hw_old)
        {
            //hardware overflow
            capture_2_timestampTimer[capture_2_count]--;
        }
        capture_2_Timestamp_hw[capture_2_count] = hw_new;
        capture_2_count++;
    }
}

uint32 MIS2_ReadCount(void)
{
    return (pulseCounter2<<8) | (0xFF & PulseCounter_2_ReadCounter());
}

uint32 MIS2_ReadTotTime(void)
{
    uint32 result = 0;
    if (capture_2_count == 2)
    {
        result  = (capture_2_timestampTimer[0]<<8) | (0xFF & capture_2_Timestamp_hw[0]); /* timestampTimerStart */
        result -= (capture_2_timestampTimer[1]<<8) | (0xFF & capture_2_Timestamp_hw[1]); /* timestampTimerStop  */
    }
    return result;
}

uint32 MIS2_ReadCurTime(void)
{
    uint32 result = 0;
     uint32 cur_timestampTimer = 0;
    if (capture_2_count == 2)
    {
        result  = (capture_2_timestampTimer[0]<<8) | (0xFF & capture_2_Timestamp_hw[0]); /* timestampTimerStart */
        result -= (capture_2_timestampTimer[1]<<8) | (0xFF & capture_2_Timestamp_hw[1]); /* timestampTimerStop  */
    }
    else if (capture_2_count == 1)
    {
        result  = (capture_2_timestampTimer[0]<<8) | (0xFF & capture_2_Timestamp_hw[0]); /* timestampTimerStart */
        uint8 hw_old;
        uint8 hw_new;
        hw_old = Timestamp_ReadCounter();
        cur_timestampTimer = timestampTimer;
        hw_new = Timestamp_ReadCounter();
        if (hw_new > hw_old)
        {
            //hardware overflow
            cur_timestampTimer--;
        }
        result -= (cur_timestampTimer<<8) | (0xFF & hw_new); /* timestampTimerStop  */
    }
    return result;
}

void MIS2_SetBurstTimeout(uint32 t)
{
    BurstTimeout_2_WritePeriod(t);
}

int MIS2_WaitPacket(void)
{
    while (0 == (2 & MIS_Stat_Read()));
    return 0;
}

int MIS2_Measure(uint32 time_ms)
{
    int result;
    
    MIS_Start();
    
    result = MIS2_WaitPacket();
    if (0 != result) return result;
    
    CyDelay(time_ms);
    
    MIS_Stop();
    result = MIS2_WaitPacket();
    if (0 != result) return result;
    
    return result;
}

/******************************************************************************
*******************************************************************************/

/******************************************************************************
* Project Name		: MIS3
*******************************************************************************/

uint32 pulseCounter3 = 0;
CY_ISR(isr_PulseCounter_3_handler)
{
   pulseCounter3++;
}


uint32 capture_3_count;
uint32 capture_3_timestampTimer[2];
uint8  capture_3_Timestamp_hw[2];

CY_ISR(isr_Capture_3)
{
    uint8 hw_old;
    uint8 hw_new;
    if (capture_3_count < sizeof(capture_2_Timestamp_hw))
    {   
        hw_old = Timestamp_ReadCounter();
        capture_3_timestampTimer[capture_3_count] = timestampTimer;
        hw_new = Timestamp_ReadCounter();
        if (hw_new > hw_old)
        {
            //hardware overflow
            capture_3_timestampTimer[capture_3_count]--;
        }
        capture_3_Timestamp_hw[capture_3_count] = hw_new;
        capture_3_count++;
    }
}

uint32 MIS3_ReadCount(void)
{
    return (pulseCounter3<<8) | (0xFF & PulseCounter_3_ReadCounter());
}

uint32 MIS3_ReadTotTime(void)
{
    uint32 result = 0;
    if (capture_3_count == 2)
    {
        result  = (capture_3_timestampTimer[0]<<8) | (0xFF & capture_3_Timestamp_hw[0]); /* timestampTimerStart */
        result -= (capture_3_timestampTimer[1]<<8) | (0xFF & capture_2_Timestamp_hw[1]); /* timestampTimerStop  */
    }
    return result;
}
uint32 MIS3_ReadCurTime(void)
{
    uint32 result = 0;
     uint32 cur_timestampTimer = 0;
    if (capture_3_count == 2)
    {
        result  = (capture_3_timestampTimer[0]<<8) | (0xFF & capture_3_Timestamp_hw[0]); /* timestampTimerStart */
        result -= (capture_3_timestampTimer[1]<<8) | (0xFF & capture_3_Timestamp_hw[1]); /* timestampTimerStop  */
    }
    else if (capture_3_count == 1)
    {
        result  = (capture_3_timestampTimer[0]<<8) | (0xFF & capture_3_Timestamp_hw[0]); /* timestampTimerStart */
        uint8 hw_old;
        uint8 hw_new;
        hw_old = Timestamp_ReadCounter();
        cur_timestampTimer = timestampTimer;
        hw_new = Timestamp_ReadCounter();
        if (hw_new > hw_old)
        {
            //hardware overflow
            cur_timestampTimer--;
        }
        result -= (cur_timestampTimer<<8) | (0xFF & hw_new); /* timestampTimerStop  */
    }
    return result;
}
void MIS3_SetBurstTimeout(uint32 t)
{
    BurstTimeout_3_WritePeriod(t);
}

int MIS3_WaitPacket(void)
{
    while (0 == (3 & MIS_Stat_Read()));
    return 0;
}

int MIS3_Measure(uint32 time_ms)
{
    int result;
    
    MIS_Start();
    
    result = MIS3_WaitPacket();
    if (0 != result) return result;
    
    CyDelay(time_ms);
    
    MIS_Stop();
    result = MIS3_WaitPacket();
    if (0 != result) return result;
    
    return result;
}

/******************************************************************************
*******************************************************************************/

/******************************************************************************
* Project Name		: MIS4
*******************************************************************************/

uint32 pulseCounter4 = 0;
CY_ISR(isr_PulseCounter_4_handler)
{
   pulseCounter4++;
}


uint32 capture_4_count;
uint32 capture_4_timestampTimer[2];
uint8  capture_4_Timestamp_hw[2];

CY_ISR(isr_Capture_4)
{
    uint8 hw_old;
    uint8 hw_new;
    if (capture_4_count < sizeof(capture_4_Timestamp_hw))
    {   
        hw_old = Timestamp_ReadCounter();
        capture_4_timestampTimer[capture_4_count] = timestampTimer;
        hw_new = Timestamp_ReadCounter();
        if (hw_new > hw_old)
        {
            //hardware overflow
            capture_4_timestampTimer[capture_4_count]--;
        }
        capture_4_Timestamp_hw[capture_4_count] = hw_new;
        capture_4_count++;
    }
}

uint32 MIS4_ReadCount(void)
{
    return (pulseCounter4<<8) | (0xFF & PulseCounter_4_ReadCounter());
}

uint32 MIS4_ReadTotTime(void)
{
    uint32 result = 0;
    if (capture_4_count == 2)
    {
        result  = (capture_4_timestampTimer[0]<<8) | (0xFF & capture_4_Timestamp_hw[0]); /* timestampTimerStart */
        result -= (capture_4_timestampTimer[1]<<8) | (0xFF & capture_4_Timestamp_hw[1]); /* timestampTimerStop  */
    }
    return result;
}

uint32 MIS4_ReadCurTime(void)
{
    uint32 result = 0;
     uint32 cur_timestampTimer = 0;
    if (capture_4_count == 2)
    {
        result  = (capture_4_timestampTimer[0]<<8) | (0xFF & capture_4_Timestamp_hw[0]); /* timestampTimerStart */
        result -= (capture_4_timestampTimer[1]<<8) | (0xFF & capture_4_Timestamp_hw[1]); /* timestampTimerStop  */
    }
    else if (capture_4_count == 1)
    {
        result  = (capture_4_timestampTimer[0]<<8) | (0xFF & capture_4_Timestamp_hw[0]); /* timestampTimerStart */
        uint8 hw_old;
        uint8 hw_new;
        hw_old = Timestamp_ReadCounter();
        cur_timestampTimer = timestampTimer;
        hw_new = Timestamp_ReadCounter();
        if (hw_new > hw_old)
        {
            //hardware overflow
            cur_timestampTimer--;
        }
        result -= (cur_timestampTimer<<8) | (0xFF & hw_new); /* timestampTimerStop  */
    }
    return result;
}

void MIS4_SetBurstTimeout(uint32 t)
{
    BurstTimeout_4_WritePeriod(t);
}

int MIS4_WaitPacket(void)
{
    while (0 == (4 & MIS_Stat_Read()));
    return 0;
}

int MIS4_Measure(uint32 time_ms)
{
    int result;
    
    MIS_Start();
    
    result = MIS4_WaitPacket();
    if (0 != result) return result;
    
    CyDelay(time_ms);
    
    MIS_Stop();
    result = MIS4_WaitPacket();
    if (0 != result) return result;
    
    return result;
}

/******************************************************************************
*******************************************************************************/


/******************************************************************************
* Project Name		: MIS
*******************************************************************************/

#define MIS_RST0 (1)
#define MIS_RST  (2)
#define MIS_CTRL (4)


void MIS_Start(void)
{
    MIS_Reg_Write(MIS_RST0 + MIS_RST);
    CyDelay(1);
    capture_1_count=capture_2_count=capture_3_count=capture_4_count=0;
    PulseCounter_1_WriteCounter(0);
    PulseCounter_2_WriteCounter(0);
    PulseCounter_3_WriteCounter(0);
    PulseCounter_4_WriteCounter(0);
    pulseCounter1 = pulseCounter2 = pulseCounter3 = pulseCounter4 = 0;
    MIS_Reg_Write(0);
}

void MIS_Stop(void)
{
    MIS_Reg_Write(MIS_RST);
    CyDelay(1);
    MIS_Reg_Write(MIS_RST + MIS_CTRL);
    CyDelay(1);
    MIS_Reg_Write(MIS_CTRL);
}

void MIS_SetPulseTimeout(uint32 t)
{
    BurstTimeout_1_WritePeriod(t);
    BurstTimeout_2_WritePeriod(t);
    BurstTimeout_3_WritePeriod(t);
    BurstTimeout_4_WritePeriod(t);
}

int MIS_WaitPacket(void)
{
    while (3 != MIS_Stat_Read());
    return 0;
}

int MIS_Measure(uint32 time_ms)
{
    int result;
    
    MIS_Start();
    
    result = MIS_WaitPacket();
    if (0 != result) return result;
    
    CyDelay(time_ms);
    
    MIS_Stop();
    result = MIS_WaitPacket();
    if (0 != result) return result;
    
    return result;
}

int MIS_PulseCounterStatus()
{   uint8 result;
    
    result = (0xF0u & MIS_Stat_Read());
    result = result >> 4;
    return result;
}

/******************************************************************************
*******************************************************************************/


/* [] END OF FILE */

#ifndef __MBUS_H__
#define __MBUS_H__
    
#include "stdio.h"
    
//#define MAX_WAIT_TIME (330*1000/2400+50)

#define MAX_WAIT_TIME ((uint32)200000)
#define MAX_WAIT_TIME2 ((uint32)200000)

#define MIN_BIT_TIME ((uint32)(4583*0.8))
#define MAX_BIT_TIME ((uint32)(4583*1.2))
    
extern uint8 uart2_tx_buffer[];
extern uint8 uart2_rx_buffer[];
extern uint16 mbus_rx_count;

extern uint32 mbus_tmr_start, mbus_tmr_stop;
extern uint32 mbus_bit_min, mbus_bit_max;

extern uint16 mbus_repeat_count;

extern const uint8 SND_NKE_FRAME[];

extern uint8 mbus_cs(uint8 *buffer, int count);

extern uint8 mbus_snd_nke(uint8 short_addres);
extern uint8 mbus_snd_ud2(uint8 short_addres, const uint8 * user_data, unsigned int lenght);

extern uint8 mbus_req_ud2(uint8 short_addres, uint8 * user_data /* grazina */, unsigned int * lenght /*grazina*/);
#endif

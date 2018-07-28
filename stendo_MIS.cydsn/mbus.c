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
#include "mbus.h"



const uint8 SND_NKE_FRAME[] = {0x10, 0x40, 0xFE, 0x3E, 0x16};



uint8 uart2_tx_buffer[500];
uint8 uart2_rx_buffer[500];
uint16 mbus_rx_count;

uint8 mbus_cs(uint8 * buffer, int count)
{
    int cs = 0;
    while(count > 0)
    {
        cs += *buffer;
        buffer++;
        count--;
    }
    return (cs & 0xFF);
}

uint32 mbus_tmr_start, mbus_tmr_stop;

uint32 mbus_bit_start, mbus_bit_stop;

uint32 mbus_bit_min, mbus_bit_max;

uint16 mbus_repeat_count;

uint8 mbus_send_confirm(const uint8 * buffer, unsigned int lenght)
{
    mbus_repeat_count = 0;
    do {
        mbus_repeat_count++;
        UART_2_ClearTxBuffer();
        UART_2_ClearRxBuffer();
        memcpy(uart2_rx_buffer,0,sizeof(uart2_rx_buffer));
        UART_2_PutArray(buffer, lenght);
        
        while (UART_2_GetTxBufferSize() > 0);
        mbus_tmr_start = Timer_1_ReadCounter();
        do {
            mbus_tmr_stop = Timer_1_ReadCounter();
        } while ((UART_2_GetRxBufferSize() == 0) && ((mbus_tmr_start - mbus_tmr_stop) < MAX_WAIT_TIME));
      
        mbus_rx_count = 0;
        while ((UART_2_GetRxBufferSize() > 0) && (mbus_rx_count < sizeof(uart2_tx_buffer)))
        {
           uart2_rx_buffer[mbus_rx_count] = UART_2_ReadRxData();
           mbus_rx_count++;
        }
        if ((mbus_rx_count == 1) && (uart2_rx_buffer[0] ==0xE5))
            break;
        else
        {
            CyDelay(200); // 330 bit times + 50ms, kai 2400bps
        }
    } while (mbus_repeat_count < 3);
    return ((mbus_rx_count == 1) && (uart2_rx_buffer[0] == 0xE5));
}

uint8 FCB_Bit; //0x20
uint8 mbus_next_record(void)
{
    FCB_Bit ^= 0x20;
}

uint8 mbus_request_respond(uint8 short_addres)
{
    uart2_tx_buffer[0] = 0x10;
    uart2_tx_buffer[1] = 0x5B | FCB_Bit;
    uart2_tx_buffer[2] = short_addres;
    uart2_tx_buffer[3] = uart2_tx_buffer[1] + uart2_tx_buffer[2];
    uart2_tx_buffer[4] = 0x16;
    
    mbus_repeat_count = 0;
    do {
        mbus_repeat_count++;
        UART_2_ClearTxBuffer();
        UART_2_ClearRxBuffer();
        memcpy(uart2_rx_buffer,0,sizeof(uart2_rx_buffer));
        UART_2_PutArray(uart2_tx_buffer, 5);
        
        while (UART_2_GetTxBufferSize() > 0);
        
        mbus_tmr_start = Timer_1_ReadCounter();
        do {
            mbus_tmr_stop = Timer_1_ReadCounter();
        } while ((UART_2_GetRxBufferSize() == 0) && ((mbus_tmr_start - mbus_tmr_stop) < MAX_WAIT_TIME));
        // Pirmas baitas.
        mbus_bit_min = MAX_WAIT_TIME;
        mbus_bit_max = 0;
        
        mbus_rx_count = 0;
        while ((UART_2_GetRxBufferSize() > 0) && (mbus_rx_count < sizeof(uart2_tx_buffer)))
        {
           uart2_rx_buffer[mbus_rx_count] = UART_2_ReadRxData();
           mbus_rx_count++;
           mbus_bit_start = Timer_1_ReadCounter();
           do {
               mbus_bit_stop = Timer_1_ReadCounter();
           } while ((UART_2_GetRxBufferSize() == 0) && ((mbus_bit_start - mbus_bit_stop) < MAX_WAIT_TIME2));
           if (UART_2_GetRxBufferSize() > 0)
           {
              if (mbus_bit_max < (mbus_bit_start - mbus_bit_stop))  mbus_bit_max = (mbus_bit_start - mbus_bit_stop);
              if (mbus_bit_min > (mbus_bit_start - mbus_bit_stop))  mbus_bit_min = (mbus_bit_start - mbus_bit_stop);
           }
        }
        if (
               (mbus_rx_count > 9)
            && (0x68 == uart2_rx_buffer[0])
            && (uart2_rx_buffer[1] == uart2_rx_buffer[2])
            && (0x68 == uart2_rx_buffer[3])
            && (mbus_rx_count == uart2_rx_buffer[1]+6)
            && (mbus_cs((uint8 *)&uart2_rx_buffer[4], uart2_rx_buffer[1]) == uart2_rx_buffer[4+uart2_rx_buffer[1]])
            && (0x16 == uart2_rx_buffer[5+uart2_rx_buffer[1]])
        )
            return 1;
        else
        {
            CyDelay(200); // 330 bit times + 50ms, kai 2400bps
        }
    } while (mbus_repeat_count < 3);
    return 0;
}

uint8 mbus_snd_nke(uint8 short_addres)
{
    FCB_Bit = 0;
    uart2_tx_buffer[0] = 0x10;
    uart2_tx_buffer[1] = 0x40;
    uart2_tx_buffer[2] = short_addres;
    uart2_tx_buffer[3] = uart2_tx_buffer[1] + uart2_tx_buffer[2];
    uart2_tx_buffer[4] = 0x16;
    
    return mbus_send_confirm((const uint8 *)&uart2_tx_buffer,5);
}
uint8 mbus_snd_ud2(uint8 short_addres, const uint8 * user_data, unsigned int lenght)
{
    
}



/* [] END OF FILE */

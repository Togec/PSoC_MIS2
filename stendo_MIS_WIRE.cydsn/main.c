/******************************************************************************
* Project Name		: MinUnit -- a minimal unit testing framework for C
* File Name			: main.c
* Version 			: **
* Device Used		: CY8C5888LTI-LP097
* Software Used		: PSoC Creator 3.1 SP2
* Compiler    		: ARM GCC 4.8.4, ARM RVDS Generic, ARM MDK Generic
* Related Hardware	: CY8CKIT059 PSoC 5 LP Prototyping Kit 
*******************************************************************************/

#include <device.h>
#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "mis.h"
#include "SPI.h"

char txt[500];
uint32 buffer;
uint8 checksum;

CY_ISR(isr_START_handler)
{
   UART_1_PutString("SG START \r\n\r\n");
   MIS_Start();
}

CY_ISR(isr_STOP_handler)
{
   UART_1_PutString("SG STOP \r\n\r\n"); 
   MIS_Stop();
  
}

CY_ISR(isr_CS_Rise_handler)
{
    uint8 b = SPIS_ReadRxData();
    LED1_Write(1);
    sprintf(txt,"RX %d \n",b); 
    assert(0 == 0, txt);
    switch(b)
        {
            case 0x01:
               buffer = MIS1_ReadCount();
             //buffer = 286331153;
            break;
             case 0x02:
               buffer = MIS1_ReadCurTime();
          //  buffer = 572662306;
            break;
            case 0x03:
               buffer = MIS2_ReadCount();
            break;
             case 0x04:
               buffer = MIS2_ReadCurTime();
               break;         
            case 0x09:
               buffer = MIS3_ReadCount();
               break;
            case 0x0A:
               buffer = MIS3_ReadCurTime();
               break;
            case 0x0B:
               buffer = MIS4_ReadCount();
               break;
            case 0x0C:
               buffer = MIS4_ReadCurTime();
               break;
            
            case 0x0D:   //  1 - 2 QuadDecoder
               buffer = QuadDec_1_GetCounter();
               break;
            
            case 0x0E:   //  3 - 4 QuadDecoder
               buffer = QuadDec_2_GetCounter();
               break;
            
            case 0x0F:   //  Read MIS 1-4 Pulse Counter Enable status
               buffer = MIS_PulseCounterStatus();
               break;
        }
        
    SPIS_ClearRxBuffer();
    SPIS_ClearTxBuffer();
    
    uint8 * p = (uint8 *)&buffer;
    SPIS_WriteTxDataZero(0x5Au);
    /* Other 7 bytes are written to the SPIS Tx software buffer */
    SPIS_WriteTxData(p[0]);
    SPIS_WriteTxData(p[1]);
    SPIS_WriteTxData(p[2]);
    SPIS_WriteTxData(p[3]);
    LED1_Write(0);
    sprintf(txt,"TX %x %x %x %x \n",p[0],p[1],p[2],p[3]); 
    assert(0 == 0, txt);
    
}

CY_ISR(isr_QuadDec_1_handler)
{
    /* Clear Inerrupt */
   	QuadDec_1_Init(); //Initializes or restores default configuration provided with the customizer
}    

CY_ISR(isr_QuadDec_2_handler)
{
    QuadDec_2_Init();
}  


void debug_master_cmd(uint8 cmd)
{
    uint8 spi_data[16];
    SPIM_ClearRxBuffer();
    SPIM_ClearTxBuffer();
    memcpy(spi_data,0,sizeof(spi_data));
    spi_data[0] = cmd;
   // SPIM_CS_Write(0);
    SPIM_PutArray(spi_data, 5);
    CyDelay(1);
    //SPIM_CS_Write(1);
}

uint32 debug_master_read(uint8 cmd)
{
    uint8 spi_data[16];
    uint32 result = 0xFFFFFFFF;
    uint8 *p = (uint8 *)&result;
    
    SPIM_ClearRxBuffer();
    SPIM_ClearTxBuffer();
    memcpy(spi_data,0,sizeof(spi_data));
    spi_data[0] = cmd;
  //  SPIM_CS_Write(0);
    SPIM_PutArray(spi_data, 5);
    CyDelay(1);
   // SPIM_CS_Write(1);
    int b_cnt = SPIM_GetRxBufferSize();
    if (b_cnt == 5)
    {
        int i;
        uint8 signature = SPIM_ReadByte();
        if (signature == 0x5A)
        {
            for (i=0; i < 4; i++)
            {
                p[i] = SPIM_ReadByte();
            }
        }
    }
    return  result;
}
    
int main()
{    
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Start the components */
    
    SPIM_Start();
    SPIS_Start();
    UART_1_Start();
    QuadDec_1_Start();
    QuadDec_2_Start();

  //  isr_SPI_StartEx(isr_SPI_handler);
    isr_CS_Rise_StartEx(isr_CS_Rise_handler);
        
    isr_START_StartEx(isr_START_handler);
    isr_STOP_StartEx(isr_STOP_handler);
    
    
    

    /* Quadrature Decoder isr */
    isr_QuadDec_1_StartEx(isr_QuadDec_1_handler);
    isr_QuadDec_2_StartEx(isr_QuadDec_2_handler);
   
    
    
    /* MIS 1------------------------------------------ */
    isr_PulseCounter_1_StartEx(isr_PulseCounter_1_handler);
    isr_Capture_1_StartEx(isr_Capture_1);
     BurstTimeout_1_Start();
    PulseCounter_1_Start();
   
    /* MIS 2------------------------------------------ */
    isr_PulseCounter_2_StartEx(isr_PulseCounter_2_handler);
    isr_Capture_2_StartEx(isr_Capture_2);
    PulseCounter_2_Start();
    BurstTimeout_2_Start();
    
    /* MIS 3------------------------------------------ */
    isr_PulseCounter_3_StartEx(isr_PulseCounter_3_handler);
    isr_Capture_3_StartEx(isr_Capture_3);
    PulseCounter_3_Start();
    BurstTimeout_3_Start();
    
    /* MIS 4------------------------------------------ */
    isr_PulseCounter_4_StartEx(isr_PulseCounter_4_handler);
    isr_Capture_4_StartEx(isr_Capture_4);
    PulseCounter_4_Start();
    BurstTimeout_4_Start();
    
    
    isr_Timestamp_StartEx(isr_Timestamp_handler);
    Timestamp_Start();
  //  EdgeDetect_1_Start();

    
    UART_1_PutString("\x1b[2J\x1b[H"); //erase screen and go home
    UART_1_PutString("A minimal unit testing framework for C\r\n\r\n");

    //test_X10();
    MIS1_SetBurstTimeout(5000);
    MIS2_SetBurstTimeout(5000); /* 5ms pulse timeout in packet */
    MIS3_SetBurstTimeout(5000);
    MIS4_SetBurstTimeout(5000);
    do
    {
   //     MIS_Debug_Write(1);
     //   UART_1_PutString("DEBUG 1 \r\n\r\n");
    //    CyDelay(60000);
        
    //    MIS_Debug_Write(0);
    //    UART_1_PutString("DEBUG 0 \r\n\r\n");

        
        /* --- MIS 1 --- */
        uint32 MIS1_pulse_count;
        uint32 MIS1_pulse_time;
        do
        {
            debug_master_cmd(1);
            MIS1_pulse_count = debug_master_read(1);
            
            debug_master_cmd(2);
            MIS1_pulse_time = debug_master_read(2);            
        } while (MIS1_pulse_time == 0);
        //////////////////////////////////////////
        
        /* --- MIS 2 --- */
        uint32 MIS2_pulse_count;
        uint32 MIS2_pulse_time;
        do
        {
            debug_master_cmd(3);
            MIS2_pulse_count = debug_master_read(3);

            debug_master_cmd(4);
            MIS2_pulse_time = debug_master_read(4);
        } while (MIS2_pulse_time == 0);
         //////////////////////////////////////////
        
        /* --- MIS 3 --- */
        uint32 MIS3_pulse_count;
        uint32 MIS3_pulse_time;
        do
        {
            debug_master_cmd(9);
            MIS3_pulse_count = debug_master_read(9);
            
            debug_master_cmd(0x0A);
            MIS3_pulse_time = debug_master_read(0x0A);            
        } while (MIS3_pulse_time == 0);
         //////////////////////////////////////////
        
        /* --- MIS 4 --- */
        uint32 MIS4_pulse_count;
        uint32 MIS4_pulse_time;
        do
        {
            debug_master_cmd(0x0B);
            MIS4_pulse_count = debug_master_read(0x0B);
            
            debug_master_cmd(0x0C);
            MIS4_pulse_time = debug_master_read(0x0C);            
        } while (MIS4_pulse_time == 0);
         //////////////////////////////////////////
        
        /* --- MIS Quad 1-2 --- */
        uint32 Quad_dec_1_count;
        uint8 Quad_Dec_1_Event;
        
        do
        {
            debug_master_cmd(0x0D);
            Quad_dec_1_count = debug_master_read(0x0D);
            Quad_Dec_1_Event = QuadDec_1_GetEvents();
            
            debug_master_cmd(2);
            MIS1_pulse_time = debug_master_read(2);  
            
        } while (MIS1_pulse_time == 0);
        //////////////////////////////////////////
        
        /* --- MIS Quad 3-4 --- */
        uint32 Quad_dec_2_count;
        uint8 Quad_Dec_2_Event;
        
        do
        {
            debug_master_cmd(0x0E);
            Quad_dec_2_count = debug_master_read(0x0E);
            Quad_Dec_2_Event = QuadDec_2_GetEvents();
            
            debug_master_cmd(0x0A);
            MIS3_pulse_time = debug_master_read(0x0A);            
        } while (MIS3_pulse_time == 0);
        //////////////////////////////////////////
        
         /*
        sprintf(txt, "MIS1 PulseCounter = %ld TotTime = %ld", MIS1_pulse_count, MIS1_pulse_time);
        assert(0 == 0, txt);
        CyDelay(1000);
            
        sprintf(txt, "MIS2 PulseCounter = %ld TotTime = %ld", MIS2_pulse_count, MIS2_pulse_time);
        assert(0 == 0, txt);
        
        sprintf(txt, "MIS3 PulseCounter = %ld TotTime = %ld", MIS3_pulse_count, MIS3_pulse_time);
        assert(0 == 0, txt);
             
        sprintf(txt, "MIS4 PulseCounter = %ld TotTime = %ld", MIS4_pulse_count, MIS4_pulse_time);
        assert(0 == 0, txt);
        
        sprintf(txt, "MIS 1-2 QuadCounter = %ld TotTime = %ld Event = %d", Quad_dec_1_count, MIS1_pulse_time,Quad_Dec_1_Event);
        assert(0 == 0, txt);
        
        sprintf(txt, "MIS 3-4 QuadCounter = %ld TotTime = %ld Event = %d", Quad_dec_2_count, MIS3_pulse_time, Quad_Dec_2_Event);
        assert(0 == 0, txt);
       */
        
    } while (1);
}

/* [] END OF FILE */

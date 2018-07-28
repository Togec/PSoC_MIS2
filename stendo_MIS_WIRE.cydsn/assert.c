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
#include "stdio.h"


char text[500];

void __assert__(int test, char msg[], char file[], int line)
{
    if (test)
       sprintf(text, "PASSED %s, %d, %s\r\n", file, line, msg);
    else
       sprintf(text, "FAILED %s, %d, %s\r\n", file, line, msg);
    UART_1_PutString(text);
}

/* [] END OF FILE */

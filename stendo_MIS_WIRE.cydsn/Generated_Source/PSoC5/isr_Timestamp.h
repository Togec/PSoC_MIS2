/*******************************************************************************
* File Name: isr_Timestamp.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_Timestamp_H)
#define CY_ISR_isr_Timestamp_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_Timestamp_Start(void);
void isr_Timestamp_StartEx(cyisraddress address);
void isr_Timestamp_Stop(void);

CY_ISR_PROTO(isr_Timestamp_Interrupt);

void isr_Timestamp_SetVector(cyisraddress address);
cyisraddress isr_Timestamp_GetVector(void);

void isr_Timestamp_SetPriority(uint8 priority);
uint8 isr_Timestamp_GetPriority(void);

void isr_Timestamp_Enable(void);
uint8 isr_Timestamp_GetState(void);
void isr_Timestamp_Disable(void);

void isr_Timestamp_SetPending(void);
void isr_Timestamp_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_Timestamp ISR. */
#define isr_Timestamp_INTC_VECTOR            ((reg32 *) isr_Timestamp__INTC_VECT)

/* Address of the isr_Timestamp ISR priority. */
#define isr_Timestamp_INTC_PRIOR             ((reg8 *) isr_Timestamp__INTC_PRIOR_REG)

/* Priority of the isr_Timestamp interrupt. */
#define isr_Timestamp_INTC_PRIOR_NUMBER      isr_Timestamp__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_Timestamp interrupt. */
#define isr_Timestamp_INTC_SET_EN            ((reg32 *) isr_Timestamp__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_Timestamp interrupt. */
#define isr_Timestamp_INTC_CLR_EN            ((reg32 *) isr_Timestamp__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_Timestamp interrupt state to pending. */
#define isr_Timestamp_INTC_SET_PD            ((reg32 *) isr_Timestamp__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_Timestamp interrupt. */
#define isr_Timestamp_INTC_CLR_PD            ((reg32 *) isr_Timestamp__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_Timestamp_H */


/* [] END OF FILE */

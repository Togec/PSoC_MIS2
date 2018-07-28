/*******************************************************************************
* File Name: MIS_Stat.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MIS_Stat.h"

#if !defined(MIS_Stat_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: MIS_Stat_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 MIS_Stat_Read(void) 
{ 
    return MIS_Stat_Status;
}


/*******************************************************************************
* Function Name: MIS_Stat_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MIS_Stat_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    MIS_Stat_Status_Aux_Ctrl |= MIS_Stat_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: MIS_Stat_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MIS_Stat_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    MIS_Stat_Status_Aux_Ctrl &= (uint8)(~MIS_Stat_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: MIS_Stat_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void MIS_Stat_WriteMask(uint8 mask) 
{
    #if(MIS_Stat_INPUTS < 8u)
    	mask &= ((uint8)(1u << MIS_Stat_INPUTS) - 1u);
	#endif /* End MIS_Stat_INPUTS < 8u */
    MIS_Stat_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: MIS_Stat_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 MIS_Stat_ReadMask(void) 
{
    return MIS_Stat_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */

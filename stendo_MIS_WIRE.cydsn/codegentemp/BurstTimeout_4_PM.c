/*******************************************************************************
* File Name: BurstTimeout_4_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "BurstTimeout_4.h"

static BurstTimeout_4_backupStruct BurstTimeout_4_backup;


/*******************************************************************************
* Function Name: BurstTimeout_4_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BurstTimeout_4_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BurstTimeout_4_SaveConfig(void) 
{
    #if (!BurstTimeout_4_UsingFixedFunction)
        BurstTimeout_4_backup.TimerUdb = BurstTimeout_4_ReadCounter();
        BurstTimeout_4_backup.InterruptMaskValue = BurstTimeout_4_STATUS_MASK;
        #if (BurstTimeout_4_UsingHWCaptureCounter)
            BurstTimeout_4_backup.TimerCaptureCounter = BurstTimeout_4_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!BurstTimeout_4_UDB_CONTROL_REG_REMOVED)
            BurstTimeout_4_backup.TimerControlRegister = BurstTimeout_4_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: BurstTimeout_4_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BurstTimeout_4_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BurstTimeout_4_RestoreConfig(void) 
{   
    #if (!BurstTimeout_4_UsingFixedFunction)

        BurstTimeout_4_WriteCounter(BurstTimeout_4_backup.TimerUdb);
        BurstTimeout_4_STATUS_MASK =BurstTimeout_4_backup.InterruptMaskValue;
        #if (BurstTimeout_4_UsingHWCaptureCounter)
            BurstTimeout_4_SetCaptureCount(BurstTimeout_4_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!BurstTimeout_4_UDB_CONTROL_REG_REMOVED)
            BurstTimeout_4_WriteControlRegister(BurstTimeout_4_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: BurstTimeout_4_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BurstTimeout_4_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void BurstTimeout_4_Sleep(void) 
{
    #if(!BurstTimeout_4_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(BurstTimeout_4_CTRL_ENABLE == (BurstTimeout_4_CONTROL & BurstTimeout_4_CTRL_ENABLE))
        {
            /* Timer is enabled */
            BurstTimeout_4_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            BurstTimeout_4_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    BurstTimeout_4_Stop();
    BurstTimeout_4_SaveConfig();
}


/*******************************************************************************
* Function Name: BurstTimeout_4_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BurstTimeout_4_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BurstTimeout_4_Wakeup(void) 
{
    BurstTimeout_4_RestoreConfig();
    #if(!BurstTimeout_4_UDB_CONTROL_REG_REMOVED)
        if(BurstTimeout_4_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                BurstTimeout_4_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

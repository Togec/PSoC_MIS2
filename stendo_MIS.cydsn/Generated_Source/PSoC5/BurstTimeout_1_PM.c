/*******************************************************************************
* File Name: BurstTimeout_1_PM.c
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

#include "BurstTimeout_1.h"

static BurstTimeout_1_backupStruct BurstTimeout_1_backup;


/*******************************************************************************
* Function Name: BurstTimeout_1_SaveConfig
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
*  BurstTimeout_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BurstTimeout_1_SaveConfig(void) 
{
    #if (!BurstTimeout_1_UsingFixedFunction)
        BurstTimeout_1_backup.TimerUdb = BurstTimeout_1_ReadCounter();
        BurstTimeout_1_backup.InterruptMaskValue = BurstTimeout_1_STATUS_MASK;
        #if (BurstTimeout_1_UsingHWCaptureCounter)
            BurstTimeout_1_backup.TimerCaptureCounter = BurstTimeout_1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!BurstTimeout_1_UDB_CONTROL_REG_REMOVED)
            BurstTimeout_1_backup.TimerControlRegister = BurstTimeout_1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: BurstTimeout_1_RestoreConfig
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
*  BurstTimeout_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BurstTimeout_1_RestoreConfig(void) 
{   
    #if (!BurstTimeout_1_UsingFixedFunction)

        BurstTimeout_1_WriteCounter(BurstTimeout_1_backup.TimerUdb);
        BurstTimeout_1_STATUS_MASK =BurstTimeout_1_backup.InterruptMaskValue;
        #if (BurstTimeout_1_UsingHWCaptureCounter)
            BurstTimeout_1_SetCaptureCount(BurstTimeout_1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!BurstTimeout_1_UDB_CONTROL_REG_REMOVED)
            BurstTimeout_1_WriteControlRegister(BurstTimeout_1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: BurstTimeout_1_Sleep
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
*  BurstTimeout_1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void BurstTimeout_1_Sleep(void) 
{
    #if(!BurstTimeout_1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(BurstTimeout_1_CTRL_ENABLE == (BurstTimeout_1_CONTROL & BurstTimeout_1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            BurstTimeout_1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            BurstTimeout_1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    BurstTimeout_1_Stop();
    BurstTimeout_1_SaveConfig();
}


/*******************************************************************************
* Function Name: BurstTimeout_1_Wakeup
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
*  BurstTimeout_1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BurstTimeout_1_Wakeup(void) 
{
    BurstTimeout_1_RestoreConfig();
    #if(!BurstTimeout_1_UDB_CONTROL_REG_REMOVED)
        if(BurstTimeout_1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                BurstTimeout_1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

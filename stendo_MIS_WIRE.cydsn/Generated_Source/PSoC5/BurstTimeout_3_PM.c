/*******************************************************************************
* File Name: BurstTimeout_3_PM.c
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

#include "BurstTimeout_3.h"

static BurstTimeout_3_backupStruct BurstTimeout_3_backup;


/*******************************************************************************
* Function Name: BurstTimeout_3_SaveConfig
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
*  BurstTimeout_3_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BurstTimeout_3_SaveConfig(void) 
{
    #if (!BurstTimeout_3_UsingFixedFunction)
        BurstTimeout_3_backup.TimerUdb = BurstTimeout_3_ReadCounter();
        BurstTimeout_3_backup.InterruptMaskValue = BurstTimeout_3_STATUS_MASK;
        #if (BurstTimeout_3_UsingHWCaptureCounter)
            BurstTimeout_3_backup.TimerCaptureCounter = BurstTimeout_3_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!BurstTimeout_3_UDB_CONTROL_REG_REMOVED)
            BurstTimeout_3_backup.TimerControlRegister = BurstTimeout_3_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: BurstTimeout_3_RestoreConfig
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
*  BurstTimeout_3_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BurstTimeout_3_RestoreConfig(void) 
{   
    #if (!BurstTimeout_3_UsingFixedFunction)

        BurstTimeout_3_WriteCounter(BurstTimeout_3_backup.TimerUdb);
        BurstTimeout_3_STATUS_MASK =BurstTimeout_3_backup.InterruptMaskValue;
        #if (BurstTimeout_3_UsingHWCaptureCounter)
            BurstTimeout_3_SetCaptureCount(BurstTimeout_3_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!BurstTimeout_3_UDB_CONTROL_REG_REMOVED)
            BurstTimeout_3_WriteControlRegister(BurstTimeout_3_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: BurstTimeout_3_Sleep
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
*  BurstTimeout_3_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void BurstTimeout_3_Sleep(void) 
{
    #if(!BurstTimeout_3_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(BurstTimeout_3_CTRL_ENABLE == (BurstTimeout_3_CONTROL & BurstTimeout_3_CTRL_ENABLE))
        {
            /* Timer is enabled */
            BurstTimeout_3_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            BurstTimeout_3_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    BurstTimeout_3_Stop();
    BurstTimeout_3_SaveConfig();
}


/*******************************************************************************
* Function Name: BurstTimeout_3_Wakeup
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
*  BurstTimeout_3_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BurstTimeout_3_Wakeup(void) 
{
    BurstTimeout_3_RestoreConfig();
    #if(!BurstTimeout_3_UDB_CONTROL_REG_REMOVED)
        if(BurstTimeout_3_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                BurstTimeout_3_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

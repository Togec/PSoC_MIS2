/*******************************************************************************
* File Name: BurstTimeout_2_PM.c
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

#include "BurstTimeout_2.h"

static BurstTimeout_2_backupStruct BurstTimeout_2_backup;


/*******************************************************************************
* Function Name: BurstTimeout_2_SaveConfig
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
*  BurstTimeout_2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BurstTimeout_2_SaveConfig(void) 
{
    #if (!BurstTimeout_2_UsingFixedFunction)
        BurstTimeout_2_backup.TimerUdb = BurstTimeout_2_ReadCounter();
        BurstTimeout_2_backup.InterruptMaskValue = BurstTimeout_2_STATUS_MASK;
        #if (BurstTimeout_2_UsingHWCaptureCounter)
            BurstTimeout_2_backup.TimerCaptureCounter = BurstTimeout_2_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!BurstTimeout_2_UDB_CONTROL_REG_REMOVED)
            BurstTimeout_2_backup.TimerControlRegister = BurstTimeout_2_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: BurstTimeout_2_RestoreConfig
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
*  BurstTimeout_2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BurstTimeout_2_RestoreConfig(void) 
{   
    #if (!BurstTimeout_2_UsingFixedFunction)

        BurstTimeout_2_WriteCounter(BurstTimeout_2_backup.TimerUdb);
        BurstTimeout_2_STATUS_MASK =BurstTimeout_2_backup.InterruptMaskValue;
        #if (BurstTimeout_2_UsingHWCaptureCounter)
            BurstTimeout_2_SetCaptureCount(BurstTimeout_2_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!BurstTimeout_2_UDB_CONTROL_REG_REMOVED)
            BurstTimeout_2_WriteControlRegister(BurstTimeout_2_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: BurstTimeout_2_Sleep
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
*  BurstTimeout_2_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void BurstTimeout_2_Sleep(void) 
{
    #if(!BurstTimeout_2_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(BurstTimeout_2_CTRL_ENABLE == (BurstTimeout_2_CONTROL & BurstTimeout_2_CTRL_ENABLE))
        {
            /* Timer is enabled */
            BurstTimeout_2_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            BurstTimeout_2_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    BurstTimeout_2_Stop();
    BurstTimeout_2_SaveConfig();
}


/*******************************************************************************
* Function Name: BurstTimeout_2_Wakeup
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
*  BurstTimeout_2_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BurstTimeout_2_Wakeup(void) 
{
    BurstTimeout_2_RestoreConfig();
    #if(!BurstTimeout_2_UDB_CONTROL_REG_REMOVED)
        if(BurstTimeout_2_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                BurstTimeout_2_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

/*******************************************************************************
* File Name: Timestamp_PM.c
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

#include "Timestamp.h"

static Timestamp_backupStruct Timestamp_backup;


/*******************************************************************************
* Function Name: Timestamp_SaveConfig
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
*  Timestamp_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timestamp_SaveConfig(void) 
{
    #if (!Timestamp_UsingFixedFunction)
        Timestamp_backup.TimerUdb = Timestamp_ReadCounter();
        Timestamp_backup.InterruptMaskValue = Timestamp_STATUS_MASK;
        #if (Timestamp_UsingHWCaptureCounter)
            Timestamp_backup.TimerCaptureCounter = Timestamp_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timestamp_UDB_CONTROL_REG_REMOVED)
            Timestamp_backup.TimerControlRegister = Timestamp_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timestamp_RestoreConfig
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
*  Timestamp_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timestamp_RestoreConfig(void) 
{   
    #if (!Timestamp_UsingFixedFunction)

        Timestamp_WriteCounter(Timestamp_backup.TimerUdb);
        Timestamp_STATUS_MASK =Timestamp_backup.InterruptMaskValue;
        #if (Timestamp_UsingHWCaptureCounter)
            Timestamp_SetCaptureCount(Timestamp_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timestamp_UDB_CONTROL_REG_REMOVED)
            Timestamp_WriteControlRegister(Timestamp_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timestamp_Sleep
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
*  Timestamp_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timestamp_Sleep(void) 
{
    #if(!Timestamp_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timestamp_CTRL_ENABLE == (Timestamp_CONTROL & Timestamp_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timestamp_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timestamp_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timestamp_Stop();
    Timestamp_SaveConfig();
}


/*******************************************************************************
* Function Name: Timestamp_Wakeup
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
*  Timestamp_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timestamp_Wakeup(void) 
{
    Timestamp_RestoreConfig();
    #if(!Timestamp_UDB_CONTROL_REG_REMOVED)
        if(Timestamp_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timestamp_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

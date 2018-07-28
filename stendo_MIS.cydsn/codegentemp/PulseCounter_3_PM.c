/*******************************************************************************
* File Name: PulseCounter_3_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PulseCounter_3.h"

static PulseCounter_3_backupStruct PulseCounter_3_backup;


/*******************************************************************************
* Function Name: PulseCounter_3_SaveConfig
********************************************************************************
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
*  PulseCounter_3_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PulseCounter_3_SaveConfig(void) 
{
    #if (!PulseCounter_3_UsingFixedFunction)

        PulseCounter_3_backup.CounterUdb = PulseCounter_3_ReadCounter();

        #if(!PulseCounter_3_ControlRegRemoved)
            PulseCounter_3_backup.CounterControlRegister = PulseCounter_3_ReadControlRegister();
        #endif /* (!PulseCounter_3_ControlRegRemoved) */

    #endif /* (!PulseCounter_3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_3_RestoreConfig
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
*  PulseCounter_3_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PulseCounter_3_RestoreConfig(void) 
{      
    #if (!PulseCounter_3_UsingFixedFunction)

       PulseCounter_3_WriteCounter(PulseCounter_3_backup.CounterUdb);

        #if(!PulseCounter_3_ControlRegRemoved)
            PulseCounter_3_WriteControlRegister(PulseCounter_3_backup.CounterControlRegister);
        #endif /* (!PulseCounter_3_ControlRegRemoved) */

    #endif /* (!PulseCounter_3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_3_Sleep
********************************************************************************
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
*  PulseCounter_3_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PulseCounter_3_Sleep(void) 
{
    #if(!PulseCounter_3_ControlRegRemoved)
        /* Save Counter's enable state */
        if(PulseCounter_3_CTRL_ENABLE == (PulseCounter_3_CONTROL & PulseCounter_3_CTRL_ENABLE))
        {
            /* Counter is enabled */
            PulseCounter_3_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            PulseCounter_3_backup.CounterEnableState = 0u;
        }
    #else
        PulseCounter_3_backup.CounterEnableState = 1u;
        if(PulseCounter_3_backup.CounterEnableState != 0u)
        {
            PulseCounter_3_backup.CounterEnableState = 0u;
        }
    #endif /* (!PulseCounter_3_ControlRegRemoved) */
    
    PulseCounter_3_Stop();
    PulseCounter_3_SaveConfig();
}


/*******************************************************************************
* Function Name: PulseCounter_3_Wakeup
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
*  PulseCounter_3_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PulseCounter_3_Wakeup(void) 
{
    PulseCounter_3_RestoreConfig();
    #if(!PulseCounter_3_ControlRegRemoved)
        if(PulseCounter_3_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            PulseCounter_3_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!PulseCounter_3_ControlRegRemoved) */
    
}


/* [] END OF FILE */

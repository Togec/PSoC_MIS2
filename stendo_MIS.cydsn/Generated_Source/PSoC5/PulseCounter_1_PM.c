/*******************************************************************************
* File Name: PulseCounter_1_PM.c  
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

#include "PulseCounter_1.h"

static PulseCounter_1_backupStruct PulseCounter_1_backup;


/*******************************************************************************
* Function Name: PulseCounter_1_SaveConfig
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
*  PulseCounter_1_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PulseCounter_1_SaveConfig(void) 
{
    #if (!PulseCounter_1_UsingFixedFunction)

        PulseCounter_1_backup.CounterUdb = PulseCounter_1_ReadCounter();

        #if(!PulseCounter_1_ControlRegRemoved)
            PulseCounter_1_backup.CounterControlRegister = PulseCounter_1_ReadControlRegister();
        #endif /* (!PulseCounter_1_ControlRegRemoved) */

    #endif /* (!PulseCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_1_RestoreConfig
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
*  PulseCounter_1_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PulseCounter_1_RestoreConfig(void) 
{      
    #if (!PulseCounter_1_UsingFixedFunction)

       PulseCounter_1_WriteCounter(PulseCounter_1_backup.CounterUdb);

        #if(!PulseCounter_1_ControlRegRemoved)
            PulseCounter_1_WriteControlRegister(PulseCounter_1_backup.CounterControlRegister);
        #endif /* (!PulseCounter_1_ControlRegRemoved) */

    #endif /* (!PulseCounter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_1_Sleep
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
*  PulseCounter_1_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PulseCounter_1_Sleep(void) 
{
    #if(!PulseCounter_1_ControlRegRemoved)
        /* Save Counter's enable state */
        if(PulseCounter_1_CTRL_ENABLE == (PulseCounter_1_CONTROL & PulseCounter_1_CTRL_ENABLE))
        {
            /* Counter is enabled */
            PulseCounter_1_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            PulseCounter_1_backup.CounterEnableState = 0u;
        }
    #else
        PulseCounter_1_backup.CounterEnableState = 1u;
        if(PulseCounter_1_backup.CounterEnableState != 0u)
        {
            PulseCounter_1_backup.CounterEnableState = 0u;
        }
    #endif /* (!PulseCounter_1_ControlRegRemoved) */
    
    PulseCounter_1_Stop();
    PulseCounter_1_SaveConfig();
}


/*******************************************************************************
* Function Name: PulseCounter_1_Wakeup
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
*  PulseCounter_1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PulseCounter_1_Wakeup(void) 
{
    PulseCounter_1_RestoreConfig();
    #if(!PulseCounter_1_ControlRegRemoved)
        if(PulseCounter_1_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            PulseCounter_1_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!PulseCounter_1_ControlRegRemoved) */
    
}


/* [] END OF FILE */

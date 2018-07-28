/*******************************************************************************
* File Name: PulseCounter_4_PM.c  
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

#include "PulseCounter_4.h"

static PulseCounter_4_backupStruct PulseCounter_4_backup;


/*******************************************************************************
* Function Name: PulseCounter_4_SaveConfig
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
*  PulseCounter_4_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PulseCounter_4_SaveConfig(void) 
{
    #if (!PulseCounter_4_UsingFixedFunction)

        PulseCounter_4_backup.CounterUdb = PulseCounter_4_ReadCounter();

        #if(!PulseCounter_4_ControlRegRemoved)
            PulseCounter_4_backup.CounterControlRegister = PulseCounter_4_ReadControlRegister();
        #endif /* (!PulseCounter_4_ControlRegRemoved) */

    #endif /* (!PulseCounter_4_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_4_RestoreConfig
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
*  PulseCounter_4_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PulseCounter_4_RestoreConfig(void) 
{      
    #if (!PulseCounter_4_UsingFixedFunction)

       PulseCounter_4_WriteCounter(PulseCounter_4_backup.CounterUdb);

        #if(!PulseCounter_4_ControlRegRemoved)
            PulseCounter_4_WriteControlRegister(PulseCounter_4_backup.CounterControlRegister);
        #endif /* (!PulseCounter_4_ControlRegRemoved) */

    #endif /* (!PulseCounter_4_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_4_Sleep
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
*  PulseCounter_4_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PulseCounter_4_Sleep(void) 
{
    #if(!PulseCounter_4_ControlRegRemoved)
        /* Save Counter's enable state */
        if(PulseCounter_4_CTRL_ENABLE == (PulseCounter_4_CONTROL & PulseCounter_4_CTRL_ENABLE))
        {
            /* Counter is enabled */
            PulseCounter_4_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            PulseCounter_4_backup.CounterEnableState = 0u;
        }
    #else
        PulseCounter_4_backup.CounterEnableState = 1u;
        if(PulseCounter_4_backup.CounterEnableState != 0u)
        {
            PulseCounter_4_backup.CounterEnableState = 0u;
        }
    #endif /* (!PulseCounter_4_ControlRegRemoved) */
    
    PulseCounter_4_Stop();
    PulseCounter_4_SaveConfig();
}


/*******************************************************************************
* Function Name: PulseCounter_4_Wakeup
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
*  PulseCounter_4_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PulseCounter_4_Wakeup(void) 
{
    PulseCounter_4_RestoreConfig();
    #if(!PulseCounter_4_ControlRegRemoved)
        if(PulseCounter_4_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            PulseCounter_4_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!PulseCounter_4_ControlRegRemoved) */
    
}


/* [] END OF FILE */

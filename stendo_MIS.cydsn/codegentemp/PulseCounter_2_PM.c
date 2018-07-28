/*******************************************************************************
* File Name: PulseCounter_2_PM.c  
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

#include "PulseCounter_2.h"

static PulseCounter_2_backupStruct PulseCounter_2_backup;


/*******************************************************************************
* Function Name: PulseCounter_2_SaveConfig
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
*  PulseCounter_2_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PulseCounter_2_SaveConfig(void) 
{
    #if (!PulseCounter_2_UsingFixedFunction)

        PulseCounter_2_backup.CounterUdb = PulseCounter_2_ReadCounter();

        #if(!PulseCounter_2_ControlRegRemoved)
            PulseCounter_2_backup.CounterControlRegister = PulseCounter_2_ReadControlRegister();
        #endif /* (!PulseCounter_2_ControlRegRemoved) */

    #endif /* (!PulseCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_2_RestoreConfig
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
*  PulseCounter_2_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PulseCounter_2_RestoreConfig(void) 
{      
    #if (!PulseCounter_2_UsingFixedFunction)

       PulseCounter_2_WriteCounter(PulseCounter_2_backup.CounterUdb);

        #if(!PulseCounter_2_ControlRegRemoved)
            PulseCounter_2_WriteControlRegister(PulseCounter_2_backup.CounterControlRegister);
        #endif /* (!PulseCounter_2_ControlRegRemoved) */

    #endif /* (!PulseCounter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_2_Sleep
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
*  PulseCounter_2_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PulseCounter_2_Sleep(void) 
{
    #if(!PulseCounter_2_ControlRegRemoved)
        /* Save Counter's enable state */
        if(PulseCounter_2_CTRL_ENABLE == (PulseCounter_2_CONTROL & PulseCounter_2_CTRL_ENABLE))
        {
            /* Counter is enabled */
            PulseCounter_2_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            PulseCounter_2_backup.CounterEnableState = 0u;
        }
    #else
        PulseCounter_2_backup.CounterEnableState = 1u;
        if(PulseCounter_2_backup.CounterEnableState != 0u)
        {
            PulseCounter_2_backup.CounterEnableState = 0u;
        }
    #endif /* (!PulseCounter_2_ControlRegRemoved) */
    
    PulseCounter_2_Stop();
    PulseCounter_2_SaveConfig();
}


/*******************************************************************************
* Function Name: PulseCounter_2_Wakeup
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
*  PulseCounter_2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PulseCounter_2_Wakeup(void) 
{
    PulseCounter_2_RestoreConfig();
    #if(!PulseCounter_2_ControlRegRemoved)
        if(PulseCounter_2_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            PulseCounter_2_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!PulseCounter_2_ControlRegRemoved) */
    
}


/* [] END OF FILE */

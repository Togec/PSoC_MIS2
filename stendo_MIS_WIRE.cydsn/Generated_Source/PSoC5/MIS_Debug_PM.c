/*******************************************************************************
* File Name: MIS_Debug_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MIS_Debug.h"

/* Check for removal by optimization */
#if !defined(MIS_Debug_Sync_ctrl_reg__REMOVED)

static MIS_Debug_BACKUP_STRUCT  MIS_Debug_backup = {0u};

    
/*******************************************************************************
* Function Name: MIS_Debug_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MIS_Debug_SaveConfig(void) 
{
    MIS_Debug_backup.controlState = MIS_Debug_Control;
}


/*******************************************************************************
* Function Name: MIS_Debug_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void MIS_Debug_RestoreConfig(void) 
{
     MIS_Debug_Control = MIS_Debug_backup.controlState;
}


/*******************************************************************************
* Function Name: MIS_Debug_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MIS_Debug_Sleep(void) 
{
    MIS_Debug_SaveConfig();
}


/*******************************************************************************
* Function Name: MIS_Debug_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MIS_Debug_Wakeup(void)  
{
    MIS_Debug_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */

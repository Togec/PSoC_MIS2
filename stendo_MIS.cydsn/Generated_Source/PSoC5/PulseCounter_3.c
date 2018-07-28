/*******************************************************************************
* File Name: PulseCounter_3.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 PulseCounter_3_initVar = 0u;


/*******************************************************************************
* Function Name: PulseCounter_3_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void PulseCounter_3_Init(void) 
{
        #if (!PulseCounter_3_UsingFixedFunction && !PulseCounter_3_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!PulseCounter_3_UsingFixedFunction && !PulseCounter_3_ControlRegRemoved) */
        
        #if(!PulseCounter_3_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 PulseCounter_3_interruptState;
        #endif /* (!PulseCounter_3_UsingFixedFunction) */
        
        #if (PulseCounter_3_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            PulseCounter_3_CONTROL &= PulseCounter_3_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                PulseCounter_3_CONTROL2 &= ((uint8)(~PulseCounter_3_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                PulseCounter_3_CONTROL3 &= ((uint8)(~PulseCounter_3_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (PulseCounter_3_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                PulseCounter_3_CONTROL |= PulseCounter_3_ONESHOT;
            #endif /* (PulseCounter_3_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            PulseCounter_3_CONTROL2 |= PulseCounter_3_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            PulseCounter_3_RT1 &= ((uint8)(~PulseCounter_3_RT1_MASK));
            PulseCounter_3_RT1 |= PulseCounter_3_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            PulseCounter_3_RT1 &= ((uint8)(~PulseCounter_3_SYNCDSI_MASK));
            PulseCounter_3_RT1 |= PulseCounter_3_SYNCDSI_EN;

        #else
            #if(!PulseCounter_3_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = PulseCounter_3_CONTROL & ((uint8)(~PulseCounter_3_CTRL_CMPMODE_MASK));
            PulseCounter_3_CONTROL = ctrl | PulseCounter_3_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = PulseCounter_3_CONTROL & ((uint8)(~PulseCounter_3_CTRL_CAPMODE_MASK));
            
            #if( 0 != PulseCounter_3_CAPTURE_MODE_CONF)
                PulseCounter_3_CONTROL = ctrl | PulseCounter_3_DEFAULT_CAPTURE_MODE;
            #else
                PulseCounter_3_CONTROL = ctrl;
            #endif /* 0 != PulseCounter_3_CAPTURE_MODE */ 
            
            #endif /* (!PulseCounter_3_ControlRegRemoved) */
        #endif /* (PulseCounter_3_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!PulseCounter_3_UsingFixedFunction)
            PulseCounter_3_ClearFIFO();
        #endif /* (!PulseCounter_3_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        PulseCounter_3_WritePeriod(PulseCounter_3_INIT_PERIOD_VALUE);
        #if (!(PulseCounter_3_UsingFixedFunction && (CY_PSOC5A)))
            PulseCounter_3_WriteCounter(PulseCounter_3_INIT_COUNTER_VALUE);
        #endif /* (!(PulseCounter_3_UsingFixedFunction && (CY_PSOC5A))) */
        PulseCounter_3_SetInterruptMode(PulseCounter_3_INIT_INTERRUPTS_MASK);
        
        #if (!PulseCounter_3_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)PulseCounter_3_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            PulseCounter_3_WriteCompare(PulseCounter_3_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PulseCounter_3_interruptState = CyEnterCriticalSection();
            
            PulseCounter_3_STATUS_AUX_CTRL |= PulseCounter_3_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(PulseCounter_3_interruptState);
            
        #endif /* (!PulseCounter_3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_3_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void PulseCounter_3_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PulseCounter_3_UsingFixedFunction)
        PulseCounter_3_GLOBAL_ENABLE |= PulseCounter_3_BLOCK_EN_MASK;
        PulseCounter_3_GLOBAL_STBY_ENABLE |= PulseCounter_3_BLOCK_STBY_EN_MASK;
    #endif /* (PulseCounter_3_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!PulseCounter_3_ControlRegRemoved || PulseCounter_3_UsingFixedFunction)
        PulseCounter_3_CONTROL |= PulseCounter_3_CTRL_ENABLE;                
    #endif /* (!PulseCounter_3_ControlRegRemoved || PulseCounter_3_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: PulseCounter_3_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  PulseCounter_3_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PulseCounter_3_Start(void) 
{
    if(PulseCounter_3_initVar == 0u)
    {
        PulseCounter_3_Init();
        
        PulseCounter_3_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    PulseCounter_3_Enable();        
}


/*******************************************************************************
* Function Name: PulseCounter_3_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void PulseCounter_3_Stop(void) 
{
    /* Disable Counter */
    #if(!PulseCounter_3_ControlRegRemoved || PulseCounter_3_UsingFixedFunction)
        PulseCounter_3_CONTROL &= ((uint8)(~PulseCounter_3_CTRL_ENABLE));        
    #endif /* (!PulseCounter_3_ControlRegRemoved || PulseCounter_3_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PulseCounter_3_UsingFixedFunction)
        PulseCounter_3_GLOBAL_ENABLE &= ((uint8)(~PulseCounter_3_BLOCK_EN_MASK));
        PulseCounter_3_GLOBAL_STBY_ENABLE &= ((uint8)(~PulseCounter_3_BLOCK_STBY_EN_MASK));
    #endif /* (PulseCounter_3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_3_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void PulseCounter_3_SetInterruptMode(uint8 interruptsMask) 
{
    PulseCounter_3_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: PulseCounter_3_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   PulseCounter_3_ReadStatusRegister(void) 
{
    return PulseCounter_3_STATUS;
}


#if(!PulseCounter_3_ControlRegRemoved)
/*******************************************************************************
* Function Name: PulseCounter_3_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   PulseCounter_3_ReadControlRegister(void) 
{
    return PulseCounter_3_CONTROL;
}


/*******************************************************************************
* Function Name: PulseCounter_3_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    PulseCounter_3_WriteControlRegister(uint8 control) 
{
    PulseCounter_3_CONTROL = control;
}

#endif  /* (!PulseCounter_3_ControlRegRemoved) */


#if (!(PulseCounter_3_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: PulseCounter_3_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void PulseCounter_3_WriteCounter(uint8 counter) \
                                   
{
    #if(PulseCounter_3_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (PulseCounter_3_GLOBAL_ENABLE & PulseCounter_3_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        PulseCounter_3_GLOBAL_ENABLE |= PulseCounter_3_BLOCK_EN_MASK;
        CY_SET_REG16(PulseCounter_3_COUNTER_LSB_PTR, (uint16)counter);
        PulseCounter_3_GLOBAL_ENABLE &= ((uint8)(~PulseCounter_3_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(PulseCounter_3_COUNTER_LSB_PTR, counter);
    #endif /* (PulseCounter_3_UsingFixedFunction) */
}
#endif /* (!(PulseCounter_3_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: PulseCounter_3_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 PulseCounter_3_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(PulseCounter_3_UsingFixedFunction)
		(void)CY_GET_REG16(PulseCounter_3_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(PulseCounter_3_COUNTER_LSB_PTR_8BIT);
	#endif/* (PulseCounter_3_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(PulseCounter_3_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PulseCounter_3_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(PulseCounter_3_STATICCOUNT_LSB_PTR));
    #endif /* (PulseCounter_3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_3_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 PulseCounter_3_ReadCapture(void) 
{
    #if(PulseCounter_3_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PulseCounter_3_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(PulseCounter_3_STATICCOUNT_LSB_PTR));
    #endif /* (PulseCounter_3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_3_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void PulseCounter_3_WritePeriod(uint8 period) 
{
    #if(PulseCounter_3_UsingFixedFunction)
        CY_SET_REG16(PulseCounter_3_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(PulseCounter_3_PERIOD_LSB_PTR, period);
    #endif /* (PulseCounter_3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_3_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 PulseCounter_3_ReadPeriod(void) 
{
    #if(PulseCounter_3_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PulseCounter_3_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PulseCounter_3_PERIOD_LSB_PTR));
    #endif /* (PulseCounter_3_UsingFixedFunction) */
}


#if (!PulseCounter_3_UsingFixedFunction)
/*******************************************************************************
* Function Name: PulseCounter_3_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void PulseCounter_3_WriteCompare(uint8 compare) \
                                   
{
    #if(PulseCounter_3_UsingFixedFunction)
        CY_SET_REG16(PulseCounter_3_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(PulseCounter_3_COMPARE_LSB_PTR, compare);
    #endif /* (PulseCounter_3_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_3_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 PulseCounter_3_ReadCompare(void) 
{
    return (CY_GET_REG8(PulseCounter_3_COMPARE_LSB_PTR));
}


#if (PulseCounter_3_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PulseCounter_3_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void PulseCounter_3_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    PulseCounter_3_CONTROL &= ((uint8)(~PulseCounter_3_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    PulseCounter_3_CONTROL |= compareMode;
}
#endif  /* (PulseCounter_3_COMPARE_MODE_SOFTWARE) */


#if (PulseCounter_3_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PulseCounter_3_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void PulseCounter_3_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    PulseCounter_3_CONTROL &= ((uint8)(~PulseCounter_3_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    PulseCounter_3_CONTROL |= ((uint8)((uint8)captureMode << PulseCounter_3_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (PulseCounter_3_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: PulseCounter_3_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void PulseCounter_3_ClearFIFO(void) 
{

    while(0u != (PulseCounter_3_ReadStatusRegister() & PulseCounter_3_STATUS_FIFONEMP))
    {
        (void)PulseCounter_3_ReadCapture();
    }

}
#endif  /* (!PulseCounter_3_UsingFixedFunction) */


/* [] END OF FILE */


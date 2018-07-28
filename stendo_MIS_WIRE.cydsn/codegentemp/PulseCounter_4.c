/*******************************************************************************
* File Name: PulseCounter_4.c  
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

#include "PulseCounter_4.h"

uint8 PulseCounter_4_initVar = 0u;


/*******************************************************************************
* Function Name: PulseCounter_4_Init
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
void PulseCounter_4_Init(void) 
{
        #if (!PulseCounter_4_UsingFixedFunction && !PulseCounter_4_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!PulseCounter_4_UsingFixedFunction && !PulseCounter_4_ControlRegRemoved) */
        
        #if(!PulseCounter_4_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 PulseCounter_4_interruptState;
        #endif /* (!PulseCounter_4_UsingFixedFunction) */
        
        #if (PulseCounter_4_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            PulseCounter_4_CONTROL &= PulseCounter_4_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                PulseCounter_4_CONTROL2 &= ((uint8)(~PulseCounter_4_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                PulseCounter_4_CONTROL3 &= ((uint8)(~PulseCounter_4_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (PulseCounter_4_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                PulseCounter_4_CONTROL |= PulseCounter_4_ONESHOT;
            #endif /* (PulseCounter_4_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            PulseCounter_4_CONTROL2 |= PulseCounter_4_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            PulseCounter_4_RT1 &= ((uint8)(~PulseCounter_4_RT1_MASK));
            PulseCounter_4_RT1 |= PulseCounter_4_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            PulseCounter_4_RT1 &= ((uint8)(~PulseCounter_4_SYNCDSI_MASK));
            PulseCounter_4_RT1 |= PulseCounter_4_SYNCDSI_EN;

        #else
            #if(!PulseCounter_4_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = PulseCounter_4_CONTROL & ((uint8)(~PulseCounter_4_CTRL_CMPMODE_MASK));
            PulseCounter_4_CONTROL = ctrl | PulseCounter_4_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = PulseCounter_4_CONTROL & ((uint8)(~PulseCounter_4_CTRL_CAPMODE_MASK));
            
            #if( 0 != PulseCounter_4_CAPTURE_MODE_CONF)
                PulseCounter_4_CONTROL = ctrl | PulseCounter_4_DEFAULT_CAPTURE_MODE;
            #else
                PulseCounter_4_CONTROL = ctrl;
            #endif /* 0 != PulseCounter_4_CAPTURE_MODE */ 
            
            #endif /* (!PulseCounter_4_ControlRegRemoved) */
        #endif /* (PulseCounter_4_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!PulseCounter_4_UsingFixedFunction)
            PulseCounter_4_ClearFIFO();
        #endif /* (!PulseCounter_4_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        PulseCounter_4_WritePeriod(PulseCounter_4_INIT_PERIOD_VALUE);
        #if (!(PulseCounter_4_UsingFixedFunction && (CY_PSOC5A)))
            PulseCounter_4_WriteCounter(PulseCounter_4_INIT_COUNTER_VALUE);
        #endif /* (!(PulseCounter_4_UsingFixedFunction && (CY_PSOC5A))) */
        PulseCounter_4_SetInterruptMode(PulseCounter_4_INIT_INTERRUPTS_MASK);
        
        #if (!PulseCounter_4_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)PulseCounter_4_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            PulseCounter_4_WriteCompare(PulseCounter_4_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PulseCounter_4_interruptState = CyEnterCriticalSection();
            
            PulseCounter_4_STATUS_AUX_CTRL |= PulseCounter_4_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(PulseCounter_4_interruptState);
            
        #endif /* (!PulseCounter_4_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_4_Enable
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
void PulseCounter_4_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PulseCounter_4_UsingFixedFunction)
        PulseCounter_4_GLOBAL_ENABLE |= PulseCounter_4_BLOCK_EN_MASK;
        PulseCounter_4_GLOBAL_STBY_ENABLE |= PulseCounter_4_BLOCK_STBY_EN_MASK;
    #endif /* (PulseCounter_4_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!PulseCounter_4_ControlRegRemoved || PulseCounter_4_UsingFixedFunction)
        PulseCounter_4_CONTROL |= PulseCounter_4_CTRL_ENABLE;                
    #endif /* (!PulseCounter_4_ControlRegRemoved || PulseCounter_4_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: PulseCounter_4_Start
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
*  PulseCounter_4_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PulseCounter_4_Start(void) 
{
    if(PulseCounter_4_initVar == 0u)
    {
        PulseCounter_4_Init();
        
        PulseCounter_4_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    PulseCounter_4_Enable();        
}


/*******************************************************************************
* Function Name: PulseCounter_4_Stop
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
void PulseCounter_4_Stop(void) 
{
    /* Disable Counter */
    #if(!PulseCounter_4_ControlRegRemoved || PulseCounter_4_UsingFixedFunction)
        PulseCounter_4_CONTROL &= ((uint8)(~PulseCounter_4_CTRL_ENABLE));        
    #endif /* (!PulseCounter_4_ControlRegRemoved || PulseCounter_4_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PulseCounter_4_UsingFixedFunction)
        PulseCounter_4_GLOBAL_ENABLE &= ((uint8)(~PulseCounter_4_BLOCK_EN_MASK));
        PulseCounter_4_GLOBAL_STBY_ENABLE &= ((uint8)(~PulseCounter_4_BLOCK_STBY_EN_MASK));
    #endif /* (PulseCounter_4_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_4_SetInterruptMode
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
void PulseCounter_4_SetInterruptMode(uint8 interruptsMask) 
{
    PulseCounter_4_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: PulseCounter_4_ReadStatusRegister
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
uint8   PulseCounter_4_ReadStatusRegister(void) 
{
    return PulseCounter_4_STATUS;
}


#if(!PulseCounter_4_ControlRegRemoved)
/*******************************************************************************
* Function Name: PulseCounter_4_ReadControlRegister
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
uint8   PulseCounter_4_ReadControlRegister(void) 
{
    return PulseCounter_4_CONTROL;
}


/*******************************************************************************
* Function Name: PulseCounter_4_WriteControlRegister
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
void    PulseCounter_4_WriteControlRegister(uint8 control) 
{
    PulseCounter_4_CONTROL = control;
}

#endif  /* (!PulseCounter_4_ControlRegRemoved) */


#if (!(PulseCounter_4_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: PulseCounter_4_WriteCounter
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
void PulseCounter_4_WriteCounter(uint8 counter) \
                                   
{
    #if(PulseCounter_4_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (PulseCounter_4_GLOBAL_ENABLE & PulseCounter_4_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        PulseCounter_4_GLOBAL_ENABLE |= PulseCounter_4_BLOCK_EN_MASK;
        CY_SET_REG16(PulseCounter_4_COUNTER_LSB_PTR, (uint16)counter);
        PulseCounter_4_GLOBAL_ENABLE &= ((uint8)(~PulseCounter_4_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(PulseCounter_4_COUNTER_LSB_PTR, counter);
    #endif /* (PulseCounter_4_UsingFixedFunction) */
}
#endif /* (!(PulseCounter_4_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: PulseCounter_4_ReadCounter
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
uint8 PulseCounter_4_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(PulseCounter_4_UsingFixedFunction)
		(void)CY_GET_REG16(PulseCounter_4_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(PulseCounter_4_COUNTER_LSB_PTR_8BIT);
	#endif/* (PulseCounter_4_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(PulseCounter_4_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PulseCounter_4_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(PulseCounter_4_STATICCOUNT_LSB_PTR));
    #endif /* (PulseCounter_4_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_4_ReadCapture
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
uint8 PulseCounter_4_ReadCapture(void) 
{
    #if(PulseCounter_4_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PulseCounter_4_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(PulseCounter_4_STATICCOUNT_LSB_PTR));
    #endif /* (PulseCounter_4_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_4_WritePeriod
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
void PulseCounter_4_WritePeriod(uint8 period) 
{
    #if(PulseCounter_4_UsingFixedFunction)
        CY_SET_REG16(PulseCounter_4_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(PulseCounter_4_PERIOD_LSB_PTR, period);
    #endif /* (PulseCounter_4_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_4_ReadPeriod
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
uint8 PulseCounter_4_ReadPeriod(void) 
{
    #if(PulseCounter_4_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PulseCounter_4_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PulseCounter_4_PERIOD_LSB_PTR));
    #endif /* (PulseCounter_4_UsingFixedFunction) */
}


#if (!PulseCounter_4_UsingFixedFunction)
/*******************************************************************************
* Function Name: PulseCounter_4_WriteCompare
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
void PulseCounter_4_WriteCompare(uint8 compare) \
                                   
{
    #if(PulseCounter_4_UsingFixedFunction)
        CY_SET_REG16(PulseCounter_4_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(PulseCounter_4_COMPARE_LSB_PTR, compare);
    #endif /* (PulseCounter_4_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PulseCounter_4_ReadCompare
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
uint8 PulseCounter_4_ReadCompare(void) 
{
    return (CY_GET_REG8(PulseCounter_4_COMPARE_LSB_PTR));
}


#if (PulseCounter_4_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PulseCounter_4_SetCompareMode
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
void PulseCounter_4_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    PulseCounter_4_CONTROL &= ((uint8)(~PulseCounter_4_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    PulseCounter_4_CONTROL |= compareMode;
}
#endif  /* (PulseCounter_4_COMPARE_MODE_SOFTWARE) */


#if (PulseCounter_4_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PulseCounter_4_SetCaptureMode
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
void PulseCounter_4_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    PulseCounter_4_CONTROL &= ((uint8)(~PulseCounter_4_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    PulseCounter_4_CONTROL |= ((uint8)((uint8)captureMode << PulseCounter_4_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (PulseCounter_4_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: PulseCounter_4_ClearFIFO
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
void PulseCounter_4_ClearFIFO(void) 
{

    while(0u != (PulseCounter_4_ReadStatusRegister() & PulseCounter_4_STATUS_FIFONEMP))
    {
        (void)PulseCounter_4_ReadCapture();
    }

}
#endif  /* (!PulseCounter_4_UsingFixedFunction) */


/* [] END OF FILE */


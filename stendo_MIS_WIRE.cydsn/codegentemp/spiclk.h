/*******************************************************************************
* File Name: spiclk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_spiclk_H)
#define CY_CLOCK_spiclk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void spiclk_Start(void) ;
void spiclk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void spiclk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void spiclk_StandbyPower(uint8 state) ;
void spiclk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 spiclk_GetDividerRegister(void) ;
void spiclk_SetModeRegister(uint8 modeBitMask) ;
void spiclk_ClearModeRegister(uint8 modeBitMask) ;
uint8 spiclk_GetModeRegister(void) ;
void spiclk_SetSourceRegister(uint8 clkSource) ;
uint8 spiclk_GetSourceRegister(void) ;
#if defined(spiclk__CFG3)
void spiclk_SetPhaseRegister(uint8 clkPhase) ;
uint8 spiclk_GetPhaseRegister(void) ;
#endif /* defined(spiclk__CFG3) */

#define spiclk_Enable()                       spiclk_Start()
#define spiclk_Disable()                      spiclk_Stop()
#define spiclk_SetDivider(clkDivider)         spiclk_SetDividerRegister(clkDivider, 1u)
#define spiclk_SetDividerValue(clkDivider)    spiclk_SetDividerRegister((clkDivider) - 1u, 1u)
#define spiclk_SetMode(clkMode)               spiclk_SetModeRegister(clkMode)
#define spiclk_SetSource(clkSource)           spiclk_SetSourceRegister(clkSource)
#if defined(spiclk__CFG3)
#define spiclk_SetPhase(clkPhase)             spiclk_SetPhaseRegister(clkPhase)
#define spiclk_SetPhaseValue(clkPhase)        spiclk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(spiclk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define spiclk_CLKEN              (* (reg8 *) spiclk__PM_ACT_CFG)
#define spiclk_CLKEN_PTR          ((reg8 *) spiclk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define spiclk_CLKSTBY            (* (reg8 *) spiclk__PM_STBY_CFG)
#define spiclk_CLKSTBY_PTR        ((reg8 *) spiclk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define spiclk_DIV_LSB            (* (reg8 *) spiclk__CFG0)
#define spiclk_DIV_LSB_PTR        ((reg8 *) spiclk__CFG0)
#define spiclk_DIV_PTR            ((reg16 *) spiclk__CFG0)

/* Clock MSB divider configuration register. */
#define spiclk_DIV_MSB            (* (reg8 *) spiclk__CFG1)
#define spiclk_DIV_MSB_PTR        ((reg8 *) spiclk__CFG1)

/* Mode and source configuration register */
#define spiclk_MOD_SRC            (* (reg8 *) spiclk__CFG2)
#define spiclk_MOD_SRC_PTR        ((reg8 *) spiclk__CFG2)

#if defined(spiclk__CFG3)
/* Analog clock phase configuration register */
#define spiclk_PHASE              (* (reg8 *) spiclk__CFG3)
#define spiclk_PHASE_PTR          ((reg8 *) spiclk__CFG3)
#endif /* defined(spiclk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define spiclk_CLKEN_MASK         spiclk__PM_ACT_MSK
#define spiclk_CLKSTBY_MASK       spiclk__PM_STBY_MSK

/* CFG2 field masks */
#define spiclk_SRC_SEL_MSK        spiclk__CFG2_SRC_SEL_MASK
#define spiclk_MODE_MASK          (~(spiclk_SRC_SEL_MSK))

#if defined(spiclk__CFG3)
/* CFG3 phase mask */
#define spiclk_PHASE_MASK         spiclk__CFG3_PHASE_DLY_MASK
#endif /* defined(spiclk__CFG3) */

#endif /* CY_CLOCK_spiclk_H */


/* [] END OF FILE */

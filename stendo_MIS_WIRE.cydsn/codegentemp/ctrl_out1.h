/*******************************************************************************
* File Name: ctrl_out1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ctrl_out1_H) /* Pins ctrl_out1_H */
#define CY_PINS_ctrl_out1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ctrl_out1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ctrl_out1__PORT == 15 && ((ctrl_out1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ctrl_out1_Write(uint8 value);
void    ctrl_out1_SetDriveMode(uint8 mode);
uint8   ctrl_out1_ReadDataReg(void);
uint8   ctrl_out1_Read(void);
void    ctrl_out1_SetInterruptMode(uint16 position, uint16 mode);
uint8   ctrl_out1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ctrl_out1_SetDriveMode() function.
     *  @{
     */
        #define ctrl_out1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ctrl_out1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ctrl_out1_DM_RES_UP          PIN_DM_RES_UP
        #define ctrl_out1_DM_RES_DWN         PIN_DM_RES_DWN
        #define ctrl_out1_DM_OD_LO           PIN_DM_OD_LO
        #define ctrl_out1_DM_OD_HI           PIN_DM_OD_HI
        #define ctrl_out1_DM_STRONG          PIN_DM_STRONG
        #define ctrl_out1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ctrl_out1_MASK               ctrl_out1__MASK
#define ctrl_out1_SHIFT              ctrl_out1__SHIFT
#define ctrl_out1_WIDTH              1u

/* Interrupt constants */
#if defined(ctrl_out1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ctrl_out1_SetInterruptMode() function.
     *  @{
     */
        #define ctrl_out1_INTR_NONE      (uint16)(0x0000u)
        #define ctrl_out1_INTR_RISING    (uint16)(0x0001u)
        #define ctrl_out1_INTR_FALLING   (uint16)(0x0002u)
        #define ctrl_out1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ctrl_out1_INTR_MASK      (0x01u) 
#endif /* (ctrl_out1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ctrl_out1_PS                     (* (reg8 *) ctrl_out1__PS)
/* Data Register */
#define ctrl_out1_DR                     (* (reg8 *) ctrl_out1__DR)
/* Port Number */
#define ctrl_out1_PRT_NUM                (* (reg8 *) ctrl_out1__PRT) 
/* Connect to Analog Globals */                                                  
#define ctrl_out1_AG                     (* (reg8 *) ctrl_out1__AG)                       
/* Analog MUX bux enable */
#define ctrl_out1_AMUX                   (* (reg8 *) ctrl_out1__AMUX) 
/* Bidirectional Enable */                                                        
#define ctrl_out1_BIE                    (* (reg8 *) ctrl_out1__BIE)
/* Bit-mask for Aliased Register Access */
#define ctrl_out1_BIT_MASK               (* (reg8 *) ctrl_out1__BIT_MASK)
/* Bypass Enable */
#define ctrl_out1_BYP                    (* (reg8 *) ctrl_out1__BYP)
/* Port wide control signals */                                                   
#define ctrl_out1_CTL                    (* (reg8 *) ctrl_out1__CTL)
/* Drive Modes */
#define ctrl_out1_DM0                    (* (reg8 *) ctrl_out1__DM0) 
#define ctrl_out1_DM1                    (* (reg8 *) ctrl_out1__DM1)
#define ctrl_out1_DM2                    (* (reg8 *) ctrl_out1__DM2) 
/* Input Buffer Disable Override */
#define ctrl_out1_INP_DIS                (* (reg8 *) ctrl_out1__INP_DIS)
/* LCD Common or Segment Drive */
#define ctrl_out1_LCD_COM_SEG            (* (reg8 *) ctrl_out1__LCD_COM_SEG)
/* Enable Segment LCD */
#define ctrl_out1_LCD_EN                 (* (reg8 *) ctrl_out1__LCD_EN)
/* Slew Rate Control */
#define ctrl_out1_SLW                    (* (reg8 *) ctrl_out1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ctrl_out1_PRTDSI__CAPS_SEL       (* (reg8 *) ctrl_out1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ctrl_out1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ctrl_out1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ctrl_out1_PRTDSI__OE_SEL0        (* (reg8 *) ctrl_out1__PRTDSI__OE_SEL0) 
#define ctrl_out1_PRTDSI__OE_SEL1        (* (reg8 *) ctrl_out1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ctrl_out1_PRTDSI__OUT_SEL0       (* (reg8 *) ctrl_out1__PRTDSI__OUT_SEL0) 
#define ctrl_out1_PRTDSI__OUT_SEL1       (* (reg8 *) ctrl_out1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ctrl_out1_PRTDSI__SYNC_OUT       (* (reg8 *) ctrl_out1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ctrl_out1__SIO_CFG)
    #define ctrl_out1_SIO_HYST_EN        (* (reg8 *) ctrl_out1__SIO_HYST_EN)
    #define ctrl_out1_SIO_REG_HIFREQ     (* (reg8 *) ctrl_out1__SIO_REG_HIFREQ)
    #define ctrl_out1_SIO_CFG            (* (reg8 *) ctrl_out1__SIO_CFG)
    #define ctrl_out1_SIO_DIFF           (* (reg8 *) ctrl_out1__SIO_DIFF)
#endif /* (ctrl_out1__SIO_CFG) */

/* Interrupt Registers */
#if defined(ctrl_out1__INTSTAT)
    #define ctrl_out1_INTSTAT            (* (reg8 *) ctrl_out1__INTSTAT)
    #define ctrl_out1_SNAP               (* (reg8 *) ctrl_out1__SNAP)
    
	#define ctrl_out1_0_INTTYPE_REG 		(* (reg8 *) ctrl_out1__0__INTTYPE)
#endif /* (ctrl_out1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ctrl_out1_H */


/* [] END OF FILE */

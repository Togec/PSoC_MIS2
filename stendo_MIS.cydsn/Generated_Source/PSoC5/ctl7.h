/*******************************************************************************
* File Name: ctl7.h  
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

#if !defined(CY_PINS_ctl7_H) /* Pins ctl7_H */
#define CY_PINS_ctl7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ctl7_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ctl7__PORT == 15 && ((ctl7__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ctl7_Write(uint8 value);
void    ctl7_SetDriveMode(uint8 mode);
uint8   ctl7_ReadDataReg(void);
uint8   ctl7_Read(void);
void    ctl7_SetInterruptMode(uint16 position, uint16 mode);
uint8   ctl7_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ctl7_SetDriveMode() function.
     *  @{
     */
        #define ctl7_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ctl7_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ctl7_DM_RES_UP          PIN_DM_RES_UP
        #define ctl7_DM_RES_DWN         PIN_DM_RES_DWN
        #define ctl7_DM_OD_LO           PIN_DM_OD_LO
        #define ctl7_DM_OD_HI           PIN_DM_OD_HI
        #define ctl7_DM_STRONG          PIN_DM_STRONG
        #define ctl7_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ctl7_MASK               ctl7__MASK
#define ctl7_SHIFT              ctl7__SHIFT
#define ctl7_WIDTH              1u

/* Interrupt constants */
#if defined(ctl7__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ctl7_SetInterruptMode() function.
     *  @{
     */
        #define ctl7_INTR_NONE      (uint16)(0x0000u)
        #define ctl7_INTR_RISING    (uint16)(0x0001u)
        #define ctl7_INTR_FALLING   (uint16)(0x0002u)
        #define ctl7_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ctl7_INTR_MASK      (0x01u) 
#endif /* (ctl7__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ctl7_PS                     (* (reg8 *) ctl7__PS)
/* Data Register */
#define ctl7_DR                     (* (reg8 *) ctl7__DR)
/* Port Number */
#define ctl7_PRT_NUM                (* (reg8 *) ctl7__PRT) 
/* Connect to Analog Globals */                                                  
#define ctl7_AG                     (* (reg8 *) ctl7__AG)                       
/* Analog MUX bux enable */
#define ctl7_AMUX                   (* (reg8 *) ctl7__AMUX) 
/* Bidirectional Enable */                                                        
#define ctl7_BIE                    (* (reg8 *) ctl7__BIE)
/* Bit-mask for Aliased Register Access */
#define ctl7_BIT_MASK               (* (reg8 *) ctl7__BIT_MASK)
/* Bypass Enable */
#define ctl7_BYP                    (* (reg8 *) ctl7__BYP)
/* Port wide control signals */                                                   
#define ctl7_CTL                    (* (reg8 *) ctl7__CTL)
/* Drive Modes */
#define ctl7_DM0                    (* (reg8 *) ctl7__DM0) 
#define ctl7_DM1                    (* (reg8 *) ctl7__DM1)
#define ctl7_DM2                    (* (reg8 *) ctl7__DM2) 
/* Input Buffer Disable Override */
#define ctl7_INP_DIS                (* (reg8 *) ctl7__INP_DIS)
/* LCD Common or Segment Drive */
#define ctl7_LCD_COM_SEG            (* (reg8 *) ctl7__LCD_COM_SEG)
/* Enable Segment LCD */
#define ctl7_LCD_EN                 (* (reg8 *) ctl7__LCD_EN)
/* Slew Rate Control */
#define ctl7_SLW                    (* (reg8 *) ctl7__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ctl7_PRTDSI__CAPS_SEL       (* (reg8 *) ctl7__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ctl7_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ctl7__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ctl7_PRTDSI__OE_SEL0        (* (reg8 *) ctl7__PRTDSI__OE_SEL0) 
#define ctl7_PRTDSI__OE_SEL1        (* (reg8 *) ctl7__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ctl7_PRTDSI__OUT_SEL0       (* (reg8 *) ctl7__PRTDSI__OUT_SEL0) 
#define ctl7_PRTDSI__OUT_SEL1       (* (reg8 *) ctl7__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ctl7_PRTDSI__SYNC_OUT       (* (reg8 *) ctl7__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ctl7__SIO_CFG)
    #define ctl7_SIO_HYST_EN        (* (reg8 *) ctl7__SIO_HYST_EN)
    #define ctl7_SIO_REG_HIFREQ     (* (reg8 *) ctl7__SIO_REG_HIFREQ)
    #define ctl7_SIO_CFG            (* (reg8 *) ctl7__SIO_CFG)
    #define ctl7_SIO_DIFF           (* (reg8 *) ctl7__SIO_DIFF)
#endif /* (ctl7__SIO_CFG) */

/* Interrupt Registers */
#if defined(ctl7__INTSTAT)
    #define ctl7_INTSTAT            (* (reg8 *) ctl7__INTSTAT)
    #define ctl7_SNAP               (* (reg8 *) ctl7__SNAP)
    
	#define ctl7_0_INTTYPE_REG 		(* (reg8 *) ctl7__0__INTTYPE)
#endif /* (ctl7__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ctl7_H */


/* [] END OF FILE */

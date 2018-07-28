/*******************************************************************************
* File Name: ctl6.h  
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

#if !defined(CY_PINS_ctl6_H) /* Pins ctl6_H */
#define CY_PINS_ctl6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ctl6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ctl6__PORT == 15 && ((ctl6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ctl6_Write(uint8 value);
void    ctl6_SetDriveMode(uint8 mode);
uint8   ctl6_ReadDataReg(void);
uint8   ctl6_Read(void);
void    ctl6_SetInterruptMode(uint16 position, uint16 mode);
uint8   ctl6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ctl6_SetDriveMode() function.
     *  @{
     */
        #define ctl6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ctl6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ctl6_DM_RES_UP          PIN_DM_RES_UP
        #define ctl6_DM_RES_DWN         PIN_DM_RES_DWN
        #define ctl6_DM_OD_LO           PIN_DM_OD_LO
        #define ctl6_DM_OD_HI           PIN_DM_OD_HI
        #define ctl6_DM_STRONG          PIN_DM_STRONG
        #define ctl6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ctl6_MASK               ctl6__MASK
#define ctl6_SHIFT              ctl6__SHIFT
#define ctl6_WIDTH              1u

/* Interrupt constants */
#if defined(ctl6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ctl6_SetInterruptMode() function.
     *  @{
     */
        #define ctl6_INTR_NONE      (uint16)(0x0000u)
        #define ctl6_INTR_RISING    (uint16)(0x0001u)
        #define ctl6_INTR_FALLING   (uint16)(0x0002u)
        #define ctl6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ctl6_INTR_MASK      (0x01u) 
#endif /* (ctl6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ctl6_PS                     (* (reg8 *) ctl6__PS)
/* Data Register */
#define ctl6_DR                     (* (reg8 *) ctl6__DR)
/* Port Number */
#define ctl6_PRT_NUM                (* (reg8 *) ctl6__PRT) 
/* Connect to Analog Globals */                                                  
#define ctl6_AG                     (* (reg8 *) ctl6__AG)                       
/* Analog MUX bux enable */
#define ctl6_AMUX                   (* (reg8 *) ctl6__AMUX) 
/* Bidirectional Enable */                                                        
#define ctl6_BIE                    (* (reg8 *) ctl6__BIE)
/* Bit-mask for Aliased Register Access */
#define ctl6_BIT_MASK               (* (reg8 *) ctl6__BIT_MASK)
/* Bypass Enable */
#define ctl6_BYP                    (* (reg8 *) ctl6__BYP)
/* Port wide control signals */                                                   
#define ctl6_CTL                    (* (reg8 *) ctl6__CTL)
/* Drive Modes */
#define ctl6_DM0                    (* (reg8 *) ctl6__DM0) 
#define ctl6_DM1                    (* (reg8 *) ctl6__DM1)
#define ctl6_DM2                    (* (reg8 *) ctl6__DM2) 
/* Input Buffer Disable Override */
#define ctl6_INP_DIS                (* (reg8 *) ctl6__INP_DIS)
/* LCD Common or Segment Drive */
#define ctl6_LCD_COM_SEG            (* (reg8 *) ctl6__LCD_COM_SEG)
/* Enable Segment LCD */
#define ctl6_LCD_EN                 (* (reg8 *) ctl6__LCD_EN)
/* Slew Rate Control */
#define ctl6_SLW                    (* (reg8 *) ctl6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ctl6_PRTDSI__CAPS_SEL       (* (reg8 *) ctl6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ctl6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ctl6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ctl6_PRTDSI__OE_SEL0        (* (reg8 *) ctl6__PRTDSI__OE_SEL0) 
#define ctl6_PRTDSI__OE_SEL1        (* (reg8 *) ctl6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ctl6_PRTDSI__OUT_SEL0       (* (reg8 *) ctl6__PRTDSI__OUT_SEL0) 
#define ctl6_PRTDSI__OUT_SEL1       (* (reg8 *) ctl6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ctl6_PRTDSI__SYNC_OUT       (* (reg8 *) ctl6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ctl6__SIO_CFG)
    #define ctl6_SIO_HYST_EN        (* (reg8 *) ctl6__SIO_HYST_EN)
    #define ctl6_SIO_REG_HIFREQ     (* (reg8 *) ctl6__SIO_REG_HIFREQ)
    #define ctl6_SIO_CFG            (* (reg8 *) ctl6__SIO_CFG)
    #define ctl6_SIO_DIFF           (* (reg8 *) ctl6__SIO_DIFF)
#endif /* (ctl6__SIO_CFG) */

/* Interrupt Registers */
#if defined(ctl6__INTSTAT)
    #define ctl6_INTSTAT            (* (reg8 *) ctl6__INTSTAT)
    #define ctl6_SNAP               (* (reg8 *) ctl6__SNAP)
    
	#define ctl6_0_INTTYPE_REG 		(* (reg8 *) ctl6__0__INTTYPE)
#endif /* (ctl6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ctl6_H */


/* [] END OF FILE */

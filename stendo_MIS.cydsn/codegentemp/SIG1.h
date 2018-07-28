/*******************************************************************************
* File Name: SIG1.h  
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

#if !defined(CY_PINS_SIG1_H) /* Pins SIG1_H */
#define CY_PINS_SIG1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SIG1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SIG1__PORT == 15 && ((SIG1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SIG1_Write(uint8 value);
void    SIG1_SetDriveMode(uint8 mode);
uint8   SIG1_ReadDataReg(void);
uint8   SIG1_Read(void);
void    SIG1_SetInterruptMode(uint16 position, uint16 mode);
uint8   SIG1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SIG1_SetDriveMode() function.
     *  @{
     */
        #define SIG1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SIG1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SIG1_DM_RES_UP          PIN_DM_RES_UP
        #define SIG1_DM_RES_DWN         PIN_DM_RES_DWN
        #define SIG1_DM_OD_LO           PIN_DM_OD_LO
        #define SIG1_DM_OD_HI           PIN_DM_OD_HI
        #define SIG1_DM_STRONG          PIN_DM_STRONG
        #define SIG1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SIG1_MASK               SIG1__MASK
#define SIG1_SHIFT              SIG1__SHIFT
#define SIG1_WIDTH              1u

/* Interrupt constants */
#if defined(SIG1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SIG1_SetInterruptMode() function.
     *  @{
     */
        #define SIG1_INTR_NONE      (uint16)(0x0000u)
        #define SIG1_INTR_RISING    (uint16)(0x0001u)
        #define SIG1_INTR_FALLING   (uint16)(0x0002u)
        #define SIG1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SIG1_INTR_MASK      (0x01u) 
#endif /* (SIG1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SIG1_PS                     (* (reg8 *) SIG1__PS)
/* Data Register */
#define SIG1_DR                     (* (reg8 *) SIG1__DR)
/* Port Number */
#define SIG1_PRT_NUM                (* (reg8 *) SIG1__PRT) 
/* Connect to Analog Globals */                                                  
#define SIG1_AG                     (* (reg8 *) SIG1__AG)                       
/* Analog MUX bux enable */
#define SIG1_AMUX                   (* (reg8 *) SIG1__AMUX) 
/* Bidirectional Enable */                                                        
#define SIG1_BIE                    (* (reg8 *) SIG1__BIE)
/* Bit-mask for Aliased Register Access */
#define SIG1_BIT_MASK               (* (reg8 *) SIG1__BIT_MASK)
/* Bypass Enable */
#define SIG1_BYP                    (* (reg8 *) SIG1__BYP)
/* Port wide control signals */                                                   
#define SIG1_CTL                    (* (reg8 *) SIG1__CTL)
/* Drive Modes */
#define SIG1_DM0                    (* (reg8 *) SIG1__DM0) 
#define SIG1_DM1                    (* (reg8 *) SIG1__DM1)
#define SIG1_DM2                    (* (reg8 *) SIG1__DM2) 
/* Input Buffer Disable Override */
#define SIG1_INP_DIS                (* (reg8 *) SIG1__INP_DIS)
/* LCD Common or Segment Drive */
#define SIG1_LCD_COM_SEG            (* (reg8 *) SIG1__LCD_COM_SEG)
/* Enable Segment LCD */
#define SIG1_LCD_EN                 (* (reg8 *) SIG1__LCD_EN)
/* Slew Rate Control */
#define SIG1_SLW                    (* (reg8 *) SIG1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SIG1_PRTDSI__CAPS_SEL       (* (reg8 *) SIG1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SIG1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SIG1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SIG1_PRTDSI__OE_SEL0        (* (reg8 *) SIG1__PRTDSI__OE_SEL0) 
#define SIG1_PRTDSI__OE_SEL1        (* (reg8 *) SIG1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SIG1_PRTDSI__OUT_SEL0       (* (reg8 *) SIG1__PRTDSI__OUT_SEL0) 
#define SIG1_PRTDSI__OUT_SEL1       (* (reg8 *) SIG1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SIG1_PRTDSI__SYNC_OUT       (* (reg8 *) SIG1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SIG1__SIO_CFG)
    #define SIG1_SIO_HYST_EN        (* (reg8 *) SIG1__SIO_HYST_EN)
    #define SIG1_SIO_REG_HIFREQ     (* (reg8 *) SIG1__SIO_REG_HIFREQ)
    #define SIG1_SIO_CFG            (* (reg8 *) SIG1__SIO_CFG)
    #define SIG1_SIO_DIFF           (* (reg8 *) SIG1__SIO_DIFF)
#endif /* (SIG1__SIO_CFG) */

/* Interrupt Registers */
#if defined(SIG1__INTSTAT)
    #define SIG1_INTSTAT            (* (reg8 *) SIG1__INTSTAT)
    #define SIG1_SNAP               (* (reg8 *) SIG1__SNAP)
    
	#define SIG1_0_INTTYPE_REG 		(* (reg8 *) SIG1__0__INTTYPE)
#endif /* (SIG1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SIG1_H */


/* [] END OF FILE */

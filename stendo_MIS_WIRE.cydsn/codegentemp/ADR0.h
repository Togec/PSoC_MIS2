/*******************************************************************************
* File Name: ADR0.h  
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

#if !defined(CY_PINS_ADR0_H) /* Pins ADR0_H */
#define CY_PINS_ADR0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ADR0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ADR0__PORT == 15 && ((ADR0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ADR0_Write(uint8 value);
void    ADR0_SetDriveMode(uint8 mode);
uint8   ADR0_ReadDataReg(void);
uint8   ADR0_Read(void);
void    ADR0_SetInterruptMode(uint16 position, uint16 mode);
uint8   ADR0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ADR0_SetDriveMode() function.
     *  @{
     */
        #define ADR0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ADR0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ADR0_DM_RES_UP          PIN_DM_RES_UP
        #define ADR0_DM_RES_DWN         PIN_DM_RES_DWN
        #define ADR0_DM_OD_LO           PIN_DM_OD_LO
        #define ADR0_DM_OD_HI           PIN_DM_OD_HI
        #define ADR0_DM_STRONG          PIN_DM_STRONG
        #define ADR0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ADR0_MASK               ADR0__MASK
#define ADR0_SHIFT              ADR0__SHIFT
#define ADR0_WIDTH              1u

/* Interrupt constants */
#if defined(ADR0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ADR0_SetInterruptMode() function.
     *  @{
     */
        #define ADR0_INTR_NONE      (uint16)(0x0000u)
        #define ADR0_INTR_RISING    (uint16)(0x0001u)
        #define ADR0_INTR_FALLING   (uint16)(0x0002u)
        #define ADR0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ADR0_INTR_MASK      (0x01u) 
#endif /* (ADR0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ADR0_PS                     (* (reg8 *) ADR0__PS)
/* Data Register */
#define ADR0_DR                     (* (reg8 *) ADR0__DR)
/* Port Number */
#define ADR0_PRT_NUM                (* (reg8 *) ADR0__PRT) 
/* Connect to Analog Globals */                                                  
#define ADR0_AG                     (* (reg8 *) ADR0__AG)                       
/* Analog MUX bux enable */
#define ADR0_AMUX                   (* (reg8 *) ADR0__AMUX) 
/* Bidirectional Enable */                                                        
#define ADR0_BIE                    (* (reg8 *) ADR0__BIE)
/* Bit-mask for Aliased Register Access */
#define ADR0_BIT_MASK               (* (reg8 *) ADR0__BIT_MASK)
/* Bypass Enable */
#define ADR0_BYP                    (* (reg8 *) ADR0__BYP)
/* Port wide control signals */                                                   
#define ADR0_CTL                    (* (reg8 *) ADR0__CTL)
/* Drive Modes */
#define ADR0_DM0                    (* (reg8 *) ADR0__DM0) 
#define ADR0_DM1                    (* (reg8 *) ADR0__DM1)
#define ADR0_DM2                    (* (reg8 *) ADR0__DM2) 
/* Input Buffer Disable Override */
#define ADR0_INP_DIS                (* (reg8 *) ADR0__INP_DIS)
/* LCD Common or Segment Drive */
#define ADR0_LCD_COM_SEG            (* (reg8 *) ADR0__LCD_COM_SEG)
/* Enable Segment LCD */
#define ADR0_LCD_EN                 (* (reg8 *) ADR0__LCD_EN)
/* Slew Rate Control */
#define ADR0_SLW                    (* (reg8 *) ADR0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ADR0_PRTDSI__CAPS_SEL       (* (reg8 *) ADR0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ADR0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ADR0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ADR0_PRTDSI__OE_SEL0        (* (reg8 *) ADR0__PRTDSI__OE_SEL0) 
#define ADR0_PRTDSI__OE_SEL1        (* (reg8 *) ADR0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ADR0_PRTDSI__OUT_SEL0       (* (reg8 *) ADR0__PRTDSI__OUT_SEL0) 
#define ADR0_PRTDSI__OUT_SEL1       (* (reg8 *) ADR0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ADR0_PRTDSI__SYNC_OUT       (* (reg8 *) ADR0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ADR0__SIO_CFG)
    #define ADR0_SIO_HYST_EN        (* (reg8 *) ADR0__SIO_HYST_EN)
    #define ADR0_SIO_REG_HIFREQ     (* (reg8 *) ADR0__SIO_REG_HIFREQ)
    #define ADR0_SIO_CFG            (* (reg8 *) ADR0__SIO_CFG)
    #define ADR0_SIO_DIFF           (* (reg8 *) ADR0__SIO_DIFF)
#endif /* (ADR0__SIO_CFG) */

/* Interrupt Registers */
#if defined(ADR0__INTSTAT)
    #define ADR0_INTSTAT            (* (reg8 *) ADR0__INTSTAT)
    #define ADR0_SNAP               (* (reg8 *) ADR0__SNAP)
    
	#define ADR0_0_INTTYPE_REG 		(* (reg8 *) ADR0__0__INTTYPE)
#endif /* (ADR0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ADR0_H */


/* [] END OF FILE */

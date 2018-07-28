/*******************************************************************************
* File Name: ADR1.h  
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

#if !defined(CY_PINS_ADR1_H) /* Pins ADR1_H */
#define CY_PINS_ADR1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ADR1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ADR1__PORT == 15 && ((ADR1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ADR1_Write(uint8 value);
void    ADR1_SetDriveMode(uint8 mode);
uint8   ADR1_ReadDataReg(void);
uint8   ADR1_Read(void);
void    ADR1_SetInterruptMode(uint16 position, uint16 mode);
uint8   ADR1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ADR1_SetDriveMode() function.
     *  @{
     */
        #define ADR1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ADR1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ADR1_DM_RES_UP          PIN_DM_RES_UP
        #define ADR1_DM_RES_DWN         PIN_DM_RES_DWN
        #define ADR1_DM_OD_LO           PIN_DM_OD_LO
        #define ADR1_DM_OD_HI           PIN_DM_OD_HI
        #define ADR1_DM_STRONG          PIN_DM_STRONG
        #define ADR1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ADR1_MASK               ADR1__MASK
#define ADR1_SHIFT              ADR1__SHIFT
#define ADR1_WIDTH              1u

/* Interrupt constants */
#if defined(ADR1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ADR1_SetInterruptMode() function.
     *  @{
     */
        #define ADR1_INTR_NONE      (uint16)(0x0000u)
        #define ADR1_INTR_RISING    (uint16)(0x0001u)
        #define ADR1_INTR_FALLING   (uint16)(0x0002u)
        #define ADR1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ADR1_INTR_MASK      (0x01u) 
#endif /* (ADR1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ADR1_PS                     (* (reg8 *) ADR1__PS)
/* Data Register */
#define ADR1_DR                     (* (reg8 *) ADR1__DR)
/* Port Number */
#define ADR1_PRT_NUM                (* (reg8 *) ADR1__PRT) 
/* Connect to Analog Globals */                                                  
#define ADR1_AG                     (* (reg8 *) ADR1__AG)                       
/* Analog MUX bux enable */
#define ADR1_AMUX                   (* (reg8 *) ADR1__AMUX) 
/* Bidirectional Enable */                                                        
#define ADR1_BIE                    (* (reg8 *) ADR1__BIE)
/* Bit-mask for Aliased Register Access */
#define ADR1_BIT_MASK               (* (reg8 *) ADR1__BIT_MASK)
/* Bypass Enable */
#define ADR1_BYP                    (* (reg8 *) ADR1__BYP)
/* Port wide control signals */                                                   
#define ADR1_CTL                    (* (reg8 *) ADR1__CTL)
/* Drive Modes */
#define ADR1_DM0                    (* (reg8 *) ADR1__DM0) 
#define ADR1_DM1                    (* (reg8 *) ADR1__DM1)
#define ADR1_DM2                    (* (reg8 *) ADR1__DM2) 
/* Input Buffer Disable Override */
#define ADR1_INP_DIS                (* (reg8 *) ADR1__INP_DIS)
/* LCD Common or Segment Drive */
#define ADR1_LCD_COM_SEG            (* (reg8 *) ADR1__LCD_COM_SEG)
/* Enable Segment LCD */
#define ADR1_LCD_EN                 (* (reg8 *) ADR1__LCD_EN)
/* Slew Rate Control */
#define ADR1_SLW                    (* (reg8 *) ADR1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ADR1_PRTDSI__CAPS_SEL       (* (reg8 *) ADR1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ADR1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ADR1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ADR1_PRTDSI__OE_SEL0        (* (reg8 *) ADR1__PRTDSI__OE_SEL0) 
#define ADR1_PRTDSI__OE_SEL1        (* (reg8 *) ADR1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ADR1_PRTDSI__OUT_SEL0       (* (reg8 *) ADR1__PRTDSI__OUT_SEL0) 
#define ADR1_PRTDSI__OUT_SEL1       (* (reg8 *) ADR1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ADR1_PRTDSI__SYNC_OUT       (* (reg8 *) ADR1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ADR1__SIO_CFG)
    #define ADR1_SIO_HYST_EN        (* (reg8 *) ADR1__SIO_HYST_EN)
    #define ADR1_SIO_REG_HIFREQ     (* (reg8 *) ADR1__SIO_REG_HIFREQ)
    #define ADR1_SIO_CFG            (* (reg8 *) ADR1__SIO_CFG)
    #define ADR1_SIO_DIFF           (* (reg8 *) ADR1__SIO_DIFF)
#endif /* (ADR1__SIO_CFG) */

/* Interrupt Registers */
#if defined(ADR1__INTSTAT)
    #define ADR1_INTSTAT            (* (reg8 *) ADR1__INTSTAT)
    #define ADR1_SNAP               (* (reg8 *) ADR1__SNAP)
    
	#define ADR1_0_INTTYPE_REG 		(* (reg8 *) ADR1__0__INTTYPE)
#endif /* (ADR1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ADR1_H */


/* [] END OF FILE */

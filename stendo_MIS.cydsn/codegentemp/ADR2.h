/*******************************************************************************
* File Name: ADR2.h  
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

#if !defined(CY_PINS_ADR2_H) /* Pins ADR2_H */
#define CY_PINS_ADR2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ADR2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ADR2__PORT == 15 && ((ADR2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ADR2_Write(uint8 value);
void    ADR2_SetDriveMode(uint8 mode);
uint8   ADR2_ReadDataReg(void);
uint8   ADR2_Read(void);
void    ADR2_SetInterruptMode(uint16 position, uint16 mode);
uint8   ADR2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ADR2_SetDriveMode() function.
     *  @{
     */
        #define ADR2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ADR2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ADR2_DM_RES_UP          PIN_DM_RES_UP
        #define ADR2_DM_RES_DWN         PIN_DM_RES_DWN
        #define ADR2_DM_OD_LO           PIN_DM_OD_LO
        #define ADR2_DM_OD_HI           PIN_DM_OD_HI
        #define ADR2_DM_STRONG          PIN_DM_STRONG
        #define ADR2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ADR2_MASK               ADR2__MASK
#define ADR2_SHIFT              ADR2__SHIFT
#define ADR2_WIDTH              1u

/* Interrupt constants */
#if defined(ADR2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ADR2_SetInterruptMode() function.
     *  @{
     */
        #define ADR2_INTR_NONE      (uint16)(0x0000u)
        #define ADR2_INTR_RISING    (uint16)(0x0001u)
        #define ADR2_INTR_FALLING   (uint16)(0x0002u)
        #define ADR2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ADR2_INTR_MASK      (0x01u) 
#endif /* (ADR2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ADR2_PS                     (* (reg8 *) ADR2__PS)
/* Data Register */
#define ADR2_DR                     (* (reg8 *) ADR2__DR)
/* Port Number */
#define ADR2_PRT_NUM                (* (reg8 *) ADR2__PRT) 
/* Connect to Analog Globals */                                                  
#define ADR2_AG                     (* (reg8 *) ADR2__AG)                       
/* Analog MUX bux enable */
#define ADR2_AMUX                   (* (reg8 *) ADR2__AMUX) 
/* Bidirectional Enable */                                                        
#define ADR2_BIE                    (* (reg8 *) ADR2__BIE)
/* Bit-mask for Aliased Register Access */
#define ADR2_BIT_MASK               (* (reg8 *) ADR2__BIT_MASK)
/* Bypass Enable */
#define ADR2_BYP                    (* (reg8 *) ADR2__BYP)
/* Port wide control signals */                                                   
#define ADR2_CTL                    (* (reg8 *) ADR2__CTL)
/* Drive Modes */
#define ADR2_DM0                    (* (reg8 *) ADR2__DM0) 
#define ADR2_DM1                    (* (reg8 *) ADR2__DM1)
#define ADR2_DM2                    (* (reg8 *) ADR2__DM2) 
/* Input Buffer Disable Override */
#define ADR2_INP_DIS                (* (reg8 *) ADR2__INP_DIS)
/* LCD Common or Segment Drive */
#define ADR2_LCD_COM_SEG            (* (reg8 *) ADR2__LCD_COM_SEG)
/* Enable Segment LCD */
#define ADR2_LCD_EN                 (* (reg8 *) ADR2__LCD_EN)
/* Slew Rate Control */
#define ADR2_SLW                    (* (reg8 *) ADR2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ADR2_PRTDSI__CAPS_SEL       (* (reg8 *) ADR2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ADR2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ADR2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ADR2_PRTDSI__OE_SEL0        (* (reg8 *) ADR2__PRTDSI__OE_SEL0) 
#define ADR2_PRTDSI__OE_SEL1        (* (reg8 *) ADR2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ADR2_PRTDSI__OUT_SEL0       (* (reg8 *) ADR2__PRTDSI__OUT_SEL0) 
#define ADR2_PRTDSI__OUT_SEL1       (* (reg8 *) ADR2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ADR2_PRTDSI__SYNC_OUT       (* (reg8 *) ADR2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ADR2__SIO_CFG)
    #define ADR2_SIO_HYST_EN        (* (reg8 *) ADR2__SIO_HYST_EN)
    #define ADR2_SIO_REG_HIFREQ     (* (reg8 *) ADR2__SIO_REG_HIFREQ)
    #define ADR2_SIO_CFG            (* (reg8 *) ADR2__SIO_CFG)
    #define ADR2_SIO_DIFF           (* (reg8 *) ADR2__SIO_DIFF)
#endif /* (ADR2__SIO_CFG) */

/* Interrupt Registers */
#if defined(ADR2__INTSTAT)
    #define ADR2_INTSTAT            (* (reg8 *) ADR2__INTSTAT)
    #define ADR2_SNAP               (* (reg8 *) ADR2__SNAP)
    
	#define ADR2_0_INTTYPE_REG 		(* (reg8 *) ADR2__0__INTTYPE)
#endif /* (ADR2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ADR2_H */


/* [] END OF FILE */

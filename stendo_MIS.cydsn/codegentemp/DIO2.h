/*******************************************************************************
* File Name: DIO2.h  
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

#if !defined(CY_PINS_DIO2_H) /* Pins DIO2_H */
#define CY_PINS_DIO2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIO2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIO2__PORT == 15 && ((DIO2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIO2_Write(uint8 value);
void    DIO2_SetDriveMode(uint8 mode);
uint8   DIO2_ReadDataReg(void);
uint8   DIO2_Read(void);
void    DIO2_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIO2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIO2_SetDriveMode() function.
     *  @{
     */
        #define DIO2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIO2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIO2_DM_RES_UP          PIN_DM_RES_UP
        #define DIO2_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIO2_DM_OD_LO           PIN_DM_OD_LO
        #define DIO2_DM_OD_HI           PIN_DM_OD_HI
        #define DIO2_DM_STRONG          PIN_DM_STRONG
        #define DIO2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIO2_MASK               DIO2__MASK
#define DIO2_SHIFT              DIO2__SHIFT
#define DIO2_WIDTH              1u

/* Interrupt constants */
#if defined(DIO2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIO2_SetInterruptMode() function.
     *  @{
     */
        #define DIO2_INTR_NONE      (uint16)(0x0000u)
        #define DIO2_INTR_RISING    (uint16)(0x0001u)
        #define DIO2_INTR_FALLING   (uint16)(0x0002u)
        #define DIO2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIO2_INTR_MASK      (0x01u) 
#endif /* (DIO2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIO2_PS                     (* (reg8 *) DIO2__PS)
/* Data Register */
#define DIO2_DR                     (* (reg8 *) DIO2__DR)
/* Port Number */
#define DIO2_PRT_NUM                (* (reg8 *) DIO2__PRT) 
/* Connect to Analog Globals */                                                  
#define DIO2_AG                     (* (reg8 *) DIO2__AG)                       
/* Analog MUX bux enable */
#define DIO2_AMUX                   (* (reg8 *) DIO2__AMUX) 
/* Bidirectional Enable */                                                        
#define DIO2_BIE                    (* (reg8 *) DIO2__BIE)
/* Bit-mask for Aliased Register Access */
#define DIO2_BIT_MASK               (* (reg8 *) DIO2__BIT_MASK)
/* Bypass Enable */
#define DIO2_BYP                    (* (reg8 *) DIO2__BYP)
/* Port wide control signals */                                                   
#define DIO2_CTL                    (* (reg8 *) DIO2__CTL)
/* Drive Modes */
#define DIO2_DM0                    (* (reg8 *) DIO2__DM0) 
#define DIO2_DM1                    (* (reg8 *) DIO2__DM1)
#define DIO2_DM2                    (* (reg8 *) DIO2__DM2) 
/* Input Buffer Disable Override */
#define DIO2_INP_DIS                (* (reg8 *) DIO2__INP_DIS)
/* LCD Common or Segment Drive */
#define DIO2_LCD_COM_SEG            (* (reg8 *) DIO2__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIO2_LCD_EN                 (* (reg8 *) DIO2__LCD_EN)
/* Slew Rate Control */
#define DIO2_SLW                    (* (reg8 *) DIO2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIO2_PRTDSI__CAPS_SEL       (* (reg8 *) DIO2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIO2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIO2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIO2_PRTDSI__OE_SEL0        (* (reg8 *) DIO2__PRTDSI__OE_SEL0) 
#define DIO2_PRTDSI__OE_SEL1        (* (reg8 *) DIO2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIO2_PRTDSI__OUT_SEL0       (* (reg8 *) DIO2__PRTDSI__OUT_SEL0) 
#define DIO2_PRTDSI__OUT_SEL1       (* (reg8 *) DIO2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIO2_PRTDSI__SYNC_OUT       (* (reg8 *) DIO2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIO2__SIO_CFG)
    #define DIO2_SIO_HYST_EN        (* (reg8 *) DIO2__SIO_HYST_EN)
    #define DIO2_SIO_REG_HIFREQ     (* (reg8 *) DIO2__SIO_REG_HIFREQ)
    #define DIO2_SIO_CFG            (* (reg8 *) DIO2__SIO_CFG)
    #define DIO2_SIO_DIFF           (* (reg8 *) DIO2__SIO_DIFF)
#endif /* (DIO2__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIO2__INTSTAT)
    #define DIO2_INTSTAT            (* (reg8 *) DIO2__INTSTAT)
    #define DIO2_SNAP               (* (reg8 *) DIO2__SNAP)
    
	#define DIO2_0_INTTYPE_REG 		(* (reg8 *) DIO2__0__INTTYPE)
#endif /* (DIO2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIO2_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: DIO4.h  
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

#if !defined(CY_PINS_DIO4_H) /* Pins DIO4_H */
#define CY_PINS_DIO4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIO4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIO4__PORT == 15 && ((DIO4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIO4_Write(uint8 value);
void    DIO4_SetDriveMode(uint8 mode);
uint8   DIO4_ReadDataReg(void);
uint8   DIO4_Read(void);
void    DIO4_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIO4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIO4_SetDriveMode() function.
     *  @{
     */
        #define DIO4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIO4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIO4_DM_RES_UP          PIN_DM_RES_UP
        #define DIO4_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIO4_DM_OD_LO           PIN_DM_OD_LO
        #define DIO4_DM_OD_HI           PIN_DM_OD_HI
        #define DIO4_DM_STRONG          PIN_DM_STRONG
        #define DIO4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIO4_MASK               DIO4__MASK
#define DIO4_SHIFT              DIO4__SHIFT
#define DIO4_WIDTH              1u

/* Interrupt constants */
#if defined(DIO4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIO4_SetInterruptMode() function.
     *  @{
     */
        #define DIO4_INTR_NONE      (uint16)(0x0000u)
        #define DIO4_INTR_RISING    (uint16)(0x0001u)
        #define DIO4_INTR_FALLING   (uint16)(0x0002u)
        #define DIO4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIO4_INTR_MASK      (0x01u) 
#endif /* (DIO4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIO4_PS                     (* (reg8 *) DIO4__PS)
/* Data Register */
#define DIO4_DR                     (* (reg8 *) DIO4__DR)
/* Port Number */
#define DIO4_PRT_NUM                (* (reg8 *) DIO4__PRT) 
/* Connect to Analog Globals */                                                  
#define DIO4_AG                     (* (reg8 *) DIO4__AG)                       
/* Analog MUX bux enable */
#define DIO4_AMUX                   (* (reg8 *) DIO4__AMUX) 
/* Bidirectional Enable */                                                        
#define DIO4_BIE                    (* (reg8 *) DIO4__BIE)
/* Bit-mask for Aliased Register Access */
#define DIO4_BIT_MASK               (* (reg8 *) DIO4__BIT_MASK)
/* Bypass Enable */
#define DIO4_BYP                    (* (reg8 *) DIO4__BYP)
/* Port wide control signals */                                                   
#define DIO4_CTL                    (* (reg8 *) DIO4__CTL)
/* Drive Modes */
#define DIO4_DM0                    (* (reg8 *) DIO4__DM0) 
#define DIO4_DM1                    (* (reg8 *) DIO4__DM1)
#define DIO4_DM2                    (* (reg8 *) DIO4__DM2) 
/* Input Buffer Disable Override */
#define DIO4_INP_DIS                (* (reg8 *) DIO4__INP_DIS)
/* LCD Common or Segment Drive */
#define DIO4_LCD_COM_SEG            (* (reg8 *) DIO4__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIO4_LCD_EN                 (* (reg8 *) DIO4__LCD_EN)
/* Slew Rate Control */
#define DIO4_SLW                    (* (reg8 *) DIO4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIO4_PRTDSI__CAPS_SEL       (* (reg8 *) DIO4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIO4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIO4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIO4_PRTDSI__OE_SEL0        (* (reg8 *) DIO4__PRTDSI__OE_SEL0) 
#define DIO4_PRTDSI__OE_SEL1        (* (reg8 *) DIO4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIO4_PRTDSI__OUT_SEL0       (* (reg8 *) DIO4__PRTDSI__OUT_SEL0) 
#define DIO4_PRTDSI__OUT_SEL1       (* (reg8 *) DIO4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIO4_PRTDSI__SYNC_OUT       (* (reg8 *) DIO4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIO4__SIO_CFG)
    #define DIO4_SIO_HYST_EN        (* (reg8 *) DIO4__SIO_HYST_EN)
    #define DIO4_SIO_REG_HIFREQ     (* (reg8 *) DIO4__SIO_REG_HIFREQ)
    #define DIO4_SIO_CFG            (* (reg8 *) DIO4__SIO_CFG)
    #define DIO4_SIO_DIFF           (* (reg8 *) DIO4__SIO_DIFF)
#endif /* (DIO4__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIO4__INTSTAT)
    #define DIO4_INTSTAT            (* (reg8 *) DIO4__INTSTAT)
    #define DIO4_SNAP               (* (reg8 *) DIO4__SNAP)
    
	#define DIO4_0_INTTYPE_REG 		(* (reg8 *) DIO4__0__INTTYPE)
#endif /* (DIO4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIO4_H */


/* [] END OF FILE */

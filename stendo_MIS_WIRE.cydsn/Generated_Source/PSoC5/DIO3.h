/*******************************************************************************
* File Name: DIO3.h  
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

#if !defined(CY_PINS_DIO3_H) /* Pins DIO3_H */
#define CY_PINS_DIO3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIO3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIO3__PORT == 15 && ((DIO3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIO3_Write(uint8 value);
void    DIO3_SetDriveMode(uint8 mode);
uint8   DIO3_ReadDataReg(void);
uint8   DIO3_Read(void);
void    DIO3_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIO3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIO3_SetDriveMode() function.
     *  @{
     */
        #define DIO3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIO3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIO3_DM_RES_UP          PIN_DM_RES_UP
        #define DIO3_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIO3_DM_OD_LO           PIN_DM_OD_LO
        #define DIO3_DM_OD_HI           PIN_DM_OD_HI
        #define DIO3_DM_STRONG          PIN_DM_STRONG
        #define DIO3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIO3_MASK               DIO3__MASK
#define DIO3_SHIFT              DIO3__SHIFT
#define DIO3_WIDTH              1u

/* Interrupt constants */
#if defined(DIO3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIO3_SetInterruptMode() function.
     *  @{
     */
        #define DIO3_INTR_NONE      (uint16)(0x0000u)
        #define DIO3_INTR_RISING    (uint16)(0x0001u)
        #define DIO3_INTR_FALLING   (uint16)(0x0002u)
        #define DIO3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIO3_INTR_MASK      (0x01u) 
#endif /* (DIO3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIO3_PS                     (* (reg8 *) DIO3__PS)
/* Data Register */
#define DIO3_DR                     (* (reg8 *) DIO3__DR)
/* Port Number */
#define DIO3_PRT_NUM                (* (reg8 *) DIO3__PRT) 
/* Connect to Analog Globals */                                                  
#define DIO3_AG                     (* (reg8 *) DIO3__AG)                       
/* Analog MUX bux enable */
#define DIO3_AMUX                   (* (reg8 *) DIO3__AMUX) 
/* Bidirectional Enable */                                                        
#define DIO3_BIE                    (* (reg8 *) DIO3__BIE)
/* Bit-mask for Aliased Register Access */
#define DIO3_BIT_MASK               (* (reg8 *) DIO3__BIT_MASK)
/* Bypass Enable */
#define DIO3_BYP                    (* (reg8 *) DIO3__BYP)
/* Port wide control signals */                                                   
#define DIO3_CTL                    (* (reg8 *) DIO3__CTL)
/* Drive Modes */
#define DIO3_DM0                    (* (reg8 *) DIO3__DM0) 
#define DIO3_DM1                    (* (reg8 *) DIO3__DM1)
#define DIO3_DM2                    (* (reg8 *) DIO3__DM2) 
/* Input Buffer Disable Override */
#define DIO3_INP_DIS                (* (reg8 *) DIO3__INP_DIS)
/* LCD Common or Segment Drive */
#define DIO3_LCD_COM_SEG            (* (reg8 *) DIO3__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIO3_LCD_EN                 (* (reg8 *) DIO3__LCD_EN)
/* Slew Rate Control */
#define DIO3_SLW                    (* (reg8 *) DIO3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIO3_PRTDSI__CAPS_SEL       (* (reg8 *) DIO3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIO3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIO3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIO3_PRTDSI__OE_SEL0        (* (reg8 *) DIO3__PRTDSI__OE_SEL0) 
#define DIO3_PRTDSI__OE_SEL1        (* (reg8 *) DIO3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIO3_PRTDSI__OUT_SEL0       (* (reg8 *) DIO3__PRTDSI__OUT_SEL0) 
#define DIO3_PRTDSI__OUT_SEL1       (* (reg8 *) DIO3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIO3_PRTDSI__SYNC_OUT       (* (reg8 *) DIO3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIO3__SIO_CFG)
    #define DIO3_SIO_HYST_EN        (* (reg8 *) DIO3__SIO_HYST_EN)
    #define DIO3_SIO_REG_HIFREQ     (* (reg8 *) DIO3__SIO_REG_HIFREQ)
    #define DIO3_SIO_CFG            (* (reg8 *) DIO3__SIO_CFG)
    #define DIO3_SIO_DIFF           (* (reg8 *) DIO3__SIO_DIFF)
#endif /* (DIO3__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIO3__INTSTAT)
    #define DIO3_INTSTAT            (* (reg8 *) DIO3__INTSTAT)
    #define DIO3_SNAP               (* (reg8 *) DIO3__SNAP)
    
	#define DIO3_0_INTTYPE_REG 		(* (reg8 *) DIO3__0__INTTYPE)
#endif /* (DIO3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIO3_H */


/* [] END OF FILE */

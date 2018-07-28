/*******************************************************************************
* File Name: slv_miso.h  
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

#if !defined(CY_PINS_slv_miso_H) /* Pins slv_miso_H */
#define CY_PINS_slv_miso_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "slv_miso_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 slv_miso__PORT == 15 && ((slv_miso__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    slv_miso_Write(uint8 value);
void    slv_miso_SetDriveMode(uint8 mode);
uint8   slv_miso_ReadDataReg(void);
uint8   slv_miso_Read(void);
void    slv_miso_SetInterruptMode(uint16 position, uint16 mode);
uint8   slv_miso_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the slv_miso_SetDriveMode() function.
     *  @{
     */
        #define slv_miso_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define slv_miso_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define slv_miso_DM_RES_UP          PIN_DM_RES_UP
        #define slv_miso_DM_RES_DWN         PIN_DM_RES_DWN
        #define slv_miso_DM_OD_LO           PIN_DM_OD_LO
        #define slv_miso_DM_OD_HI           PIN_DM_OD_HI
        #define slv_miso_DM_STRONG          PIN_DM_STRONG
        #define slv_miso_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define slv_miso_MASK               slv_miso__MASK
#define slv_miso_SHIFT              slv_miso__SHIFT
#define slv_miso_WIDTH              1u

/* Interrupt constants */
#if defined(slv_miso__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in slv_miso_SetInterruptMode() function.
     *  @{
     */
        #define slv_miso_INTR_NONE      (uint16)(0x0000u)
        #define slv_miso_INTR_RISING    (uint16)(0x0001u)
        #define slv_miso_INTR_FALLING   (uint16)(0x0002u)
        #define slv_miso_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define slv_miso_INTR_MASK      (0x01u) 
#endif /* (slv_miso__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define slv_miso_PS                     (* (reg8 *) slv_miso__PS)
/* Data Register */
#define slv_miso_DR                     (* (reg8 *) slv_miso__DR)
/* Port Number */
#define slv_miso_PRT_NUM                (* (reg8 *) slv_miso__PRT) 
/* Connect to Analog Globals */                                                  
#define slv_miso_AG                     (* (reg8 *) slv_miso__AG)                       
/* Analog MUX bux enable */
#define slv_miso_AMUX                   (* (reg8 *) slv_miso__AMUX) 
/* Bidirectional Enable */                                                        
#define slv_miso_BIE                    (* (reg8 *) slv_miso__BIE)
/* Bit-mask for Aliased Register Access */
#define slv_miso_BIT_MASK               (* (reg8 *) slv_miso__BIT_MASK)
/* Bypass Enable */
#define slv_miso_BYP                    (* (reg8 *) slv_miso__BYP)
/* Port wide control signals */                                                   
#define slv_miso_CTL                    (* (reg8 *) slv_miso__CTL)
/* Drive Modes */
#define slv_miso_DM0                    (* (reg8 *) slv_miso__DM0) 
#define slv_miso_DM1                    (* (reg8 *) slv_miso__DM1)
#define slv_miso_DM2                    (* (reg8 *) slv_miso__DM2) 
/* Input Buffer Disable Override */
#define slv_miso_INP_DIS                (* (reg8 *) slv_miso__INP_DIS)
/* LCD Common or Segment Drive */
#define slv_miso_LCD_COM_SEG            (* (reg8 *) slv_miso__LCD_COM_SEG)
/* Enable Segment LCD */
#define slv_miso_LCD_EN                 (* (reg8 *) slv_miso__LCD_EN)
/* Slew Rate Control */
#define slv_miso_SLW                    (* (reg8 *) slv_miso__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define slv_miso_PRTDSI__CAPS_SEL       (* (reg8 *) slv_miso__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define slv_miso_PRTDSI__DBL_SYNC_IN    (* (reg8 *) slv_miso__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define slv_miso_PRTDSI__OE_SEL0        (* (reg8 *) slv_miso__PRTDSI__OE_SEL0) 
#define slv_miso_PRTDSI__OE_SEL1        (* (reg8 *) slv_miso__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define slv_miso_PRTDSI__OUT_SEL0       (* (reg8 *) slv_miso__PRTDSI__OUT_SEL0) 
#define slv_miso_PRTDSI__OUT_SEL1       (* (reg8 *) slv_miso__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define slv_miso_PRTDSI__SYNC_OUT       (* (reg8 *) slv_miso__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(slv_miso__SIO_CFG)
    #define slv_miso_SIO_HYST_EN        (* (reg8 *) slv_miso__SIO_HYST_EN)
    #define slv_miso_SIO_REG_HIFREQ     (* (reg8 *) slv_miso__SIO_REG_HIFREQ)
    #define slv_miso_SIO_CFG            (* (reg8 *) slv_miso__SIO_CFG)
    #define slv_miso_SIO_DIFF           (* (reg8 *) slv_miso__SIO_DIFF)
#endif /* (slv_miso__SIO_CFG) */

/* Interrupt Registers */
#if defined(slv_miso__INTSTAT)
    #define slv_miso_INTSTAT            (* (reg8 *) slv_miso__INTSTAT)
    #define slv_miso_SNAP               (* (reg8 *) slv_miso__SNAP)
    
	#define slv_miso_0_INTTYPE_REG 		(* (reg8 *) slv_miso__0__INTTYPE)
#endif /* (slv_miso__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_slv_miso_H */


/* [] END OF FILE */

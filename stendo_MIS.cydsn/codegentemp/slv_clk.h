/*******************************************************************************
* File Name: slv_clk.h  
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

#if !defined(CY_PINS_slv_clk_H) /* Pins slv_clk_H */
#define CY_PINS_slv_clk_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "slv_clk_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 slv_clk__PORT == 15 && ((slv_clk__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    slv_clk_Write(uint8 value);
void    slv_clk_SetDriveMode(uint8 mode);
uint8   slv_clk_ReadDataReg(void);
uint8   slv_clk_Read(void);
void    slv_clk_SetInterruptMode(uint16 position, uint16 mode);
uint8   slv_clk_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the slv_clk_SetDriveMode() function.
     *  @{
     */
        #define slv_clk_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define slv_clk_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define slv_clk_DM_RES_UP          PIN_DM_RES_UP
        #define slv_clk_DM_RES_DWN         PIN_DM_RES_DWN
        #define slv_clk_DM_OD_LO           PIN_DM_OD_LO
        #define slv_clk_DM_OD_HI           PIN_DM_OD_HI
        #define slv_clk_DM_STRONG          PIN_DM_STRONG
        #define slv_clk_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define slv_clk_MASK               slv_clk__MASK
#define slv_clk_SHIFT              slv_clk__SHIFT
#define slv_clk_WIDTH              1u

/* Interrupt constants */
#if defined(slv_clk__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in slv_clk_SetInterruptMode() function.
     *  @{
     */
        #define slv_clk_INTR_NONE      (uint16)(0x0000u)
        #define slv_clk_INTR_RISING    (uint16)(0x0001u)
        #define slv_clk_INTR_FALLING   (uint16)(0x0002u)
        #define slv_clk_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define slv_clk_INTR_MASK      (0x01u) 
#endif /* (slv_clk__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define slv_clk_PS                     (* (reg8 *) slv_clk__PS)
/* Data Register */
#define slv_clk_DR                     (* (reg8 *) slv_clk__DR)
/* Port Number */
#define slv_clk_PRT_NUM                (* (reg8 *) slv_clk__PRT) 
/* Connect to Analog Globals */                                                  
#define slv_clk_AG                     (* (reg8 *) slv_clk__AG)                       
/* Analog MUX bux enable */
#define slv_clk_AMUX                   (* (reg8 *) slv_clk__AMUX) 
/* Bidirectional Enable */                                                        
#define slv_clk_BIE                    (* (reg8 *) slv_clk__BIE)
/* Bit-mask for Aliased Register Access */
#define slv_clk_BIT_MASK               (* (reg8 *) slv_clk__BIT_MASK)
/* Bypass Enable */
#define slv_clk_BYP                    (* (reg8 *) slv_clk__BYP)
/* Port wide control signals */                                                   
#define slv_clk_CTL                    (* (reg8 *) slv_clk__CTL)
/* Drive Modes */
#define slv_clk_DM0                    (* (reg8 *) slv_clk__DM0) 
#define slv_clk_DM1                    (* (reg8 *) slv_clk__DM1)
#define slv_clk_DM2                    (* (reg8 *) slv_clk__DM2) 
/* Input Buffer Disable Override */
#define slv_clk_INP_DIS                (* (reg8 *) slv_clk__INP_DIS)
/* LCD Common or Segment Drive */
#define slv_clk_LCD_COM_SEG            (* (reg8 *) slv_clk__LCD_COM_SEG)
/* Enable Segment LCD */
#define slv_clk_LCD_EN                 (* (reg8 *) slv_clk__LCD_EN)
/* Slew Rate Control */
#define slv_clk_SLW                    (* (reg8 *) slv_clk__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define slv_clk_PRTDSI__CAPS_SEL       (* (reg8 *) slv_clk__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define slv_clk_PRTDSI__DBL_SYNC_IN    (* (reg8 *) slv_clk__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define slv_clk_PRTDSI__OE_SEL0        (* (reg8 *) slv_clk__PRTDSI__OE_SEL0) 
#define slv_clk_PRTDSI__OE_SEL1        (* (reg8 *) slv_clk__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define slv_clk_PRTDSI__OUT_SEL0       (* (reg8 *) slv_clk__PRTDSI__OUT_SEL0) 
#define slv_clk_PRTDSI__OUT_SEL1       (* (reg8 *) slv_clk__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define slv_clk_PRTDSI__SYNC_OUT       (* (reg8 *) slv_clk__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(slv_clk__SIO_CFG)
    #define slv_clk_SIO_HYST_EN        (* (reg8 *) slv_clk__SIO_HYST_EN)
    #define slv_clk_SIO_REG_HIFREQ     (* (reg8 *) slv_clk__SIO_REG_HIFREQ)
    #define slv_clk_SIO_CFG            (* (reg8 *) slv_clk__SIO_CFG)
    #define slv_clk_SIO_DIFF           (* (reg8 *) slv_clk__SIO_DIFF)
#endif /* (slv_clk__SIO_CFG) */

/* Interrupt Registers */
#if defined(slv_clk__INTSTAT)
    #define slv_clk_INTSTAT            (* (reg8 *) slv_clk__INTSTAT)
    #define slv_clk_SNAP               (* (reg8 *) slv_clk__SNAP)
    
	#define slv_clk_0_INTTYPE_REG 		(* (reg8 *) slv_clk__0__INTTYPE)
#endif /* (slv_clk__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_slv_clk_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: SPI1_CS.h  
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

#if !defined(CY_PINS_SPI1_CS_H) /* Pins SPI1_CS_H */
#define CY_PINS_SPI1_CS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SPI1_CS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SPI1_CS__PORT == 15 && ((SPI1_CS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SPI1_CS_Write(uint8 value);
void    SPI1_CS_SetDriveMode(uint8 mode);
uint8   SPI1_CS_ReadDataReg(void);
uint8   SPI1_CS_Read(void);
void    SPI1_CS_SetInterruptMode(uint16 position, uint16 mode);
uint8   SPI1_CS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SPI1_CS_SetDriveMode() function.
     *  @{
     */
        #define SPI1_CS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SPI1_CS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SPI1_CS_DM_RES_UP          PIN_DM_RES_UP
        #define SPI1_CS_DM_RES_DWN         PIN_DM_RES_DWN
        #define SPI1_CS_DM_OD_LO           PIN_DM_OD_LO
        #define SPI1_CS_DM_OD_HI           PIN_DM_OD_HI
        #define SPI1_CS_DM_STRONG          PIN_DM_STRONG
        #define SPI1_CS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SPI1_CS_MASK               SPI1_CS__MASK
#define SPI1_CS_SHIFT              SPI1_CS__SHIFT
#define SPI1_CS_WIDTH              1u

/* Interrupt constants */
#if defined(SPI1_CS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SPI1_CS_SetInterruptMode() function.
     *  @{
     */
        #define SPI1_CS_INTR_NONE      (uint16)(0x0000u)
        #define SPI1_CS_INTR_RISING    (uint16)(0x0001u)
        #define SPI1_CS_INTR_FALLING   (uint16)(0x0002u)
        #define SPI1_CS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SPI1_CS_INTR_MASK      (0x01u) 
#endif /* (SPI1_CS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SPI1_CS_PS                     (* (reg8 *) SPI1_CS__PS)
/* Data Register */
#define SPI1_CS_DR                     (* (reg8 *) SPI1_CS__DR)
/* Port Number */
#define SPI1_CS_PRT_NUM                (* (reg8 *) SPI1_CS__PRT) 
/* Connect to Analog Globals */                                                  
#define SPI1_CS_AG                     (* (reg8 *) SPI1_CS__AG)                       
/* Analog MUX bux enable */
#define SPI1_CS_AMUX                   (* (reg8 *) SPI1_CS__AMUX) 
/* Bidirectional Enable */                                                        
#define SPI1_CS_BIE                    (* (reg8 *) SPI1_CS__BIE)
/* Bit-mask for Aliased Register Access */
#define SPI1_CS_BIT_MASK               (* (reg8 *) SPI1_CS__BIT_MASK)
/* Bypass Enable */
#define SPI1_CS_BYP                    (* (reg8 *) SPI1_CS__BYP)
/* Port wide control signals */                                                   
#define SPI1_CS_CTL                    (* (reg8 *) SPI1_CS__CTL)
/* Drive Modes */
#define SPI1_CS_DM0                    (* (reg8 *) SPI1_CS__DM0) 
#define SPI1_CS_DM1                    (* (reg8 *) SPI1_CS__DM1)
#define SPI1_CS_DM2                    (* (reg8 *) SPI1_CS__DM2) 
/* Input Buffer Disable Override */
#define SPI1_CS_INP_DIS                (* (reg8 *) SPI1_CS__INP_DIS)
/* LCD Common or Segment Drive */
#define SPI1_CS_LCD_COM_SEG            (* (reg8 *) SPI1_CS__LCD_COM_SEG)
/* Enable Segment LCD */
#define SPI1_CS_LCD_EN                 (* (reg8 *) SPI1_CS__LCD_EN)
/* Slew Rate Control */
#define SPI1_CS_SLW                    (* (reg8 *) SPI1_CS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SPI1_CS_PRTDSI__CAPS_SEL       (* (reg8 *) SPI1_CS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SPI1_CS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SPI1_CS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SPI1_CS_PRTDSI__OE_SEL0        (* (reg8 *) SPI1_CS__PRTDSI__OE_SEL0) 
#define SPI1_CS_PRTDSI__OE_SEL1        (* (reg8 *) SPI1_CS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SPI1_CS_PRTDSI__OUT_SEL0       (* (reg8 *) SPI1_CS__PRTDSI__OUT_SEL0) 
#define SPI1_CS_PRTDSI__OUT_SEL1       (* (reg8 *) SPI1_CS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SPI1_CS_PRTDSI__SYNC_OUT       (* (reg8 *) SPI1_CS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SPI1_CS__SIO_CFG)
    #define SPI1_CS_SIO_HYST_EN        (* (reg8 *) SPI1_CS__SIO_HYST_EN)
    #define SPI1_CS_SIO_REG_HIFREQ     (* (reg8 *) SPI1_CS__SIO_REG_HIFREQ)
    #define SPI1_CS_SIO_CFG            (* (reg8 *) SPI1_CS__SIO_CFG)
    #define SPI1_CS_SIO_DIFF           (* (reg8 *) SPI1_CS__SIO_DIFF)
#endif /* (SPI1_CS__SIO_CFG) */

/* Interrupt Registers */
#if defined(SPI1_CS__INTSTAT)
    #define SPI1_CS_INTSTAT            (* (reg8 *) SPI1_CS__INTSTAT)
    #define SPI1_CS_SNAP               (* (reg8 *) SPI1_CS__SNAP)
    
	#define SPI1_CS_0_INTTYPE_REG 		(* (reg8 *) SPI1_CS__0__INTTYPE)
#endif /* (SPI1_CS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SPI1_CS_H */


/* [] END OF FILE */

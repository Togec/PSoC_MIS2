/*******************************************************************************
* File Name: SW1_LED2.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SW1_LED2_H) /* Pins SW1_LED2_H */
#define CY_PINS_SW1_LED2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SW1_LED2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SW1_LED2__PORT == 15 && ((SW1_LED2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SW1_LED2_Write(uint8 value) ;
void    SW1_LED2_SetDriveMode(uint8 mode) ;
uint8   SW1_LED2_ReadDataReg(void) ;
uint8   SW1_LED2_Read(void) ;
uint8   SW1_LED2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW1_LED2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SW1_LED2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SW1_LED2_DM_RES_UP          PIN_DM_RES_UP
#define SW1_LED2_DM_RES_DWN         PIN_DM_RES_DWN
#define SW1_LED2_DM_OD_LO           PIN_DM_OD_LO
#define SW1_LED2_DM_OD_HI           PIN_DM_OD_HI
#define SW1_LED2_DM_STRONG          PIN_DM_STRONG
#define SW1_LED2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SW1_LED2_MASK               SW1_LED2__MASK
#define SW1_LED2_SHIFT              SW1_LED2__SHIFT
#define SW1_LED2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW1_LED2_PS                     (* (reg8 *) SW1_LED2__PS)
/* Data Register */
#define SW1_LED2_DR                     (* (reg8 *) SW1_LED2__DR)
/* Port Number */
#define SW1_LED2_PRT_NUM                (* (reg8 *) SW1_LED2__PRT) 
/* Connect to Analog Globals */                                                  
#define SW1_LED2_AG                     (* (reg8 *) SW1_LED2__AG)                       
/* Analog MUX bux enable */
#define SW1_LED2_AMUX                   (* (reg8 *) SW1_LED2__AMUX) 
/* Bidirectional Enable */                                                        
#define SW1_LED2_BIE                    (* (reg8 *) SW1_LED2__BIE)
/* Bit-mask for Aliased Register Access */
#define SW1_LED2_BIT_MASK               (* (reg8 *) SW1_LED2__BIT_MASK)
/* Bypass Enable */
#define SW1_LED2_BYP                    (* (reg8 *) SW1_LED2__BYP)
/* Port wide control signals */                                                   
#define SW1_LED2_CTL                    (* (reg8 *) SW1_LED2__CTL)
/* Drive Modes */
#define SW1_LED2_DM0                    (* (reg8 *) SW1_LED2__DM0) 
#define SW1_LED2_DM1                    (* (reg8 *) SW1_LED2__DM1)
#define SW1_LED2_DM2                    (* (reg8 *) SW1_LED2__DM2) 
/* Input Buffer Disable Override */
#define SW1_LED2_INP_DIS                (* (reg8 *) SW1_LED2__INP_DIS)
/* LCD Common or Segment Drive */
#define SW1_LED2_LCD_COM_SEG            (* (reg8 *) SW1_LED2__LCD_COM_SEG)
/* Enable Segment LCD */
#define SW1_LED2_LCD_EN                 (* (reg8 *) SW1_LED2__LCD_EN)
/* Slew Rate Control */
#define SW1_LED2_SLW                    (* (reg8 *) SW1_LED2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SW1_LED2_PRTDSI__CAPS_SEL       (* (reg8 *) SW1_LED2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SW1_LED2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SW1_LED2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SW1_LED2_PRTDSI__OE_SEL0        (* (reg8 *) SW1_LED2__PRTDSI__OE_SEL0) 
#define SW1_LED2_PRTDSI__OE_SEL1        (* (reg8 *) SW1_LED2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SW1_LED2_PRTDSI__OUT_SEL0       (* (reg8 *) SW1_LED2__PRTDSI__OUT_SEL0) 
#define SW1_LED2_PRTDSI__OUT_SEL1       (* (reg8 *) SW1_LED2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SW1_LED2_PRTDSI__SYNC_OUT       (* (reg8 *) SW1_LED2__PRTDSI__SYNC_OUT) 


#if defined(SW1_LED2__INTSTAT)  /* Interrupt Registers */

    #define SW1_LED2_INTSTAT                (* (reg8 *) SW1_LED2__INTSTAT)
    #define SW1_LED2_SNAP                   (* (reg8 *) SW1_LED2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SW1_LED2_H */


/* [] END OF FILE */

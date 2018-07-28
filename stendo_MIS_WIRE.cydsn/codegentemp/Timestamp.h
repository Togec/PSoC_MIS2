/*******************************************************************************
* File Name: Timestamp.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_Timestamp_H)
#define CY_Timer_v2_60_Timestamp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Timestamp_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define Timestamp_Resolution                 8u
#define Timestamp_UsingFixedFunction         0u
#define Timestamp_UsingHWCaptureCounter      0u
#define Timestamp_SoftwareCaptureMode        0u
#define Timestamp_SoftwareTriggerMode        0u
#define Timestamp_UsingHWEnable              0u
#define Timestamp_EnableTriggerMode          0u
#define Timestamp_InterruptOnCaptureCount    0u
#define Timestamp_RunModeUsed                0u
#define Timestamp_ControlRegRemoved          0u

#if defined(Timestamp_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define Timestamp_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (Timestamp_UsingFixedFunction)
    #define Timestamp_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define Timestamp_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End Timestamp_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!Timestamp_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (Timestamp_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!Timestamp_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}Timestamp_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    Timestamp_Start(void) ;
void    Timestamp_Stop(void) ;

void    Timestamp_SetInterruptMode(uint8 interruptMode) ;
uint8   Timestamp_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define Timestamp_GetInterruptSource() Timestamp_ReadStatusRegister()

#if(!Timestamp_UDB_CONTROL_REG_REMOVED)
    uint8   Timestamp_ReadControlRegister(void) ;
    void    Timestamp_WriteControlRegister(uint8 control) ;
#endif /* (!Timestamp_UDB_CONTROL_REG_REMOVED) */

uint8  Timestamp_ReadPeriod(void) ;
void    Timestamp_WritePeriod(uint8 period) ;
uint8  Timestamp_ReadCounter(void) ;
void    Timestamp_WriteCounter(uint8 counter) ;
uint8  Timestamp_ReadCapture(void) ;
void    Timestamp_SoftwareCapture(void) ;

#if(!Timestamp_UsingFixedFunction) /* UDB Prototypes */
    #if (Timestamp_SoftwareCaptureMode)
        void    Timestamp_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!Timestamp_UsingFixedFunction) */

    #if (Timestamp_SoftwareTriggerMode)
        void    Timestamp_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (Timestamp_SoftwareTriggerMode) */

    #if (Timestamp_EnableTriggerMode)
        void    Timestamp_EnableTrigger(void) ;
        void    Timestamp_DisableTrigger(void) ;
    #endif /* (Timestamp_EnableTriggerMode) */


    #if(Timestamp_InterruptOnCaptureCount)
        void    Timestamp_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (Timestamp_InterruptOnCaptureCount) */

    #if (Timestamp_UsingHWCaptureCounter)
        void    Timestamp_SetCaptureCount(uint8 captureCount) ;
        uint8   Timestamp_ReadCaptureCount(void) ;
    #endif /* (Timestamp_UsingHWCaptureCounter) */

    void Timestamp_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void Timestamp_Init(void)          ;
void Timestamp_Enable(void)        ;
void Timestamp_SaveConfig(void)    ;
void Timestamp_RestoreConfig(void) ;
void Timestamp_Sleep(void)         ;
void Timestamp_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define Timestamp__B_TIMER__CM_NONE 0
#define Timestamp__B_TIMER__CM_RISINGEDGE 1
#define Timestamp__B_TIMER__CM_FALLINGEDGE 2
#define Timestamp__B_TIMER__CM_EITHEREDGE 3
#define Timestamp__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define Timestamp__B_TIMER__TM_NONE 0x00u
#define Timestamp__B_TIMER__TM_RISINGEDGE 0x04u
#define Timestamp__B_TIMER__TM_FALLINGEDGE 0x08u
#define Timestamp__B_TIMER__TM_EITHEREDGE 0x0Cu
#define Timestamp__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define Timestamp_INIT_PERIOD             255u
#define Timestamp_INIT_CAPTURE_MODE       ((uint8)((uint8)2u << Timestamp_CTRL_CAP_MODE_SHIFT))
#define Timestamp_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << Timestamp_CTRL_TRIG_MODE_SHIFT))
#if (Timestamp_UsingFixedFunction)
    #define Timestamp_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << Timestamp_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << Timestamp_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define Timestamp_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << Timestamp_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Timestamp_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Timestamp_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (Timestamp_UsingFixedFunction) */
#define Timestamp_INIT_CAPTURE_COUNT      (2u)
#define Timestamp_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << Timestamp_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (Timestamp_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define Timestamp_STATUS         (*(reg8 *) Timestamp_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define Timestamp_STATUS_MASK    (*(reg8 *) Timestamp_TimerHW__SR0 )
    #define Timestamp_CONTROL        (*(reg8 *) Timestamp_TimerHW__CFG0)
    #define Timestamp_CONTROL2       (*(reg8 *) Timestamp_TimerHW__CFG1)
    #define Timestamp_CONTROL2_PTR   ( (reg8 *) Timestamp_TimerHW__CFG1)
    #define Timestamp_RT1            (*(reg8 *) Timestamp_TimerHW__RT1)
    #define Timestamp_RT1_PTR        ( (reg8 *) Timestamp_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define Timestamp_CONTROL3       (*(reg8 *) Timestamp_TimerHW__CFG2)
        #define Timestamp_CONTROL3_PTR   ( (reg8 *) Timestamp_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define Timestamp_GLOBAL_ENABLE  (*(reg8 *) Timestamp_TimerHW__PM_ACT_CFG)
    #define Timestamp_GLOBAL_STBY_ENABLE  (*(reg8 *) Timestamp_TimerHW__PM_STBY_CFG)

    #define Timestamp_CAPTURE_LSB         (* (reg16 *) Timestamp_TimerHW__CAP0 )
    #define Timestamp_CAPTURE_LSB_PTR       ((reg16 *) Timestamp_TimerHW__CAP0 )
    #define Timestamp_PERIOD_LSB          (* (reg16 *) Timestamp_TimerHW__PER0 )
    #define Timestamp_PERIOD_LSB_PTR        ((reg16 *) Timestamp_TimerHW__PER0 )
    #define Timestamp_COUNTER_LSB         (* (reg16 *) Timestamp_TimerHW__CNT_CMP0 )
    #define Timestamp_COUNTER_LSB_PTR       ((reg16 *) Timestamp_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define Timestamp_BLOCK_EN_MASK                     Timestamp_TimerHW__PM_ACT_MSK
    #define Timestamp_BLOCK_STBY_EN_MASK                Timestamp_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define Timestamp_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define Timestamp_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define Timestamp_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define Timestamp_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define Timestamp_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define Timestamp_CTRL_ENABLE                        ((uint8)((uint8)0x01u << Timestamp_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Timestamp_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define Timestamp_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << Timestamp_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define Timestamp_CTRL_MODE_SHIFT                 0x01u
        #define Timestamp_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << Timestamp_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define Timestamp_CTRL_RCOD_SHIFT        0x02u
        #define Timestamp_CTRL_ENBL_SHIFT        0x00u
        #define Timestamp_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define Timestamp_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << Timestamp_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define Timestamp_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << Timestamp_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define Timestamp_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << Timestamp_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define Timestamp_CTRL_RCOD       ((uint8)((uint8)0x03u << Timestamp_CTRL_RCOD_SHIFT))
        #define Timestamp_CTRL_ENBL       ((uint8)((uint8)0x80u << Timestamp_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define Timestamp_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define Timestamp_RT1_MASK                        ((uint8)((uint8)0x03u << Timestamp_RT1_SHIFT))
    #define Timestamp_SYNC                            ((uint8)((uint8)0x03u << Timestamp_RT1_SHIFT))
    #define Timestamp_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define Timestamp_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << Timestamp_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define Timestamp_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << Timestamp_SYNCDSI_SHIFT))

    #define Timestamp_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << Timestamp_CTRL_MODE_SHIFT))
    #define Timestamp_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << Timestamp_CTRL_MODE_SHIFT))
    #define Timestamp_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << Timestamp_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Timestamp_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Timestamp_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Timestamp_STATUS_TC_INT_MASK_SHIFT        (Timestamp_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Timestamp_STATUS_CAPTURE_INT_MASK_SHIFT   (Timestamp_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define Timestamp_STATUS_TC                       ((uint8)((uint8)0x01u << Timestamp_STATUS_TC_SHIFT))
    #define Timestamp_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << Timestamp_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define Timestamp_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << Timestamp_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define Timestamp_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << Timestamp_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define Timestamp_STATUS              (* (reg8 *) Timestamp_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define Timestamp_STATUS_MASK         (* (reg8 *) Timestamp_TimerUDB_rstSts_stsreg__MASK_REG)
    #define Timestamp_STATUS_AUX_CTRL     (* (reg8 *) Timestamp_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define Timestamp_CONTROL             (* (reg8 *) Timestamp_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(Timestamp_Resolution <= 8u) /* 8-bit Timer */
        #define Timestamp_CAPTURE_LSB         (* (reg8 *) Timestamp_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define Timestamp_CAPTURE_LSB_PTR       ((reg8 *) Timestamp_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define Timestamp_PERIOD_LSB          (* (reg8 *) Timestamp_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define Timestamp_PERIOD_LSB_PTR        ((reg8 *) Timestamp_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define Timestamp_COUNTER_LSB         (* (reg8 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define Timestamp_COUNTER_LSB_PTR       ((reg8 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(Timestamp_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define Timestamp_CAPTURE_LSB         (* (reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define Timestamp_CAPTURE_LSB_PTR       ((reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define Timestamp_PERIOD_LSB          (* (reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define Timestamp_PERIOD_LSB_PTR        ((reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define Timestamp_COUNTER_LSB         (* (reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define Timestamp_COUNTER_LSB_PTR       ((reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define Timestamp_CAPTURE_LSB         (* (reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define Timestamp_CAPTURE_LSB_PTR       ((reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define Timestamp_PERIOD_LSB          (* (reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define Timestamp_PERIOD_LSB_PTR        ((reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define Timestamp_COUNTER_LSB         (* (reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define Timestamp_COUNTER_LSB_PTR       ((reg16 *) Timestamp_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(Timestamp_Resolution <= 24u)/* 24-bit Timer */
        #define Timestamp_CAPTURE_LSB         (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define Timestamp_CAPTURE_LSB_PTR       ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define Timestamp_PERIOD_LSB          (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define Timestamp_PERIOD_LSB_PTR        ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define Timestamp_COUNTER_LSB         (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define Timestamp_COUNTER_LSB_PTR       ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define Timestamp_CAPTURE_LSB         (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define Timestamp_CAPTURE_LSB_PTR       ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define Timestamp_PERIOD_LSB          (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define Timestamp_PERIOD_LSB_PTR        ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define Timestamp_COUNTER_LSB         (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define Timestamp_COUNTER_LSB_PTR       ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define Timestamp_CAPTURE_LSB         (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define Timestamp_CAPTURE_LSB_PTR       ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define Timestamp_PERIOD_LSB          (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define Timestamp_PERIOD_LSB_PTR        ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define Timestamp_COUNTER_LSB         (* (reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define Timestamp_COUNTER_LSB_PTR       ((reg32 *) Timestamp_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define Timestamp_COUNTER_LSB_PTR_8BIT       ((reg8 *) Timestamp_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (Timestamp_UsingHWCaptureCounter)
        #define Timestamp_CAP_COUNT              (*(reg8 *) Timestamp_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Timestamp_CAP_COUNT_PTR          ( (reg8 *) Timestamp_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Timestamp_CAPTURE_COUNT_CTRL     (*(reg8 *) Timestamp_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define Timestamp_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) Timestamp_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (Timestamp_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define Timestamp_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define Timestamp_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define Timestamp_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define Timestamp_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define Timestamp_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define Timestamp_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << Timestamp_CTRL_INTCNT_SHIFT))
    #define Timestamp_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << Timestamp_CTRL_TRIG_MODE_SHIFT))
    #define Timestamp_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << Timestamp_CTRL_TRIG_EN_SHIFT))
    #define Timestamp_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << Timestamp_CTRL_CAP_MODE_SHIFT))
    #define Timestamp_CTRL_ENABLE                    ((uint8)((uint8)0x01u << Timestamp_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define Timestamp_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define Timestamp_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define Timestamp_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define Timestamp_STATUS_TC_INT_MASK_SHIFT       Timestamp_STATUS_TC_SHIFT
    #define Timestamp_STATUS_CAPTURE_INT_MASK_SHIFT  Timestamp_STATUS_CAPTURE_SHIFT
    #define Timestamp_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define Timestamp_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define Timestamp_STATUS_FIFOFULL_INT_MASK_SHIFT Timestamp_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define Timestamp_STATUS_TC                      ((uint8)((uint8)0x01u << Timestamp_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define Timestamp_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << Timestamp_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timestamp_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << Timestamp_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timestamp_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << Timestamp_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define Timestamp_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << Timestamp_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define Timestamp_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << Timestamp_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timestamp_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << Timestamp_STATUS_FIFOFULL_SHIFT))

    #define Timestamp_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define Timestamp_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define Timestamp_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define Timestamp_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define Timestamp_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define Timestamp_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_Timestamp_H */


/* [] END OF FILE */

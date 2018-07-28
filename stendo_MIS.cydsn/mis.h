#ifndef __MIS_H__
#define __MIS_H__

extern void MIS1_SetBurstTimeout(uint32 t);
extern int MIS1_Measure(uint32 time_ms);
extern uint32 MIS1_ReadCount(void);
extern uint32 MIS1_ReadTotTime(void);
extern uint32 MIS1_ReadCurTime(void);
extern uint32 MIS1_LastPulseTime(void);

extern void MIS2_SetBurstTimeout(uint32 t);
extern int MIS2_Measure(uint32 time_ms);
extern uint32 MIS2_ReadCount(void);
extern uint32 MIS2_ReadTotTime(void);
extern uint32 MIS2_ReadCurTime(void);

extern void MIS3_SetBurstTimeout(uint32 t);
extern int MIS3_Measure(uint32 time_ms);
extern uint32 MIS3_ReadCount(void);
extern uint32 MIS3_ReadTotTime(void);
extern uint32 MIS3_ReadCurTime(void);

extern void MIS4_SetBurstTimeout(uint32 t);
extern int MIS4_Measure(uint32 time_ms);
extern uint32 MIS4_ReadCount(void);
extern uint32 MIS4_ReadTotTime(void);
extern uint32 MIS4_ReadCurTime(void);

extern void MIS_Start(void);
extern void MIS_Stop(void);
extern int MIS_WaitPacket(void);
extern int MIS_PulseCounterStatus(void);

extern CY_ISR(isr_QuadDec_1_handler);
extern CY_ISR(isr_QuadDec_2_handler);

extern CY_ISR(isr_PulseCounter_1_handler);
extern CY_ISR(isr_Capture_1);

extern CY_ISR(isr_PulseCounter_2_handler);
extern CY_ISR(isr_Capture_2);

extern CY_ISR(isr_PulseCounter_3_handler);
extern CY_ISR(isr_Capture_3);

extern CY_ISR(isr_PulseCounter_4_handler);
extern CY_ISR(isr_Capture_4);


extern CY_ISR(isr_Timestamp_handler);

#endif

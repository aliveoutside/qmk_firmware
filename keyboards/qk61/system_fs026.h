#ifndef __SYSTEM_FS026_H__
#define __SYSTEM_FS026_H__

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int SystemCoreClock;
extern unsigned int SystemFrequency_SysClk;
extern unsigned int SystemFrequency_AHBClk;
extern unsigned int SystemFrequency_APBClk;
extern unsigned int HRC48Frequency;
extern unsigned int PLL0Frequency;

extern void SystemInit(void);

#ifdef __cplusplus
}
#endif

#endif

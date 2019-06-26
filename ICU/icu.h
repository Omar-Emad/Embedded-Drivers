/**********************************************************
 *
 * File Name: icu.h
 *
 * Author: Omar Emad
 *
 * Date Created: 20/10/2018
 *
 * File Description: The Header file for ICU driver
 *
 **********************************************************/

#ifndef ICU_H_
#define ICU_H_


#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/***************************************************************
 *                  Types Declaration                          *
 ***************************************************************/
typedef enum
{
	FALLING,RISING
}ICU_edgeType;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_prescaler;

typedef struct
{
	ICU_edgeType edge;
	ICU_prescaler prescaler;
	bool interruptEnable;
} ICU_configType;

/*****************************************************************
 *                   Functions Prototypes                        *
 *****************************************************************/

void ICU_init (ICU_configType * ICU_config);
uint16 ICU_getInputCaptureValue(void);
void ICU_clearTimerValue(void);
void ICU_setEdgeDetectionType(const ICU_edgeType edgeType);
void ICU_setCallBack (void (*a_callBackptr)(void));
void ICU_DeInit(void);



#endif /* ICU_H_ */

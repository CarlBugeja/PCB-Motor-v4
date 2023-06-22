/**
  PWM Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm.h

  @Summary
    This is the generated header file for the PWM driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for PWM.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33EP64MC202
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _PWM_H
#define _PWM_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data Types
*/
/** PWM Driver Specific Macro Definition
 
 @Summary 
   Defines the PWM driver specific macro definitions.
 
 @Description
   This routine defines the PWM driver specific macro definitions.
 
 Remarks:
   None
 */
#define PWM_OVERRIDE_DATA_MASK                  0x00c0
#define PWM_OVERRIDE_DATA_POSITION              6
#define PWM_OVERRIDE_DATA_HIGH_MASK             0x0080
#define PWM_OVERRIDE_DATA_HIGH_POSITION         7
#define PWM_OVERRIDE_DATA_LOW_MASK              0x0040
#define PWM_OVERRIDE_DATA_LOW_POSITION          6
#define PWM_OVERRIDE_HIGH_MASK                  0x0200
#define PWM_OVERRIDE_LOW_MASK                   0x0100
#define PWM_FAULT_LATCH_MASK                    0x0003
#define PWM_FAULT_LATCH_POSITION                0
#define PWM_FAULT_LATCH_ENABLE_VALUE            0x0000
#define PWM_FAULT_LATCH_DISABLE_VALUE           0x0011

/** PWM Generator Definition
 
 @Summary 
   Defines the PWM generators available for PWM
 
 @Description
   This routine defines the PWM generators that are available for the module to use.
 
 Remarks:
   None
 */
typedef enum 
{
    PWM_GENERATOR_1 =  1,       
    PWM_GENERATOR_2 =  2,       
    PWM_GENERATOR_3 =  3,       
} PWM_GENERATOR;

/** PWM Generator Interrupt Definition
 
 @Summary 
   Defines the PWM generator interrupt available for PWM
 
 @Description
   This routine defines the PWM generator interrupt that are available for the module to use.
 
 Remarks:
   None
 */
typedef enum 
{
    PWM_GENERATOR_INTERRUPT_FAULT =  1,       
    PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT =  2,
    PWM_GENERATOR_INTERRUPT_TRIGGER =  3,	
} PWM_GENERATOR_INTERRUPT;

/**
  Section: Interface Routines
*/

/**
  @Summary
    Initializes PWM module.

  @Description
    This routine initializes PWM module, using the given initialization data. 

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    bool status;
    uint16_t masterPeriod,masterDutyCycle;
    uint16_t compareValue;

    compareValue = 0x1;

    masterPeriod = 0xFFFF;
    masterDutyCycle = 0xFF;


    PWM_Initialize();

    PWM_Disable();

    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_MasterPeriodSet(period);

    PWM_SpecialEventPrimaryInterruptDisable();
    PWM_SpecialEventTriggerInterruptFlagClear();
    PWM_SpecialEventPrimaryCompareValueSet(compareValue);
    PWM_SpecialEventPrimaryInterruptEnable();

    PWM_Enable();
    </code>
*/
void PWM_Initialize (void);

/**
  @Summary
    Enables the PWM module.

  @Description
    This routine is used to enable the PWM module.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_Enable();
    </code>
*/
inline static void PWM_Enable(void)
{
	PTCONbits.PTEN = true; 
}

/**
  @Summary
    Disables the PWM module.

  @Description
    This routine is used to disable the PWM module.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_Disable();
    </code>
*/
inline static void PWM_Disable(void)
{
	PTCONbits.PTEN = false; 
}

/**
  @Summary
    Sets the period value in count for the Primary Master Time Base generator.

  @Description
    This routine is used to set the period value in count for the Primary Master Time Base generator.

  @Param
    masterPeriod - Period value in count.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t masterPeriod;

    masterPeriod = 0xFF;
    
    PWM_MasterPeriodSet(masterPeriod);
    </code>
*/
inline static void PWM_MasterPeriodSet(uint16_t masterPeriod)
{
    PTPER = masterPeriod;
}

/**
  @Summary
    Used to set the PWM master duty cycle register.

  @Description
    This routine is used to set the PWM master duty cycle register.

  @Param
    masterDutyCycle - Master Duty Cyle value.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t masterDutyCycle;

    masterDutyCycle = 0xFF;
    
    PWM_MasterDutyCycleSet(masterDutyCycle);
    </code>
*/
inline static void PWM_MasterDutyCycleSet(uint16_t masterDutyCycle)
{
    MDC = masterDutyCycle;
}

/**
  @Summary
    Sets the period value in count for the PWM generator specific Time Base.

  @Description
    This routine is used to set the period value in count for the PWM generator specific Time Base.

  @Param
    genNum  - PWM generator number.
    period  - Period value in count.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t period;

    period = 0xFF;
    
    genNum = PWM_GENERATOR_1;
    PWM_PeriodSet(genNum, period);
    </code>
*/  
inline static void PWM_PeriodSet(PWM_GENERATOR genNum, uint16_t period)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PHASE1 = period;                
                break;       
        case PWM_GENERATOR_2:
                PHASE2 = period;                
                break;       
        case PWM_GENERATOR_3:
                PHASE3 = period;                
                break;       
        default:break;  
    }
}

/**
  @Summary
    Sets the PWM duty cycle value in count for the PWM Generator.

  @Description
    This routine is used to set the PWM duty cycle value in count for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum      - PWM generator number.
    dutyCycle   - Duty cycle value in count.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t dutyCycle;

    dutyCycle = 0xFF;
    
    genNum = PWM_GENERATOR_1;
    PWM_DutyCycleSet(genNum, dutyCycle);
    </code>
*/  
inline static void PWM_DutyCycleSet(PWM_GENERATOR genNum, uint16_t dutyCycle)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PDC1 = dutyCycle;                
                break;       
        case PWM_GENERATOR_2:
                PDC2 = dutyCycle;                
                break;       
        case PWM_GENERATOR_3:
                PDC3 = dutyCycle;                
                break;       
        default:break;  
    }
}

/**
  @Summary
    Updates PWM override data bits with the requested value for the PWM Generator.

  @Description
    This routine is used to updates PWM override data bits with the requested 
    value for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    overrideData    - Override data

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t overrideData;

    overrideData = 0x01;
    
    genNum = PWM_GENERATOR_1;
    PWM_OverrideDataSet(genNum, overrideData);
    </code>
*/  
inline static void PWM_OverrideDataSet(PWM_GENERATOR genNum, uint16_t overrideData)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                overrideData = ((overrideData & 0x0003)<< PWM_OVERRIDE_DATA_POSITION);
                overrideData = (IOCON1 & (~(PWM_OVERRIDE_DATA_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON1, overrideData, &PWMKEY); 
                break;       
        case PWM_GENERATOR_2:
                overrideData = ((overrideData & 0x0003)<< PWM_OVERRIDE_DATA_POSITION);
                overrideData = (IOCON2 & (~(PWM_OVERRIDE_DATA_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON2, overrideData, &PWMKEY); 
                break;       
        case PWM_GENERATOR_3:
                overrideData = ((overrideData & 0x0003)<< PWM_OVERRIDE_DATA_POSITION);
                overrideData = (IOCON3 & (~(PWM_OVERRIDE_DATA_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON3, overrideData, &PWMKEY); 
                break;       
        default:break;  
    }
}

/**
  @Summary
    Updates PWM override high data bit with the requested value for the PWM 
    Generator.

  @Description
    This routine is used to update PWM override high data bit with the 
    requested value for the PWM Generator selected by the argument 
    PWM_GENERATOR.

  @Param
    genNum              - PWM generator number.
    overrideDataHigh    - Override data

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    bool overrideDataHigh;

    overrideDataHigh = true;
    
    genNum = PWM_GENERATOR_1;
    PWM_OverrideDataHighSet(genNum, overrideDataHigh);
    </code>
*/  
inline static void PWM_OverrideDataHighSet(PWM_GENERATOR genNum, bool overrideDataHigh)
{
    uint16_t overrideData;
    
    switch(genNum) { 
        case PWM_GENERATOR_1:
                overrideData = (overrideDataHigh << PWM_OVERRIDE_DATA_HIGH_POSITION);
                overrideData = (IOCON1 & (~(PWM_OVERRIDE_DATA_HIGH_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON1, overrideData, &PWMKEY);
                break;       
        case PWM_GENERATOR_2:
                overrideData = (overrideDataHigh << PWM_OVERRIDE_DATA_HIGH_POSITION);
                overrideData = (IOCON2 & (~(PWM_OVERRIDE_DATA_HIGH_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON2, overrideData, &PWMKEY);
                break;       
        case PWM_GENERATOR_3:
                overrideData = (overrideDataHigh << PWM_OVERRIDE_DATA_HIGH_POSITION);
                overrideData = (IOCON3 & (~(PWM_OVERRIDE_DATA_HIGH_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON3, overrideData, &PWMKEY);
                break;       
        default:break;  
    }
}

/**
  @Summary
    Updates PWM override low data bit with the requested value 
    for the PWM Generator.

  @Description
    This routine is used to update PWM override low data bit with the requested 
    value for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum              - PWM generator number.
    overrideDataLow     - Override data

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    bool overrideDataLow;

    overrideDataLow = true;
    
    genNum = PWM_GENERATOR_1;
    PWM_OverrideDataLowSet(genNum, overrideDataLow);
    </code>
*/  
inline static void PWM_OverrideDataLowSet(PWM_GENERATOR genNum, bool overrideDataLow)
{
    uint16_t overrideData;
    
    switch(genNum) { 
        case PWM_GENERATOR_1:
                overrideData = (overrideDataLow << PWM_OVERRIDE_DATA_LOW_POSITION);
                overrideData = (IOCON1 & (~(PWM_OVERRIDE_DATA_LOW_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON1, overrideData, &PWMKEY);
                break;       
        case PWM_GENERATOR_2:
                overrideData = (overrideDataLow << PWM_OVERRIDE_DATA_LOW_POSITION);
                overrideData = (IOCON2 & (~(PWM_OVERRIDE_DATA_LOW_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON2, overrideData, &PWMKEY);
                break;       
        case PWM_GENERATOR_3:
                overrideData = (overrideDataLow << PWM_OVERRIDE_DATA_LOW_POSITION);
                overrideData = (IOCON3 & (~(PWM_OVERRIDE_DATA_LOW_MASK))) | overrideData;
                __builtin_write_PWMSFR(&IOCON3, overrideData, &PWMKEY);
                break;       
        default:break;  
    }
}

/**
  @Summary
    Gets PWM override value for the PWM Generator.

  @Description
    This routine is used to get PWM override value for the PWM Generator 
    selected by the argument PWM_GENERATOR.
	
  @Param
    genNum          - PWM generator number.

  @Returns
    Override data for the PWM Generator selected by the argument PWM_GENERATOR.
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t overrideData;
    
    genNum = PWM_GENERATOR_1;
    overrideData = PWM_OverrideDataGet(genNum, overrideData);
    </code>
*/
inline static uint16_t PWM_OverrideDataGet(PWM_GENERATOR genNum)
{
    uint16_t overrideData;
    switch(genNum) { 
        case PWM_GENERATOR_1:
                overrideData = IOCON1bits.OVRDAT;                 
                break;       
        case PWM_GENERATOR_2:
                overrideData = IOCON2bits.OVRDAT;                 
                break;       
        case PWM_GENERATOR_3:
                overrideData = IOCON3bits.OVRDAT;                 
                break;       
        default:break;  
    }
    return overrideData;
}

/**
  @Summary
    Enables PWM override on PWMH output for the PWM Generator.

  @Description
    This routine is used to enable PWM override on PWMH output for the 
    PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_OverrideHighEnable(genNum);
    </code>
*/  
inline static void PWM_OverrideHighEnable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                __builtin_write_PWMSFR(&IOCON1, (IOCON1 | (PWM_OVERRIDE_HIGH_MASK)), &PWMKEY); 
                break;       
        case PWM_GENERATOR_2:
                __builtin_write_PWMSFR(&IOCON2, (IOCON2 | (PWM_OVERRIDE_HIGH_MASK)), &PWMKEY); 
                break;       
        case PWM_GENERATOR_3:
                __builtin_write_PWMSFR(&IOCON3, (IOCON3 | (PWM_OVERRIDE_HIGH_MASK)), &PWMKEY); 
                break;       
        default:break;  
    }
}

/**
  @Summary
    Enables PWM override on PWML output for the PWM Generator.

  @Description
    This routine is used to enable PWM override on PWML output for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_OverrideLowEnable(genNum);
    </code>
*/  
inline static void PWM_OverrideLowEnable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                __builtin_write_PWMSFR(&IOCON1, (IOCON1 | (PWM_OVERRIDE_LOW_MASK)), &PWMKEY);
                break;       
        case PWM_GENERATOR_2:
                __builtin_write_PWMSFR(&IOCON2, (IOCON2 | (PWM_OVERRIDE_LOW_MASK)), &PWMKEY);
                break;       
        case PWM_GENERATOR_3:
                __builtin_write_PWMSFR(&IOCON3, (IOCON3 | (PWM_OVERRIDE_LOW_MASK)), &PWMKEY);
                break;       
        default:break;  
    }
}

/**
  @Summary
    Disables PWM override on PWMH output for the PWM Generator.

  @Description
    This routine is used to disable PWM override on PWMH output for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_OverrideHighDisable(genNum);
    </code>
*/  
inline static void PWM_OverrideHighDisable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                __builtin_write_PWMSFR(&IOCON1, (IOCON1 & (~(PWM_OVERRIDE_HIGH_MASK))), &PWMKEY);
                break;       
        case PWM_GENERATOR_2:
                __builtin_write_PWMSFR(&IOCON2, (IOCON2 & (~(PWM_OVERRIDE_HIGH_MASK))), &PWMKEY);
                break;       
        case PWM_GENERATOR_3:
                __builtin_write_PWMSFR(&IOCON3, (IOCON3 & (~(PWM_OVERRIDE_HIGH_MASK))), &PWMKEY);
                break;       
        default:break;  
    }
}

/**
  @Summary
    Disables PWM override on PWML output for the PWM Generator.

  @Description
    This routine is used to disable PWM override on PWML output for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_OverrideLowDisable(genNum);
    </code>
*/  
inline static void PWM_OverrideLowDisable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                __builtin_write_PWMSFR(&IOCON1, (IOCON1 & (~(PWM_OVERRIDE_LOW_MASK))), &PWMKEY);
                break;       
        case PWM_GENERATOR_2:
                __builtin_write_PWMSFR(&IOCON2, (IOCON2 & (~(PWM_OVERRIDE_LOW_MASK))), &PWMKEY);
                break;       
        case PWM_GENERATOR_3:
                __builtin_write_PWMSFR(&IOCON3, (IOCON3 & (~(PWM_OVERRIDE_LOW_MASK))), &PWMKEY);
                break;       
        default:break;  
    }
}

/**
  @Summary
    Updates PWM Deadtime low register with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM Deadtime low register with the requested 
    value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum      - PWM generator number.
    deadtimeLow - Deadtime low value.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t deadtimeLow;

    deadtimeLow = 0x01;
    
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, deadtimeLow);
    </code>
*/  
inline static void PWM_DeadTimeLowSet(PWM_GENERATOR genNum, uint16_t deadtimeLow)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                DTR1 = deadtimeLow;                
                break;          
        case PWM_GENERATOR_2:
                DTR2 = deadtimeLow;                
                break;          
        case PWM_GENERATOR_3:
                DTR3 = deadtimeLow;                
                break;          
        default:break;  
    }
}

/**
  @Summary
    Updates PWM Deadtime high register with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM Deadtime high register with the requested 
    value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    deadtimeHigh    - Deadtime high value.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t deadtimeHigh;

    deadtimeHigh = 0x01;
    
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, deadtimeHigh);
    </code>
*/  
inline static void PWM_DeadTimeHighSet(PWM_GENERATOR genNum, uint16_t deadtimeHigh)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                ALTDTR1 = deadtimeHigh;                
                break;   
        case PWM_GENERATOR_2:
                ALTDTR2 = deadtimeHigh;                
                break;   
        case PWM_GENERATOR_3:
                ALTDTR3 = deadtimeHigh;                
                break;   
        default:break;  
    }
}

/**
  @Summary
    Updates PWM Deadtime low and high register with the requested value for a specific PWM generator.

  @Description
    This routine is used to updates PWM Deadtime low and high register with the 
    requested value for a specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    deadtimeHigh    - Deadtime value.

  @Returns
    None
 
  @Example 
    <code>    
    uint16_t deadtime;

    deadtime = 0x01;
    
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, deadtime);
    </code>
*/  
inline static void PWM_DeadTimeSet(PWM_GENERATOR genNum, uint16_t deadtime)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                DTR1 = deadtime; 
                ALTDTR1 = deadtime;				
                break;   
        case PWM_GENERATOR_2:
                DTR2 = deadtime; 
                ALTDTR2 = deadtime;				
                break;   
        case PWM_GENERATOR_3:
                DTR3 = deadtime; 
                ALTDTR3 = deadtime;				
                break;   
        default:break;  
    }
}

/**
  @Summary
    Sets the PWM trigger compare value in count for the PWM Generator.

  @Description
    This routine is used to set the PWM trigger compare value in count 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    trigCompValue   - Trigger compare value in count.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t trigCompValue;

    trigCompValue = 0x01;
    
    genNum = PWM_GENERATOR_1;
    PWM_TriggerCompareValueSet(genNum, trigCompValue);
    </code>
*/  
inline static void PWM_TriggerCompareValueSet(PWM_GENERATOR genNum, uint16_t trigCompValue)
{
    switch(genNum) { 
        case PWM_GENERATOR_1: 
                TRIG1 = trigCompValue;               
                break;       
        case PWM_GENERATOR_2: 
                TRIG2 = trigCompValue;               
                break;       
        case PWM_GENERATOR_3: 
                TRIG3 = trigCompValue;               
                break;       
        default:break;  
    }
}

/**
  @Summary
    Enables interrupt requests for the PWM Generator.

  @Description
    This routine is used to enable interrupt requests for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    interrupt - PWM generator interrupt source.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    PWM_GENERATOR_INTERRUPT interrupt;
    
    genNum = PWM_GENERATOR_1;
    interrupt = PWM_GENERATOR_INTERRUPT_TRIGGER;
    PWM_GeneratorInterruptEnable(genNum, interrupt);
    </code>
*/ 
inline static void PWM_GeneratorInterruptEnable(PWM_GENERATOR genNum, PWM_GENERATOR_INTERRUPT interrupt)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON1bits.FLTIEN = true;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON1bits.CLIEN = true;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON1bits.TRGIEN = true;
							break;							
					default:break;  
				}              
                break; 
        case PWM_GENERATOR_2:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON2bits.FLTIEN = true;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON2bits.CLIEN = true;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON2bits.TRGIEN = true;
							break;							
					default:break;  
				}              
                break; 
        case PWM_GENERATOR_3:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON3bits.FLTIEN = true;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON3bits.CLIEN = true;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON3bits.TRGIEN = true;
							break;							
					default:break;  
				}              
                break; 
        default:break;  
    }
}

/**
  @Summary
    Disables interrupt requests for the PWM Generator.

  @Description
    This routine is used to disables interrupt requests for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    interrupt - PWM generator interrupt source.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    PWM_GENERATOR_INTERRUPT interrupt;
    
    genNum = PWM_GENERATOR_1;
    interrupt = PWM_GENERATOR_INTERRUPT_TRIGGER;
    PWM_GeneratorInterruptDisable(genNum, interrupt);
    </code>
*/ 
inline static void PWM_GeneratorInterruptDisable(PWM_GENERATOR genNum, PWM_GENERATOR_INTERRUPT interrupt)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON1bits.FLTIEN = false;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON1bits.CLIEN = false;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON1bits.TRGIEN = false;
							break;							
					default:break;  
				}              
                break;  
        case PWM_GENERATOR_2:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON2bits.FLTIEN = false;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON2bits.CLIEN = false;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON2bits.TRGIEN = false;
							break;							
					default:break;  
				}              
                break;  
        case PWM_GENERATOR_3:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON3bits.FLTIEN = false;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON3bits.CLIEN = false;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON3bits.TRGIEN = false;
							break;							
					default:break;  
				}              
                break;  
        default:break;  
    }
}

/**
  @Summary
    Clears PWM interrupt status for the PWM Generator.

  @Description
    This routine is used to clear PWM interrupt status for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    interrupt - PWM generator interrupt source.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    PWM_GENERATOR_INTERRUPT interrupt;
    
    genNum = PWM_GENERATOR_1;
    interrupt = PWM_GENERATOR_INTERRUPT_TRIGGER;
    PWM_GeneratorEventStatusClear(genNum, interrupt);
    </code>
*/
inline static void PWM_GeneratorEventStatusClear(PWM_GENERATOR genNum, PWM_GENERATOR_INTERRUPT interrupt)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON1bits.FLTIEN = false;
							PWMCON1bits.FLTIEN = true;							
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON1bits.CLIEN = false;
							PWMCON1bits.CLIEN = true;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON1bits.TRGIEN = false;
							PWMCON1bits.TRGIEN = true;
							break;							
					default:break;  
				}              
                break; 
        case PWM_GENERATOR_2:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON2bits.FLTIEN = false;
							PWMCON2bits.FLTIEN = true;							
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON2bits.CLIEN = false;
							PWMCON2bits.CLIEN = true;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON2bits.TRGIEN = false;
							PWMCON2bits.TRGIEN = true;
							break;							
					default:break;  
				}              
                break; 
        case PWM_GENERATOR_3:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							PWMCON3bits.FLTIEN = false;
							PWMCON3bits.FLTIEN = true;							
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							PWMCON3bits.CLIEN = false;
							PWMCON3bits.CLIEN = true;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							PWMCON3bits.TRGIEN = false;
							PWMCON3bits.TRGIEN = true;
							break;							
					default:break;  
				}              
                break; 
        default:break;  
    }
}

/**
  @Summary
    Gets PWM interrupt status for the PWM Generator.

  @Description
    This routine is used to get PWM interrupt status for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.
    interrupt - PWM generator interrupt source.

  @Returns
    true - Interrupt is pending.
	false - Interrupt is not pending.
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    PWM_GENERATOR_INTERRUPT interrupt;
    bool status;
    
    genNum = PWM_GENERATOR_1;
    interrupt = PWM_GENERATOR_INTERRUPT_TRIGGER;
    status = PWM_GeneratorEventStatusGet(genNum, interrupt);
    </code>
*/
inline static bool PWM_GeneratorEventStatusGet(PWM_GENERATOR genNum, PWM_GENERATOR_INTERRUPT interrupt)
{
    bool status = false;
	
    switch(genNum) { 
        case PWM_GENERATOR_1:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							status = PWMCON1bits.FLTSTAT;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							status = PWMCON1bits.CLSTAT;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							status = PWMCON1bits.TRGSTAT;
							break;							
					default:break;  
				}              
                break; 
        case PWM_GENERATOR_2:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							status = PWMCON2bits.FLTSTAT;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							status = PWMCON2bits.CLSTAT;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							status = PWMCON2bits.TRGSTAT;
							break;							
					default:break;  
				}              
                break; 
        case PWM_GENERATOR_3:
				switch(interrupt) { 
					case PWM_GENERATOR_INTERRUPT_FAULT:
							status = PWMCON3bits.FLTSTAT;               
							break;       
					case PWM_GENERATOR_INTERRUPT_CURRENT_LIMIT:
							status = PWMCON3bits.CLSTAT;
							break;
					case PWM_GENERATOR_INTERRUPT_TRIGGER:
							status = PWMCON3bits.TRGSTAT;
							break;							
					default:break;  
				}              
                break; 
        default:break;  
    }
	return status;
}

/**
  @Summary
    Sets the compare value in count for the Special Event Trigger from the Primary time base generator.

  @Description
    This routine is used to set the compare value in count for the Special Event Trigger from the Primary time base generator.

  @Param
    compareValue - Compare value in count.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t compareValue;

    compareValue = 0xFF;
    
    PWM_SpecialEventPrimaryCompareValueSet(compareValue);
    </code>
*/  
inline static void PWM_SpecialEventPrimaryCompareValueSet(uint16_t compareValue)
{
    SEVTCMP = compareValue;
}

/**
  @Summary
    Clears PWM Special Event Trigger interrupt request flag.

  @Description
    This routine is used to clear PWM Special Event Trigger interrupt request flag.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_SpecialEventTriggerInterruptFlagClear();
    </code>
*/ 
inline static void PWM_SpecialEventTriggerInterruptFlagClear(void)
{
    IFS3bits.PSEMIF = false;
}

/**
  @Summary
    Enables interrupt request for Special Event Trigger from the Primary time base generator.

  @Description
    This routine is used to enable interrupt request for Special Event Trigger from the Primary time base generator.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_SpecialEventPrimaryInterruptEnable();
    </code>
*/  
inline static void PWM_SpecialEventPrimaryInterruptEnable(void)
{
	PTCONbits.SEIEN = true; 
}

/**
  @Summary
    Disables interrupt request for Special Event Trigger from the Primary time base generator.

  @Description
    This routine is used to disable interrupt request for Special Event Trigger from the Primary time base generator.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_SpecialEventPrimaryInterruptDisable();
    </code>
*/  
inline static void PWM_SpecialEventPrimaryInterruptDisable(void)
{
	PTCONbits.SEIEN = false; 
}

/**
  @Summary
    Enables PWM latched fault mode for the PWM Generator.

  @Description
    This routine is used to enable PWM latched fault mode for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_FaultModeLatchEnable(genNum);
    </code>
*/ 
inline static void PWM_FaultModeLatchEnable(PWM_GENERATOR genNum)
{
    uint16_t faultValue;
    
    switch(genNum) { 
        case PWM_GENERATOR_1:
                faultValue = ((FCLCON1 & (~(PWM_FAULT_LATCH_MASK))) | PWM_FAULT_LATCH_ENABLE_VALUE);
                __builtin_write_PWMSFR(&FCLCON1, faultValue, &PWMKEY);
                break;       
        case PWM_GENERATOR_2:
                faultValue = ((FCLCON2 & (~(PWM_FAULT_LATCH_MASK))) | PWM_FAULT_LATCH_ENABLE_VALUE);
                __builtin_write_PWMSFR(&FCLCON2, faultValue, &PWMKEY);
                break;       
        case PWM_GENERATOR_3:
                faultValue = ((FCLCON3 & (~(PWM_FAULT_LATCH_MASK))) | PWM_FAULT_LATCH_ENABLE_VALUE);
                __builtin_write_PWMSFR(&FCLCON3, faultValue, &PWMKEY);
                break;       
        default:break;    
    }
}

/**
  @Summary
    Disables PWM latched fault mode for the PWM Generator selected by the 
    argument PWM_GENERATOR.

  @Description
    This routine is used to disable PWM latched fault mode for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_FaultModeLatchDisable(genNum);
    </code>
*/  
inline static void PWM_FaultModeLatchDisable(PWM_GENERATOR genNum)
{
    uint16_t faultValue;
    
    switch(genNum) { 
        case PWM_GENERATOR_1: 
                faultValue = ((FCLCON1 & (~(PWM_FAULT_LATCH_MASK))) | PWM_FAULT_LATCH_DISABLE_VALUE);
                __builtin_write_PWMSFR(&FCLCON1, faultValue, &PWMKEY);
                break;       
        case PWM_GENERATOR_2: 
                faultValue = ((FCLCON2 & (~(PWM_FAULT_LATCH_MASK))) | PWM_FAULT_LATCH_DISABLE_VALUE);
                __builtin_write_PWMSFR(&FCLCON2, faultValue, &PWMKEY);
                break;       
        case PWM_GENERATOR_3: 
                faultValue = ((FCLCON3 & (~(PWM_FAULT_LATCH_MASK))) | PWM_FAULT_LATCH_DISABLE_VALUE);
                __builtin_write_PWMSFR(&FCLCON3, faultValue, &PWMKEY);
                break;       
        default:break;   
    }   
}

/**
  @Summary
    Callback for PWM Special Event.

  @Description
    This routine is callback for PWM Special Event

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_SpecialEvent_CallBack();
    </code>
*/
void PWM_SpecialEvent_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PWM_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    <code>    
    PWM_SpecialEvent_Tasks();
    </code>
    
*/
void PWM_SpecialEvent_Tasks(void);

/**
  @Summary
    Callback for PWM Generator1.

  @Description
    This routine is callback for PWM Generator1

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_Generator1_CallBack();
    </code>
*/
void PWM_Generator1_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PWM_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    <code>    
    PWM_Generator1_Tasks();
    </code>   
*/
void PWM_Generator1_Tasks(void);

/**
  @Summary
    Callback for PWM Generator2.

  @Description
    This routine is callback for PWM Generator2

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_Generator2_CallBack();
    </code>
*/
void PWM_Generator2_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PWM_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    <code>    
    PWM_Generator2_Tasks();
    </code>   
*/
void PWM_Generator2_Tasks(void);

/**
  @Summary
    Callback for PWM Generator3.

  @Description
    This routine is callback for PWM Generator3

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_Generator3_CallBack();
    </code>
*/
void PWM_Generator3_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PWM_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    <code>    
    PWM_Generator3_Tasks();
    </code>   
*/
void PWM_Generator3_Tasks(void);


/*******************************************************************************

  !!! Deprecated Definitions and APIs !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/

/** PWM Primary Synchronization Polarity Definition
 
 @Summary 
   Defines the PWM Primary Synchronization Input/Output Polarity.
 
 @Description
   This routine defines the PWM Primary Synchronization Input/Output Polarity.
 
 Remarks:
   None
 */
typedef enum 
{
    PWM_PRIMARY_SYNC_INOUT_POLARITY_HIGH,
    PWM_PRIMARY_SYNC_INOUT_POLARITY_LOW
} PWM_PRIMARY_SYNC_INOUT_POLARITY;

/**
  @Summary
    Sets the period value in count for the Primary Master Time Base generator.

  @Description
    This routine is used to set the period value in count for the Primary Master Time Base generator.

  @Param
    period - Period value in count.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t period;

    period = 0xFF;
    
    PWM_PrimaryMasterPeriodSet(period);
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_MasterPeriodSet instead."))) PWM_PrimaryMasterPeriodSet(uint16_t period)
{
    PTPER = period;
}

/**
  @Summary
    Sets the period value in count for the PWM generator specific Time Base.

  @Description
    This routine is used to set the period value in count for the PWM generator specific Time Base.

  @Param
    genNum  - PWM generator number.
    period  - Period value in count.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t period;

    period = 0x01;
    
    genNum = PWM_GENERATOR_1;
    PWM_PeriodCenterAlignedModeSet(genNum, period);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_PeriodSet instead."))) PWM_PeriodCenterAlignedModeSet(PWM_GENERATOR genNum,uint16_t period)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PHASE1 = period;                
                break;       
        case PWM_GENERATOR_2:
                PHASE2 = period;                
                break;       
        case PWM_GENERATOR_3:
                PHASE3 = period;                
                break;       
        default:break;  
    }
}

/**
  @Summary
    Sets the PWM deadtime value in count for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Description
    This routine is used to set the PWM deadtime value in count for the 
    PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum      - PWM generator number.
    deadtime    - Dead time value in count

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t deadtime;

    deadtime = 0x01;
    
    genNum = PWM_GENERATOR_1;
    PWM_DeadTimeCenterAlignedModeSet(genNum, deadtime);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_DeadTimeHighSet instead."))) PWM_DeadTimeCenterAlignedModeSet(PWM_GENERATOR genNum,uint16_t deadtime)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                ALTDTR1 = deadtime;                
                break;       
        case PWM_GENERATOR_2:
                ALTDTR2 = deadtime;                
                break;       
        case PWM_GENERATOR_3:
                ALTDTR3 = deadtime;                
                break;       
        default:break;  
    }
}

/**
  @Summary
    Clears PWM interupt request flag for the PWM Generator selected by 
    the argument PWM_GENERATOR.

  @Description
    This routine is used to clear PWM interupt request flag for the 
    PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_InterruptFlagClear(genNum);
    </code>
*/ 
inline static void __attribute__((deprecated)) PWM_InterruptFlagClear(PWM_GENERATOR genNum)
{	
    switch(genNum) { 
        case PWM_GENERATOR_1:
                IFS5bits.PWM1IF = false;                 
                break;       
        case PWM_GENERATOR_2:
                IFS5bits.PWM2IF = false;                 
                break;       
        case PWM_GENERATOR_3:
                IFS6bits.PWM3IF = false;                 
                break;       
        default:break;    
    }
}

/**
  @Summary
    Enables the PWM module.

  @Description
    This routine is used to enable the PWM module.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_ModuleEnable();
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_Enable instead."))) PWM_ModuleEnable(void)
{
	PTCONbits.PTEN = true; 
}

/**
  @Summary
    Disables the PWM module.

  @Description
    This routine is used to disable the PWM module.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_ModuleDisable();
    </code>
*/
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_Disable instead."))) PWM_ModuleDisable(void)
{
	PTCONbits.PTEN = false; 
}

/**
  @Summary
    Sets the PWM trigger output divider value in count for the 
    PWM Generator selected by the argument PWM_GENERATOR.

  @Description
    This routine is used to set the PWM trigger output divider value in count 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum          - PWM generator number.
    trigDivValue    - Trigger value value in count

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t trigDivValue;

    trigDivValue = 0x01;
    
    genNum = PWM_GENERATOR_1;
    PWM_TriggerDividerSet(genNum, trigDivValue);
    </code>
*/  
inline static void __attribute__((deprecated)) PWM_TriggerDividerSet(PWM_GENERATOR genNum,uint16_t trigDivValue)
{
    switch(genNum) { 
        case PWM_GENERATOR_1: 
                TRGCON1bits.TRGDIV = trigDivValue;               
                break;       
        case PWM_GENERATOR_2: 
                TRGCON2bits.TRGDIV = trigDivValue;               
                break;       
        case PWM_GENERATOR_3: 
                TRGCON3bits.TRGDIV = trigDivValue;               
                break;       
        default:break;  
    }
}

/**
  @Summary
    Sets the PWM trigger start delay value in count for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Description
    This routine is used to set the PWM trigger start delay value in count
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum      - PWM generator number.
    delayValue  - Trigger start delay value in count

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    uint16_t delayValue;

    delayValue = 0x01;
    
    genNum = PWM_GENERATOR_1;
    PWM_TriggerStartDelaySet(genNum, delayValue);
    </code>
*/  
inline static void __attribute__((deprecated)) PWM_TriggerStartDelaySet(PWM_GENERATOR genNum,uint16_t delayValue)
{
    switch(genNum) { 
        case PWM_GENERATOR_1: 
                TRGCON1bits.TRGSTRT = delayValue;               
                break;       
        case PWM_GENERATOR_2: 
                TRGCON2bits.TRGSTRT = delayValue;               
                break;       
        case PWM_GENERATOR_3: 
                TRGCON3bits.TRGSTRT = delayValue;               
                break;       
        default:break;  
    }
}

/**
  @Summary
   Sets the postscaler value for the PWM special event trigger from the Primary time base generator.

  @Description
    This routine is used to set the postscaler value for the PWM special event trigger from the Primary time base generator.

  @Param
    postscaler - Special event postscaler value.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t postscaler;

    postscaler = 0xFF;

    PWM_SpecialEventPrimaryPostscalerSet(postscaler);
    </code>
*/  
inline static void __attribute__((deprecated)) PWM_SpecialEventPrimaryPostscalerSet(uint16_t postscaler)
{
    PTCONbits.SEVTPS = postscaler;
}

/**
  @Summary
    Enables synchronization output from the Primary PWM timebase generator.

  @Description
    This routine is used to enable synchronization output from the Primary PWM timebase generator.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_PrimarySyncOutputEnable();
    </code>
*/ 
inline static void __attribute__((deprecated)) PWM_PrimarySyncOutputEnable(void)
{
    PTCONbits.SYNCOEN = true; 
}

/**
  @Summary
    Disables synchronization output from the Primary PWM timebase generator.

  @Description
    This routine is used to disable synchronization output from the Primary PWM timebase generator.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    PWM_PrimarySyncOutputDisable();
    </code>
*/  
inline static void __attribute__((deprecated)) PWM_PrimarySyncOutputDisable(void)
{
    PTCONbits.SYNCOEN = false; 
}

/**
  @Summary
    Assigns the primary synchronization input/output polarity.

  @Description
    This routine is used to assign the primary synchronization input/output polarity.

  @Param
    polarity    -   Polarity to be set.

  @Returns
    None
 
  @Example 
    <code>    
        PWM_PRIMARY_SYNC_INOUT_POLARITY polarity = PWM_PRIMARY_SYNC_INOUT_POLARITY_LOW;
        PWM_PrimarySyncInputOutputPolaritySet(polarity);
    </code>
*/
inline static void __attribute__((deprecated)) PWM_PrimarySyncInputOutputPolaritySet(PWM_PRIMARY_SYNC_INOUT_POLARITY polarity)
{
    PTCONbits.SYNCPOL = polarity;
}

/**
  @Summary
    Clears PWM fault status for the PWM Generator selected by the 
    argument PWM_GENERATOR.

  @Description
    This routine is used to clear PWM fault status for the PWM 
    Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_FaultInterruptStatusClear(genNum);
    </code>
*/ 
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorEventStatusClear instead."))) PWM_FaultInterruptStatusClear(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PWMCON1bits.FLTIEN = false;
                PWMCON1bits.FLTIEN = true;                
                break;       
        case PWM_GENERATOR_2:
                PWMCON2bits.FLTIEN = false;
                PWMCON2bits.FLTIEN = true;                
                break;       
        case PWM_GENERATOR_3:
                PWMCON3bits.FLTIEN = false;
                PWMCON3bits.FLTIEN = true;                
                break;       
        default:break;    
    }
}

/**
  @Summary
    Gets PWM fault status for the PWM Generator selected by the 
    argument PWM_GENERATOR.

  @Description
    This routine is used to get PWM fault status for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    Fault interrupt status value.
 
  @Example 
    <code>    
    bool status;
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    status = PWM_FaultInterruptStatusGet(genNum);
    </code>
*/ 
inline static bool __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorEventStatusGet instead."))) PWM_FaultInterruptStatusGet(PWM_GENERATOR genNum)
{
    bool status = false;
    switch(genNum) { 
        case PWM_GENERATOR_1:
                status = PWMCON1bits.FLTSTAT;                
                break;       
        case PWM_GENERATOR_2:
                status = PWMCON2bits.FLTSTAT;                
                break;       
        case PWM_GENERATOR_3:
                status = PWMCON3bits.FLTSTAT;                
                break;       
        default:break;    
    }
    return status;
}

/**
  @Summary
    Enables fault event interrupt requests for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Description
    This routine is used to enable fault event interrupt requests 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_FaultInterruptEnable(genNum);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorInterruptEnable instead."))) PWM_FaultInterruptEnable(PWM_GENERATOR genNum)
{	
    switch(genNum) { 
        case PWM_GENERATOR_1: 
                PWMCON1bits.FLTIEN = true;               
                break;       
        case PWM_GENERATOR_2: 
                PWMCON2bits.FLTIEN = true;               
                break;       
        case PWM_GENERATOR_3: 
                PWMCON3bits.FLTIEN = true;               
                break;       
        default:break;  
    } 
}

/**
  @Summary
    Disables fault event interrupt requests for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Description
    This routine is used to disable fault event interrupt requests 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_FaultInterruptDisable(genNum);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorInterruptDisable instead."))) PWM_FaultInterruptDisable(PWM_GENERATOR genNum)
{	
    switch(genNum) { 
        case PWM_GENERATOR_1: 
                PWMCON1bits.FLTIEN = false;               
                break;       
        case PWM_GENERATOR_2: 
                PWMCON2bits.FLTIEN = false;               
                break;       
        case PWM_GENERATOR_3: 
                PWMCON3bits.FLTIEN = false;               
                break;       
        default:break;  
    }
}

/**
  @Summary
    Clears PWM current limit status for the PWM Generator selected 
    by the argument PWM_GENERATOR.

  @Description
    This routine is used to clear PWM current limit status 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_CurrentLimitInterruptStatusClear(genNum);
    </code>
*/ 
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorEventStatusClear instead."))) PWM_CurrentLimitInterruptStatusClear(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PWMCON1bits.CLIEN = false;
                PWMCON1bits.CLIEN = true;                
                break;       
        case PWM_GENERATOR_2:
                PWMCON2bits.CLIEN = false;
                PWMCON2bits.CLIEN = true;                
                break;       
        case PWM_GENERATOR_3:
                PWMCON3bits.CLIEN = false;
                PWMCON3bits.CLIEN = true;                
                break;       
        default:break;    
    }
}

/**
  @Summary
    Gets PWM current limit status for the PWM Generator selected 
    by the argument PWM_GENERATOR.

  @Description
    This routine is used to get PWM current limit status 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    Current Limit interrupt status value.
 
  @Example 
    <code>    
    bool status;
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    status = PWM_CurrentLimitInterruptStatusGet(genNum);
    </code>
*/  
inline static bool __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorEventStatusGet instead."))) PWM_CurrentLimitInterruptStatusGet(PWM_GENERATOR genNum)
{	
    bool status = false;
    switch(genNum) { 
        case PWM_GENERATOR_1:
                status = PWMCON1bits.CLSTAT;                
                break;       
        case PWM_GENERATOR_2:
                status = PWMCON2bits.CLSTAT;                
                break;       
        case PWM_GENERATOR_3:
                status = PWMCON3bits.CLSTAT;                
                break;       
        default:break;   
    }
    return status;
}

/**
  @Summary
    Enables current limit interrupt requests for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Description
    This routine is used to enable current limit interrupt requests 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_CurrentLimitInterruptEnable(genNum);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorInterruptEnable instead."))) PWM_CurrentLimitInterruptEnable(PWM_GENERATOR genNum)
{	
    switch(genNum) { 
        case PWM_GENERATOR_1: 
                PWMCON1bits.CLIEN = true;               
                break;       
        case PWM_GENERATOR_2: 
                PWMCON2bits.CLIEN = true;               
                break;       
        case PWM_GENERATOR_3: 
                PWMCON3bits.CLIEN = true;               
                break;       
        default:break;  
    }
}

/**
  @Summary
    Disables current limit interrupt requests for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Description
    This routine is used to disable current limit interrupt requests 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_CurrentLimitInterruptDisable(genNum);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorInterruptDisable instead."))) PWM_CurrentLimitInterruptDisable(PWM_GENERATOR genNum)
{	
     switch(genNum) { 
        case PWM_GENERATOR_1: 
                PWMCON1bits.CLIEN = false;               
                break;       
        case PWM_GENERATOR_2: 
                PWMCON2bits.CLIEN = false;               
                break;       
        case PWM_GENERATOR_3: 
                PWMCON3bits.CLIEN = false;               
                break;       
        default:break;  
    }
}

/**
  @Summary
    Clears PWM trigger status for the PWM Generator selected by the 
    argument PWM_GENERATOR.

  @Description
    This routine is used to clear PWM trigger status for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_TriggerInterruptStatusClear(genNum);
    </code>
*/ 
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorEventStatusClear instead."))) PWM_TriggerInterruptStatusClear(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PWMCON1bits.TRGIEN = false;
                PWMCON1bits.TRGIEN = true;                
                break;       
        case PWM_GENERATOR_2:
                PWMCON2bits.TRGIEN = false;
                PWMCON2bits.TRGIEN = true;                
                break;       
        case PWM_GENERATOR_3:
                PWMCON3bits.TRGIEN = false;
                PWMCON3bits.TRGIEN = true;                
                break;       
        default:break;    
    }
}

/**
  @Summary
    Gets PWM trigger status for the PWM Generator selected by the argument 
    PWM_GENERATOR.

  @Description
    This routine is used to get PWM trigger status for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    Trigger interrupt status value.
 
  @Example 
    <code>    
    bool status;
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    status = PWM_TriggerInterruptStatusGet(genNum);
    </code>
*/  
inline static bool __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorEventStatusGet instead."))) PWM_TriggerInterruptStatusGet(PWM_GENERATOR genNum)
{
    bool status = false;
    switch(genNum) { 
        case PWM_GENERATOR_1:
                status = PWMCON1bits.TRGSTAT;                
                break;       
        case PWM_GENERATOR_2:
                status = PWMCON2bits.TRGSTAT;                
                break;       
        case PWM_GENERATOR_3:
                status = PWMCON3bits.TRGSTAT;                
                break;       
        default:break;  
    }
    return status;
}

/**
  @Summary
    Enables trigger event interrupt requests for the PWM Generator 
    selected by the argument PWM_GENERATOR.

  @Description
    This routine is used to enable trigger event interrupt requests 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_TriggerInterruptEnable(genNum);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorInterruptEnable instead."))) PWM_TriggerInterruptEnable(PWM_GENERATOR genNum)
{	
     switch(genNum) { 
        case PWM_GENERATOR_1: 
                PWMCON1bits.TRGIEN = true;               
                break;       
        case PWM_GENERATOR_2: 
                PWMCON2bits.TRGIEN = true;               
                break;       
        case PWM_GENERATOR_3: 
                PWMCON3bits.TRGIEN = true;               
                break;       
        default:break;  
    }
}

/**
  @Summary
    Disables trigger event interrupt requests for the PWM Generator.

  @Description
    This routine is used to disable trigger event interrupt requests 
    for the PWM Generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>    
    PWM_GENERATOR genNum;
    
    genNum = PWM_GENERATOR_1;
    PWM_TriggerInterruptDisable(genNum);
    </code>
*/  
inline static void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse PWM_GeneratorInterruptDisable instead."))) PWM_TriggerInterruptDisable(PWM_GENERATOR genNum)
{	
     switch(genNum) { 
        case PWM_GENERATOR_1: 
                PWMCON1bits.TRGIEN = false;               
                break;       
        case PWM_GENERATOR_2: 
                PWMCON2bits.TRGIEN = false;               
                break;       
        case PWM_GENERATOR_3: 
                PWMCON3bits.TRGIEN = false;               
                break;       
        default:break;  
    }
}

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_PWM_H
    
/**
 End of File
*/

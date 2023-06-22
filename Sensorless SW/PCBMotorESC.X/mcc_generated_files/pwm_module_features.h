/**
  PWM Module Feature Header File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm_module_features.h

  @Summary
    This is the generated module feature header file for PWM driver 
    using PIC24 / dsPIC33 / PIC32MM MCUs.
    This file provides module feature list available on the selected device. 
    The macros defined in this file provides the flexibility to easily migrate the user
    application to other device which might have varied feature list.
         
    The content in this file is strictly "read only" and should not be altered.

  @Description
    This header file provides module feature list for PWM driver.
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

#ifndef PWM_MODULE_FEATURES
#define PWM_MODULE_FEATURES

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
        
/*******************************************************************************
********************************************************************************
******************************************************************************** 
                            ********IMPORTANT********

This file defines the PWM module feature C-macros available 
on the selected device. The macros defined in this file provides the 
flexibility to easily migrate the user application to other device which might 
have varied feature list.

The file has to be manually included in main.c, if the user intends to migrate the
application to another device which might have varied feature list.
  
  
 ***************The content in this file is strictly "read only" and should 
 not be altered. Failing to do so, the migration is not guaranteed.*************

********************************************************************************
********************************************************************************         
********************************************************************************/

/*******************************************************************************
            Macros defined for features supported in the device
*******************************************************************************/

/** PWM SPECIAL EVENT FEATURE
 
 @Summary 
   Defines the macro associated with PWM special event triggers.

 @APIs Supported:
   PWM_SpecialEventPrimaryCompareValueSet(uint16_t compareValue);
   PWM_SpecialEventTriggerInterruptFlagClear(void);
   PWM_SpecialEventPrimaryInterruptEnable(void);
   PWM_SpecialEventPrimaryInterruptDisable(void);

   Refer driver header file for detailed description of the APIs.
  
 @Remarks:
   None
 */ 
#define PWM_SPECIAL_EVENT_FEATURE_AVAILABLE  1

/*******************************************************************************
            Macros defined for features not supported in the device
*******************************************************************************/

/** PWM GENERATOR ENABLE FEATURE
 
 @Summary 
   Defines the macro associated with enabling PWM generators.
 
 @APIs Supported:
   NA
 
 @Remarks:
   None
 */     
#define PWM_GENERATOR_ENABLE_FEATURE_AVAILABLE   0       
                
/** PWM SOFTWARE UPDATE FEATURE
 
 @Summary 
   Defines the macro associated with PWM data update request feature.
 
 @APIs Supported:
   NA
  
 @Remarks:
   None
 */
#define PWM_SOFTWARE_UPDATE_FEATURE_AVAILABLE    0   
        
/** PWM FAULT LATCH SOFTWARE CLEAR FEATURE
 
 @Summary 
   Defines the macro associated with PWM fault latch clear through software.
 
 @APIs Supported:
   NA
 
 @Remarks:
   None
 */       
#define PWM_FAULT_LATCH_SOFTWARE_CLEAR_FEATURE_AVAILABLE 0            
        
/** PWM MULTIPLE TRIGGER FEATURE
 
 @Summary 
   Defines the macro associated with multiple triggers in the PWM.
 
 @APIs Supported:
   NA
  
 @Remarks:
   None
 */   
#define PWM_MULTIPLE_TRIGGER_FEATURE_AVAILABLE   0

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //PWM_MODULE_FEATURES
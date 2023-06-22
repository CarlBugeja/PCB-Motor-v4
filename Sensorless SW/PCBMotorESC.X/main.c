#include "mcc_generated_files/mcc.h"
#include "motor.h"
#include "libpic30.h" 

extern bool timer_flag;
uint16_t adc_phase1 = 0U;
uint16_t adc_phase2 = 0U;
uint16_t adc_phase3 = 0U;

int main(void)
{    
    SYSTEM_Initialize();/*initialize the device*/ 
                
    motor_init();
        
    while (1){
        if(timer_flag == 1){
            /*2us timer*/
            timer_flag = 0; 
            motor_handler(); 
            ClrWdt(); /*Clear Watchdog*/ 
        } 
        else{
            /*skip*/
        }
    }
}
/**
 End of File
*/


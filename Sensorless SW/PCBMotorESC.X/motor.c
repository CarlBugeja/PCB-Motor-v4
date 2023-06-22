#include "mcc_generated_files/mcc.h"
#include "motor.h"
#include "libpic30.h" 

extern uint16_t step_timer;

bool motor_dir = 0, speed_cl = 0, zerocross_flag = 0;
uint8_t sindex = 0u, signal_last  = 0U, StepNum = 3U;
uint32_t step_counts_calc = 0U;
uint16_t StepIndex = 0U, i = 0U, speed_counter = 0U, signal_high = 0U, signal_low = 0U, speed_dc = 1000U, speed_stimer = 0U, step_counts = 0U, speed_value = 999U, step_error = 0U, step_errorlast = 0U;
double temp_double = 0;
uint16_t step_counts_new[arraynum] = {240U};
uint16_t supply_new[6U] = {0U,0U,0U,0U,0U,0U};

void motor_stop(void){
    PDC3 = 0U;     
    PH2_L_OUT_SetLow();
    PDC1 = 0;
    PH3_L_OUT_SetLow();
    PDC2 = 0U;
    PH1_L_OUT_SetLow();
}

void motor_init(void){
    
    LED1_SetHigh();
    LED2_SetLow();
    
    step_timer = 0U;
    step_counts = INIT_SPEED;
    speed_value = INIT_SPEED;
    speed_dc = 1000U;
    
    for(i = 0U; i < 5000U; i++){
        __delay_us(60);  
        step_handler(0); /*Buzz the motor*/
    }
    __delay_ms(100);
    for(i = 0U; i < 10000U; i++){
        __delay_us(20);  
        step_handler(1); /*Buzz the motor*/
    }
    
    motor_stop();    
    __delay_ms(100);
        
    LED2_SetHigh();
    LED1_SetLow();
}

void signal_handler(void){    
    if(PORTBbits.RB4 == 1){
        if(signal_last == 0){
            /*Start a new Cycle*/
            temp_double = (signal_high/(signal_high + signal_low))*1000U;
            speed_stimer = (int16_t)temp_double;
            if(speed_stimer < DC_MIN){
                speed_stimer = DC_MIN;
            }
            signal_high = 0U;
            signal_low = 0U;
        }
        if(signal_high <= 65535U){
            signal_high++;
        }
        signal_last  = 1;
    }
    else{
        if(signal_low <= 65535U){
            signal_low++;
        }
        else{
            speed_stimer = DC_MIN;
            
        }
        signal_last = 0;
    }
}

void speed_handler(void){    
    /*Speed Control Algorithm*/
    if(speed_cl == 0){
        /*Open Loop Speed Control - Ramp up the Speed to detect Back-emf*/
        if(step_counts > 2U) { 
            if(step_counts > 400U){
                step_counts = step_counts - (step_counts>>8U);                
            }
            else{
                speed_counter++;
                if(speed_counter > 4U){
                    speed_counter = 0U;
                    step_counts--;
                }
                else{
                    /*skip*/
                }
            }
        } 
        else { 
            if(speed_dc > DC_MIN){
                speed_dc--;
             }
             else{
                speed_cl = 1; 
                for(i = 0U; i < arraynum; i++){
                   step_counts_new[i] = step_counts;
                }
             } 
        }
    }
    else{
        /*Closed Loop Speed Control*/   
        step_counts_calc = 0U;
        for(i = 0U; i < arraynum; i++){
           step_counts_calc = step_counts_calc + (uint32_t)step_counts_new[i];
        }
        step_counts_calc = step_counts_calc/arraynum;
        speed_counter++;
        if(speed_counter > 10U){
            speed_counter = 0U;
            speed_stimer = 900U;          
            if(speed_stimer > speed_dc){
                speed_dc++;
            }
            else{
                speed_dc--;
            }
             if(step_counts == step_counts_calc){
            }
            else if(step_counts > step_counts_calc){
                step_counts--;
            }
            else{
                step_counts++;
            }   
        }
    }
}

void motor_handler(void){
    if(step_timer >= step_counts){   
        step_timer = 0U;
        speed_handler();   
        step_handler(motor_dir);
    }
    else{
        /*wait*/
    } 
}

void step_handler(bool direction){       
    uint16_t step_thr = step_counts/3U;
    StepNum++; /*Go to next commutation step*/  
    zerocross_flag = 0;
    uint16_t y1 = 0;
    uint16_t y2 = 0;   
    
    switch (StepNum) {
        case 1:
            /*PH1-H = HIGH, PH2-L = HIGH, PH3 - READ*/            
            PDC3 = 0U;
            PDC1 = speed_dc;
//            if(speed_cl == 1){ 
//                while(zerocross_flag == 0){                    
////                    if(step_timer >= (step_counts-10U)){
////                        zerocross_flag = 1; 
////                    }
//                    if(step_timer >= step_thr){
//                        AD1CON1bits.SAMP = 0; // start Converting
//                       while (!AD1CON1bits.DONE);// conversion done?
//                        y1 = ADC1BUF1;
//                        y2 = ADC1BUF2/2;
//                        if(y1<=y2){              
//                            LED1_Toggle();     
//                            step_counts_new[StepIndex] = step_timer + step_timer; 
//                            zerocross_flag = 1;   
//                        }
//                    }                    
//                }
            } 
            break;

        case 2:
            /*PH1-H = HIGH, PH3-L = HIGH, PH2 - READ*/        
            PH2_L_OUT_SetLow();
            PH3_L_OUT_SetHigh();
            StepIndex++;
            if(speed_cl == 1){ 
                while(zerocross_flag == 0){                    
//                    if(step_timer >= (step_counts-10U)){
//                        zerocross_flag = 1; 
//                    }
                    if(step_timer >= step_thr){
                        AD1CON1bits.SAMP = 0; // start Converting
                       while (!AD1CON1bits.DONE);// conversion done?
                        y1 = ADC1BUF0;
                        y2 = ADC1BUF2/2;
                        if(y1>=y2){        
                            LED1_Toggle();     
                            step_counts_new[StepIndex] = step_timer + step_timer; 
                            zerocross_flag = 1;   
                        }
                    }
                }
            } 
            break;

        case 3:
            /*PH2-H = HIGH, PH3-L = HIGH, PH1 - READ*/ 
            PDC1 = 0;
            PDC2 = speed_dc;
//            if(speed_cl == 1){ 
//                while(zerocross_flag == 0){                    
////                    if(step_timer >= (step_counts-10U)){
////                        zerocross_flag = 1; 
////                    }
//                    if(step_timer >= step_thr){
//                        AD1CON1bits.SAMP = 0; // start Converting
//                       while (!AD1CON1bits.DONE);// conversion done?
//                        y1 = ADC1BUF2;
//                        y2 = ADC1BUF0/2;
//                        if(y1<=y2){           
//                            LED1_Toggle();     
//                            step_counts_new[StepIndex] = step_timer + step_timer; 
//                            zerocross_flag = 1;   
//                        }
//                    }
//                }
//            } 
            break;

        case 4:
            /*PH2-H = HIGH, PH1-L = HIGH, PH3 - READ*/
            PH3_L_OUT_SetLow();
            PH1_L_OUT_SetHigh(); 
            StepIndex++;
            if(speed_cl == 1){ 
                while(zerocross_flag == 0){                    
//                    if(step_timer >= (step_counts-10U)){
//                        zerocross_flag = 1; 
//                    }
                    if(step_timer >= step_thr){
                        AD1CON1bits.SAMP = 0; // start Converting
                       while (!AD1CON1bits.DONE);// conversion done?
                        y1 = ADC1BUF1;
                        y2 = ADC1BUF0/2;
                        if(y1>=y2){
                            LED1_Toggle();     
                            step_counts_new[StepIndex] = step_timer + step_timer; 
                            zerocross_flag = 1;   
                        }
                    }
                }
            } 
            break;

        case 5:
            /*PH3-H = HIGH, PH1-L = HIGH, PH2 - READ*/
            PDC2 = 0U;
            PDC3 = speed_dc;
//            if(speed_cl == 1){ 
//                while(zerocross_flag == 0){
////                    if(step_timer >= (step_counts-10U)){
////                        zerocross_flag = 1; 
////                    }
//                    if(step_timer >= step_thr){
//                        AD1CON1bits.SAMP = 0; // start Converting
//                       while (!AD1CON1bits.DONE);// conversion done?
//                        y1 = ADC1BUF0;
//                        y2 = ADC1BUF1/2;
//                        if(y1<=y2){               
//                            LED1_Toggle();     
//                            step_counts_new[StepIndex] = step_timer + step_timer; 
//                            zerocross_flag = 1;   
//                        }
//                    }
//                }
//            } 
            break;

        case 6:
            /*PH3-H = HIGH, PH2-L = HIGH, PH1 - READ*/
            PH1_L_OUT_SetLow();
            PH2_L_OUT_SetHigh();
            StepIndex++;
            if(speed_cl == 1){ 
                while(zerocross_flag == 0){
//                    if(step_timer >= (step_counts-10U)){
//                        zerocross_flag = 1; 
//                    }
                    if(step_timer >= step_thr){
                        AD1CON1bits.SAMP = 0; // start Converting
                       while (!AD1CON1bits.DONE);// conversion done?
                        y1 = ADC1BUF2;
                        y2 = ADC1BUF1/2;
                        if(y1>=y2){                
                            LED1_Toggle();     
                            step_counts_new[StepIndex] = step_timer + step_timer; 
                            zerocross_flag = 1;   
                        }
                    }
                }
            }   
            StepNum = 0U;
            break;
    }   
    if(StepIndex >= arraynum){
        StepIndex = 0U;
    }  
}


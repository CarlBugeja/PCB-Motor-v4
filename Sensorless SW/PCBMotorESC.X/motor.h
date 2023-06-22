/* 
 * File:   motor.h
 * Author: carlb
 *
 * Created on June 22, 2021, 3:22 PM
 */

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FCY  (42377500UL)
    
void motor_init(void);
void motor_stop(void);
void motor_handler(void);
void step_handler(bool direction);
void speed_handler(void);
void signal_handler(void);

#define arraynum 6U
#define INIT_SPEED 6500U
#define DC_MIN 180U
#define DC_MAX 1000U
#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */


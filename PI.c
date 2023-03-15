/**
  Section: Included Files
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "PI.h"
#include <stdlib.h> //for atoi and atof functions

/**
  Section: PI Module APIs
 */

static uint8_t sensorHeight = 0;
static uint8_t setpoint = 150;
static int iteration_time = 0.33;
static int error_prior = 0;
static int error = 0;
static int integral_prior = 0;
static float integral = 0;
static float derivative = 0;

static float kp = 8.00;
static float ki = 0.025 ;
static float kd = 15;

static int dutycycle;

uint8_t PI_GetSensorHeight(void) {
    return sensorHeight;
}

void PI_SetSetpoint(uint8_t value) {
    setpoint = value;
}
uint8_t PI_GetSetPoint(void) {
    return setpoint;
}


int PI_GetDutycycle(void) {
    return dutycycle;
}

void PI_SetKp(float value) {
    kp = value;
}
float PI_GetKp(void) {
    return kp;
}

void PI_SetKi(float value) {
    ki = value;
}
float PI_GetKi(void) {
    return ki;
}

void PI(void) {
    sensorHeight = (uint8_t) (ADC_GetConversionResult() >> 2); //resultaat van ADC (8 bit )
    
     error = (int) setpoint - (int)sensorHeight;
    
    integral += error;
    derivative = (error - error_prior)*3;
    
    dutycycle = (int)(kp*error + ki*integral +kd*derivative);
    error_prior = error;
    integral_prior = integral;
    //sleep(iteration_time);
    
    //printf("integral =  %d", integral);
    
    if (dutycycle > 1023) {
        dutycycle = 1023;
    }
    if (dutycycle < 0 ) {
        dutycycle = 0;
    }
    
    
            

    PWM5_LoadDutyValue( (uint16_t) dutycycle); // output pwm signaal voor hoogte 10 bit (van 0 tot 0x3FF)
}

/**
 End of File
 */
/* Demo project pingpongtoren + hoogtesensor 
 * 
 * 
 * pinout:  RC2 = receiver input
 *          RC7 = transmitter output
 *          RB6 = pulse lengte output
 *          RB4 = pwm output
 *          RC1 = motor output
 */

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include "PI.h"
#include "UART.h"
#include "led.h"


/*
                         Main application
 */
void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    // Initialiseer de hoogtemeting
    
    printf(" hello3");
    ADC_SelectChannel(Hoogtesensor);
    ADC_StartConversion();
    TMR2_Initialize();
    TMR2_StartTimer();
    SPI1_Open(    MASTER0_CONFIG);
    TMR0_Initialize();
    while (1) {
        // PI moet op een vaste frequentie (elke 33ms) lopen voor de integrator
        uartHandler();
        updateLedStrip(PI_GetSensorHeight(),getTargetHeight());
        if (TMR0_HasOverflowOccured()) {
            TMR0_Initialize();

            PI();
            static uint8_t  counter =0;
            if(counter++>30){
                printLogs();
                counter=0;
            }

        }
    }
}

/**
 End of File
 */
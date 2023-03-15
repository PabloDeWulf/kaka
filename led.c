#include <xc.h>
#include "mcc_generated_files/mcc.h"
uint8_t blue = 0x00, green = 0x00, red = 0xFF;
#define EUART_READ_LINE_BUFFER_LENGTH 20
char line[EUART_READ_LINE_BUFFER_LENGTH];
#include <math.h>

#define PRINT_BUFFER_LENGTH 11
char printBuffer[PRINT_BUFFER_LENGTH];
enum states {
    GREEN_UP, RED_DOWN, BLUE_UP, GREEN_DOWN, RED_UP, BLUE_DOWN
};
enum states change_color = GREEN_UP;
uint8_t step = 1;

enum count {
    UP, DOWN
};
enum count direction = UP;
char led_run = 0;
const int NumberOfLEDs = 60;

void Send_LED_Frame(uint8_t intensity, uint8_t blue, uint8_t green, uint8_t red) {
    SPI1_ExchangeByte(0xE0 | intensity);
    SPI1_ExchangeByte(blue);
    SPI1_ExchangeByte(green);
    SPI1_ExchangeByte(red);
}

void Send_LED_StartFrame() {
    for (int i = 0; i < 4; i++) {
        SPI1_ExchangeByte(0x00);
    }
}

void Send_LED_EndFrame() {
    for (int i = 0; i < 4; i++) {
        SPI1_ExchangeByte(0xFF);
    }
}


void updateLedStrip(uint8_t ledHeight, uint8_t targetHeight){
    
        char inputchar =(ledHeight/3)-8;
        
    
     Send_LED_StartFrame();
        //printf('%c\n',inputchar);
//        char inputchar = EUSART_Read();
//        EUSART_Write(inputchar);
        for (char led = 0; led < NumberOfLEDs; led++) {
            if ((inputchar== targetHeight || inputchar== targetHeight-1 || inputchar== targetHeight+1)&& (led ==targetHeight+1 || led ==targetHeight-1 ||led ==targetHeight)){
               Send_LED_Frame(0x1F,0x00, 0xFF, 0x00);
            }
            
            else if (led == inputchar || led == inputchar+1 || led== inputchar-1) {
                Send_LED_Frame(0x1F, blue, green, red);
            }else if(led == targetHeight || led == targetHeight-1 || led == targetHeight+1 || led == targetHeight-2 || led == targetHeight+2 ){
                Send_LED_Frame(0x1F,0x00, 0xFF, 0x00);
            }
            else{
                Send_LED_Frame(0x00, 0x00, 0x00, 0x00);
            }
        }
        //stop frame
        Send_LED_EndFrame();
}

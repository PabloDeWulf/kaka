#ifndef UART_H
#define	UART_H

#include <xc.h> 

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
    void uartHandler(void);
    void printLogs(void);
    uint8_t getTargetHeight(void);
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* UART_H */


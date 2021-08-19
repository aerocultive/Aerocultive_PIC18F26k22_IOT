/*
 * File:   init_system.c
 * Author: estudiante
 *
 * Created on 31 de octubre de 2020, 07:48 AM
 */
#include <xc.h>
#include <PIC18F26k22.h>
#include <stdio.h>
#include <stdint.h>
#include <xc.h>
#include <usart.h>
#include "init_system.h"

void init_system(void){
    //// Configuracion del reloj ////
    *OSCCON = 0b01111111;        //  Internal Clock set as 16 MHz 
    INTCON = 0b11100000;        //  Enable global(7) and peripheral interrupts(6), aHabilita TMR0 interrupt(5), INT0 interrpcion deshabilitado(4), deshabiliya interrpcion IOCX(3), tmr0if BANDERA DEL TIMER0(2), BANDERA int0(1) , BANDERA I0CX(0)
    INTCON3 = 0b00000000;       //  Interrupts 1 and 2 disabled
    INTCON2 = 0b00000100;       // Se establece TMR= interrupcion como maxima prioridad 

    /// Configuracion del puerto A ////
    CM1CON0 = 0b00000000;       //  Comparator 1 disabled
    CM2CON0 = 0b00000000;       //  Comparator 2 disabled
    ADCON0 = 0b00000000;        //  A/D disabled
    VREFCON0 = 0b00000000;      //  Fixed Voltage Reference disabled
    VREFCON1 = 0b00000000;      //  DAC disabled
    CCP1CON = 0b00000000;       //  Capture Compare disabled
    CCP2CON = 0b00000000;       //  Capture Compare disabled
    CCP3CON = 0b00000000;       //  Capture Compare disabled
    SRCON0 = 0b00000000;        //  SR Latch disabled
    T0CON = 0b10000000;         //  Timer 0 HABILITADO(7),timer de 16 bits(6),reloj del CLKOUT(5),incrementa de bajo a alto (4),timer 0 prescaladpo, prescaldo 1:2 (2-0)
    SSP1CON1 = 0b00000111;      //  Set MSSP1 as Slave Port
    HLVDCON = 0b00000000;       //  High-Low Voltage Detect Disabled
    *TRISA = 0b11111100;         //  1-impuit 0 -output,  Tri-state A5, A6, A7; input 5P3V_PG, PWR1_PRES, PWR2_PRES; output LED1, LED2
    *ANSELA = 0b11111111;        //
    //  Port B Configuration
    INTCON3 = 0b00000000;       //  Interrupts 1 and 2 disabled
    ECCP2AS = 0b00000000;       //  Auto Shutdown disabled on ECCP2
    ECCP3AS = 0b00000000;       //  Auto Shutdown disabled on ECCP3
    CTMUCONH = 0b00000000;      //  CTMU disabled
    T5CON = 0b00000000;         //  Timer 5 disabled
    T3CON = 0b00000000;         //  Timer 3 disabled
    T1CON = 0b00000000;         //  Timer 1 disabled
    *TXSTA2 = 0b00000000;        //  EUSART2 Transmit disabled
    *RCSTA2 = 0b00000000;        //  EUSART2 Receive disabled
    *TRISB = 0b11111111;         //  Tri-state all of Port B
    *ANSELB = 0b11111111;

    //  Port C Configuration
    *OSCCON2 = 0b00000000;       //  Secondary Oscillator disabled
    SSP2CON1 = 0b00101000;      //  Set MSSP2 as Master Port with Serial Enabled
    *TXSTA1 = 0b00000000;        //  EUSART1 Transmit disabled
    *RCSTA1 = 0b00000000;        //  EUSART1 Receive disabled
    *TRISC = 0b11111011;         //  Input EUSART_RX1; Tri-State EUSART_TX1;
                                //  Input UART_RXDV; Tri-State SDA_IN, SCL_IN;
                                //  Output RS232_EN_N; Input +12V_IN2/1_SENSE
    *ANSELC = 0b11111111;   
}
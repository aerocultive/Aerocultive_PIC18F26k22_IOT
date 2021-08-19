/*
 * File:   init_system.c
 * Author: estudiante
 *
 * Created on 31 de octubre de 2020, 07:48 AM
 */
 
#define USE_OR_MASKS
#include <xc.h>
#include <PIC18F26k22.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <xc.h>
#include <usart.h>
#include "init_system.h"

volatile int inicio_config_wifi=0;
volatile unsigned char value[50];
volatile int start_transmision_wifi=0;
*** volatile char ? respuesta;

void main(void) {
    init_system();
    Close1USART();
    Close2USART();
    USARTconfig = USART_TX_INT_OFF | USART_RX_INT_ON | USART_ASYNCH_MODE | USART_EIGHT_BIT | USART_CONT_RX | USART_BRGH_LOW;
    spbrg = 25;    // A 1MHz , baudrate de 2400
    Open1USART(USARTconfig,spbrg);   // USART Configured for desired parameters
    baudconfig = BAUD_16_BIT_RATE | BAUD_AUTO_OFF;
    baud1USART(baudconfig);         // Baud Rate Controls configured
    BAUDCON1bits.DTRXP = 0;
    BAUDCON1bits.CKTXP = 0;
    BAUDCON1bits.WUE1 = 1;

    //  PIE1bits.RC1IE = 1;

    LATAbits.LA0 = 1;
    LATAbits.LA1 = 1;
    LATCbits.LC2 = 0;


    while(1){
        if(inicio_config_wifi=0){
            transmitir_wifi("AT");
            respuesta=strstr(&value, "OK");
                if(respuesta < 79){
                    inicio_config_wifi=1;
                }else {
                    inicio_config_wifi=0;
                }
        }
        if(inicio_config_wifi=1){
            transmitir_wifi("AT+CWMODE=3");
            respuesta=strstr(&value,"OK");
                if(respuesta < 79){
                    inicio_config_wifi=2;
                }else {
                    inicio_config_wifi=1;
                }
        }
        if(inicio_config_wifi=2){
            transmitir_wifi("AT+CIPMUX=1"); // Habilito multiples conexiones TCP
            respuesta=strstr(&value,"OK");
                if(respuesta < 79){
                    inicio_config_wifi=3;
                }else {
                    inicio_config_wifi=2;
                }
        }

        if(inicio_config_wifi=3){
            value[0]='/0';
            strcat(value,"AT+CWJAP=\"estefania\",\"3123066108\"");
            transmitir_wifi(&value); // Configuro la red a conectar 
            respuesta=strstr(&value,"OK");
                if(respuesta < 79){
                    start_transmision_wifi=1;
                }else {
                    inicio_config_wifi=3;
                }
        }

        if(start_transmision_wifi=1){
            value[0]='/0';
            strcat(value,"AT+CIPSTART=4,\"TCP\",\"192.168.1.1\",80") // link a thingspeak
            transmitir_wifi(&value);
            respuesta=strstr(&value,"OK");
                if(respuesta < 79){
                    start_transmision_wifi=2;
                }else {
                    inicio_config_wifi=1;
                }
        }
        if(start_transmision_wifi==2){
            value[0]='/0';
            strcat(value,"AT+CIPSEND=4,46");//envio el numero de caracteres a enviar
            transmitir_wifi(&value);
            respuesta=strstr(&value,">");
                if(respuesta < 79){
                    start_transmision_wifi=3;
                }else {
                    inicio_config_wifi=2;
                }
        }
        if(start_transmision_wifi==3){
            value[0]='/0';
            strcat(value,"GET /update?key=4L77HR0XBBBVZNVU&field1=");
            transmitir(&value);
        }
        
    }
}


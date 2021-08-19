/*
 * File:  transmitir_wifi
 * Author: Aerocultive
 *
 * Created on 8 de octubre de 2021 07:48 AM
 */
#include <xc.h>
#include <PIC18F26k22.h>
#include <stdio.h>
#include <stdint.h>
#include "transmitir_wifi.h"


/*Variables de transmitir WIFI*/
volatile int ready=0;


void transmitir_wifi(const char *ptr){
    if(Busy2USART()==0){
        ready=1;
    }
    if(ready==1){
        put2USART((char *)ptr);   // Transmit the String
        ready=0;
    }
}
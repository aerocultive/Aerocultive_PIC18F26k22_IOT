/*
 * File:  transmitir_sensores
 * Author: Aerocultive
 *
 * Created on 8 de octubre de 2021 07:48 AM
 */
#include <xc.h>
#include <PIC18F26k22.h>
#include <stdio.h>
#include <stdint.h>
#include "transmitir_sensores.h"


/*Variables de transmitir WIFI*/
volatile int ready=0;


void transmitir_sensores(int direccion){
    if(Busy2USART()==0){
        ready=1;
    }
    if(ready==1){
        Write1USART(direccion);   // Transmit the String
        ready=0;
    }
}
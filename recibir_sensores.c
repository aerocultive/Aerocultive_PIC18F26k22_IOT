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
#include "recibir_sensores.h"


/*Variables de transmitir WIFI*/
volatile int ready=0;
volatile char *rxdata;
volatile int i = 0;
volatile int len=0;
volatile int datos[4];
volatile int bytes=0,


void recibir_sensores(int len){
    if ( PIR3bits.RC2IF == 1){  // Se pregunta si llego algo en el buffer de recepción
        PIR3bits.RC2IF=0;
        if(i > (len - 1)){
            // Se acaba la transmision
            i=0;
        }else{
            datosd[i] = Read1USART();
            i++;
        }
    }
}
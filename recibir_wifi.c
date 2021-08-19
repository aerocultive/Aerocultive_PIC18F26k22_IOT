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
#include "recibir_wifi.h"


/*Variables de transmitir WIFI*/
volatile int ready=0;
volatile char *rxdata;
volatile int i = 0;


/*Variables de Clasificar       */

void recibir_wifi(unsigned char len){
    if ( PIR3bits.RC2IF == 1){  // Se pregunta si llego algo en el buffer de recepción
        PIR3bits.RC2IF=0;
        if (i = (len - 1))
        {
            rxdata[i] = '\0';
        }
        else
        {
            rxdata[i] = getc2USART();
            if (rxdata[i] == '\n')
            {
                rxdata[i + 1] = '\0';
                i = 0;
            }
            else
            {
                i++;
            }
        }
    }
}
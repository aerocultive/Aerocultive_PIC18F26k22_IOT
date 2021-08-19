/*
 * File: control
 * Author: Aerocultive
 *
 * Created on 8 de octubre de 2021 07:48 AM
 */
#include <xc.h>
#include <PIC18F26k22.h>
#include <stdio.h>
#include <stdint.h>
#include "control.h"

/*Variables de transmitir WIFI*/
volatile int ready=0;
volatile char *rxdata;
volatile int i = 0;
volatile int intensidad_luminica=0;
volatile int pedir_dato=0;            // Variable que levanto cada vez que pido un dato


void control(void){
    if(intensidad_luminica==1){       // Variable que se habilita en la interrupción del timer despues de 1 hora
        intensidad_luminica=0;
        pedir_dato=1;                // Se sube la bandera para el pedir el dato 
        transmitir_sensores(0x01);   // Envio dirección del senso de intensidad lumínica
        recibir_sensores();
        transmitir_wifi();
        if((dato <= 12000) || (dato >= 30000)){
            //realizo algo esta pedmiente  
        }
    }
    if(sensor_hum_tem==1){          // Variable que se habilita en la interrupcion del timer despues de 2 min
        sensor_hum_tem=0;
        transmitir_sensores(0x02);  // Envio dirrecion del sensor de humedad y temperatura
        recibir_sensores();         // recibo dato de humedad y temperatura 
        transmitir_wifi();          // Envio humedad y temperatura 
        if(dato_humedad <= 60){
            pinx=1;                 // se prenden los extractores 
        }else if (dato_humedad >= 80) {
            // NO hay control para este caso
        }
        if(dato_temperatura<=18){
            // No hay control ´para este caso 
        }else if(dato_temperatura>=20){
            pinx=1;                  // se prenden los extractores 
        }
    }
    if(sensor_ph==1){                // Variable que se habilita en la interrupcion del timer despues de 7 dias
        sensor_ph=0;
        transmitir_sensores(0x03);
        recibir_sensores();
        transmitir_wifi():
        if (dato<= 6.7){
            // Algo sucede todavia no sabemos que
        }else if (dato >= 6.5){
            // Algo sucede todavia no sabemos que
        }
    }
    if(sensor_EC==1){          // Variable que se habilita en la interrupcion del timer despues de 2 min
        sensor_EC=0;
        transmitir_sensores(0x05);  // Envio dirrecion del sensor de humedad y temperatura
        recibir_sensores();         // recibo dato de humedad y temperatura 
        transmitir_wifi();          // Envio humedad y temperatura 
        if(dato <= 1.4){
            // ALGO SUCEDE NO SABEMOS QUE
        }
    } 
        
}
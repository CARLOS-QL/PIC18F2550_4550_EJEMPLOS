/**********************************************
* Libreria:     ADC.h
* Author:       Carlos QL
* Contacto:     carlos.quispe.359@gmail.com
* Descripcion   Para el manejo del ADC del PIC18F
* TAD mínimo    0.7us
* TADC          2.45us  
* Tiempo de Adquisición mínimo 20us	
 **********************************************/

#include <stdint.h>

/******************************************
* Inicialización del ADC
******************************************/

void ADC_init(void)
{  
    ADCON1bits.VCFG = 0b00;     //REF -> VSS, VCC
    ADCON1bits.PCFG = 0b1110;   //Entradas Analogicas an0
    
    ADCON2bits.ACQT = 0b010;    //TACQT > 2.45us
    ADCON2bits.ADCS = 0b100;    //TAD >  0.7us Tosc * 4 = 1us
    ADCON2bits.ADFM = 1;        //1 derecha, 0 izquierda
    
    ADCON0bits.ADON = 1;        //ADC on
}

/*****************************************
* Lectura de un canal Analogico
*****************************************/

uint16_t ADC_read(uint8_t channel)
{
    ADCON0bits.CHS = channel;                  //Seleccion e canal
    ADCON0bits.GO = 1;                          //ADC start
    while(ADCON0bits.GO_DONE);                  //Espera termine la conversion
    return ((uint16_t)((ADRESH<<8)+ADRESL));    //Retorna el valor del ADC
}

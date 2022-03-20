
// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = XT_XT     // Oscillator Selection bits (XT oscillator (XT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)


#define _XTAL_FREQ  4000000

#include <xc.h>
#include <stdint.h>
#include "I2C.h"
#include "LCD.h"

uint8_t sec, min, hora;
uint8_t dia, mes, anio;

char Hora[] = "105845";
char Fecha[] = "200319";

void convertirHora(void){
    
    for(uint8_t i=0; i<7; i++){
        Hora[i] &= 0x0F;
    }
    
    hora = ((Hora[0]<<4)+ Hora[1]);
    min = ((Hora[2]<<4)+ Hora[3]);
    sec = ((Hora[4]<<4)+ Hora[5]);
}

void convertirFecha(void){
    
    for(uint8_t i=0; i<7; i++){
        Fecha[i] &= 0x0F;
    }
    
    dia = ((Fecha[0]<<4)+ Fecha[1]);
    mes = ((Fecha[2]<<4)+ Fecha[3]);
    anio = ((Fecha[4]<<4)+ Fecha[5]);
}

void enviar_hora(void){
    
    I2C_start();            //Incia comunicai�n I2C
    I2C_write(0xD0);        //Escoje direcci�n del reloj
    I2C_write(0x00);        //Posici�n de los segundos
    I2C_write(sec);         //Posici�n donde va leer
    I2C_write(min);         //Posici�n donde va leer
    I2C_write(hora);        //Posici�n donde va leer
    I2C_stop();             //Detiene la comunicai�n I2C
}

void leer_hora(void){
    
    I2C_start();            //Incia comunicai�n I2C
    I2C_write(0xD0);        //Escoje direcci�n del reloj
    I2C_write(0x00);        //Posici�n donde va leer
    I2C_restart();          //Reinicia la comuniaci�n I2C
    I2C_write(0xD1);        //Leer posici�n
    sec = I2C_read();      //lee posicion de reloj
    I2C_ack();
    min = I2C_read();      //lee posicion de reloj
    I2C_ack();
    hora = I2C_read();      //lee posicion de reloj
    I2C_nack();
    I2C_stop();             //Termina comunicaion I2C
}

void enviar_fecha(void){
    
    I2C_start();            //Incia comunicai�n I2C
    I2C_write(0xD0);        //Escoje direcci�n del reloj
    I2C_write(0x04);        //Posici�n de los segundos
    I2C_write(dia);         //Posici�n donde va leer
    I2C_write(mes);         //Posici�n donde va leer
    I2C_write(anio);        //Posici�n donde va leer
    I2C_stop();             //Detiene la comunicai�n I2C
}

void leer_fecha(void){
    
    I2C_start();            //Incia comunicai�n I2C
    I2C_write(0xD0);        //Escoje direcci�n del reloj
    I2C_write(0x04);        //Posici�n donde va leer
    I2C_restart();          //Reinicia la comuniaci�n I2C
    I2C_write(0xD1);        //Leer posici�n
    dia = I2C_read();      //lee posicion de reloj
    I2C_ack();
    mes = I2C_read();      //lee posicion de reloj
    I2C_ack();
    anio = I2C_read();      //lee posicion de reloj
    I2C_nack();
    I2C_stop();             //Termina comunicaion I2C
}


void mostrar_hora(void){
    
    LCD_dato((hora>>4)+0x30);
    LCD_dato((hora & 0x0F)+0x30);
    LCD_dato(':');
    LCD_dato((min>>4)+0x30);
    LCD_dato((min & 0x0F)+0x30);
    LCD_dato(':');
    LCD_dato((sec>>4)+0x30);
    LCD_dato((sec & 0x0F)+0x30);
}

void mostrar_fecha(void){
    
    LCD_dato((dia>>4)+0x30);
    LCD_dato((dia & 0x0F)+0x30);
    LCD_dato('/');
    LCD_dato((mes>>4)+0x30);
    LCD_dato((mes & 0x0F)+0x30);
    LCD_dato('/');   
    LCD_dato((anio>>4)+0x30);
    LCD_dato((anio & 0x0F)+0x30);
}



void main(void) {
   
    ADCON1 = 0X06;
    LCD_init();
    I2C_init();
    
    convertirHora();
    enviar_hora();
      
    convertirFecha();
    enviar_fecha();
    
    while(1){
      
        LCD_goto(2, 1);
        LCD_printf("Hora  ");
        leer_hora();
        mostrar_hora();
        
        LCD_goto(2, 2);
        LCD_printf("Fecha ");
        leer_fecha();
        mostrar_fecha();
        __delay_ms(100);
             
    }
    return;
}

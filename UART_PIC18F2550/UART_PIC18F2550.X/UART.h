
/*
 * File:   UART.h
 * Author: Carlos Quispe
 * Contacto carlos.quispe.359@gmail.com
 */

/************** Prototipo de funciones ******************/

void UART_init(void);
void UART_init_baud(const long int baudRate);
char UART_read(void);
void UART_write(char dato);
void UART_printf(char *cadena);


void UART_init(void)
{
    TRISCbits.TRISC7 = 1;   //RX input
    TRISCbits.TRISC6 = 0;   //TX output 
    
    TXSTAbits.SYNC = 0;     //UART
    TXSTAbits.TX9 = 0;      //8 BITS
    TXSTAbits.BRGH = 1;     //ALTA VELOCIDAD
    SPBRG = 129;            //9600 a 20MHZ
    RCSTAbits.SPEN = 1;     //UART on    
    TXSTAbits.TXEN = 1;    //TX on
    RCSTAbits.CREN = 1;     //RX on
}

void UART_init_baud(const long int baudRate)
{
    
    unsigned char valor = (unsigned char)((_XTAL_FREQ/(baudRate*16)) -1);
    TXSTAbits.BRGH = 1;     //ALTA VELOCIDAD
    
    if(valor>255)
    {
        valor = (unsigned char)((_XTAL_FREQ/(baudRate*64)) -1);
        TXSTAbits.BRGH = 0;     //ALTA VELOCIDAD
    }
    
    TRISCbits.TRISC7 = 1;   //RX input
    TRISCbits.TRISC6 = 0;   //TX output 
    
    TXSTAbits.SYNC = 0;     //UART
    TXSTAbits.TX9 = 0;      //8 BITS
   
    SPBRG = valor;            //9600 a 20MHZ
    RCSTAbits.SPEN = 1;     //UART on    
    TXSTAbits.TXEN = 1;    //TX on
    RCSTAbits.CREN = 1;     //RX on
}

char UART_read(void)
{
    if (PIR1bits.RCIF == 1)
    {
        if(RCSTAbits.OERR)
        {
            RCSTAbits.CREN = 0;
            NOP();
            RCSTAbits.CREN = 1;          
        }
        return RCREG;
    }
        
    else
        return 0;
}

void UART_write(char dato)
{
    TXREG = dato;
     while(TXSTAbits.TRMT == 0);
}

void UART_printf(char *cadena)
{
    while(*cadena !=0x00){
        UART_write(*cadena);
        cadena++;
    }
}

/************* Para poder utilizar la funcion printf **********/

void putch(char dato)
{
    UART_write(dato);
}

#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"

#define SLAVE_SELECT SPI_SS_PORT &= ~(1<<SPI_SS)
#define SLAVE_DESELECT SPI_SS_PORT |= (1<<SPI_SS)

void write_data(char the_register, char data) {
    SLAVE_SELECT;
    //right eye
    SPDR = the_register;
    loop_until_bit_is_set(SPSR, SPIF);
    SPDR = data;
    loop_until_bit_is_set(SPSR, SPIF);
    //left eye
    SPDR = the_register;
    loop_until_bit_is_set(SPSR, SPIF);
    SPDR = data;
    loop_until_bit_is_set(SPSR, SPIF);
    SLAVE_DESELECT;
    _delay_ms(5);
}

void single_data(char the_register_right_eye, char data_right_eye,
                 char the_register_left_eye, char data_left_eye) {
   SLAVE_SELECT;
    //right eye
    SPDR = the_register_right_eye;
    loop_until_bit_is_set(SPSR, SPIF);
    SPDR = data_right_eye;
    loop_until_bit_is_set(SPSR, SPIF);
    //left eye
    SPDR = the_register_left_eye;
    loop_until_bit_is_set(SPSR, SPIF);
    SPDR = data_left_eye;
    loop_until_bit_is_set(SPSR, SPIF);
    SLAVE_DESELECT;
    _delay_ms(5);
}

void splash_octocat() {
    write_data(0x01, 0b00100100); _delay_ms(70);
    write_data(0x02, 0b01111110); _delay_ms(70);
    write_data(0x03, 0b01111110); _delay_ms(70);
    write_data(0x04, 0b00111100); _delay_ms(70);
    write_data(0x05, 0b10011000); _delay_ms(70);
    write_data(0x06, 0b01111000); _delay_ms(70);
    write_data(0x07, 0b00011000); _delay_ms(70);
    write_data(0x08, 0b00000000);
    _delay_ms(3000);        
}

void bullseye() {
    write_data(0x01, 0b00111100); _delay_ms(70);
    write_data(0x02, 0b01000010); _delay_ms(70);
    write_data(0x03, 0b10011001); _delay_ms(70);
    write_data(0x04, 0b10100101); _delay_ms(70);
    write_data(0x05, 0b10100101); _delay_ms(70);
    write_data(0x06, 0b10011001); _delay_ms(70);
    write_data(0x07, 0b01000010); _delay_ms(70);
    write_data(0x08, 0b00111100); _delay_ms(3000);
    clear();
}

void ping_pong()
{
    single_data(0x01, 0b00000000, 0x01, 0b00000000); 
    single_data(0x02, 0b00000000, 0x02, 0b00000000); 
    single_data(0x03, 0b00011000, 0x03, 0b00011000); 
    single_data(0x04, 0b00100100, 0x04, 0b00100100); 
    single_data(0x05, 0b00100100, 0x05, 0b00100100); 
    single_data(0x06, 0b00011000, 0x06, 0b00011000); 
    single_data(0x07, 0b00000000, 0x07, 0b00000000); 
    single_data(0x08, 0b00000000, 0x08, 0b00000000); _delay_ms(35);
    
    single_data(0x03, 0b00001100, 0x03, 0b00110000); 
    single_data(0x04, 0b00010010, 0x04, 0b01001000); 
    single_data(0x05, 0b00010010, 0x05, 0b01001000); 
    single_data(0x06, 0b00001100, 0x06, 0b00110000); _delay_ms(35);
    
    single_data(0x03, 0b00000110, 0x03, 0b01100000); 
    single_data(0x04, 0b00001001, 0x04, 0b10010000); 
    single_data(0x05, 0b00001001, 0x05, 0b10010000); 
    single_data(0x06, 0b00000110, 0x06, 0b01100000); _delay_ms(35);

    for (int i=0; i<3; i++) {
    single_data(0x03, 0b00000011, 0x03, 0b11000000); 
    single_data(0x04, 0b00000100, 0x04, 0b00100000); 
    single_data(0x05, 0b00000100, 0x05, 0b00100000); 
    single_data(0x06, 0b00000011, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b01100000); 
    single_data(0x04, 0b00000100, 0x04, 0b10010000); 
    single_data(0x05, 0b00000100, 0x05, 0b10010000); 
    single_data(0x06, 0b00000011, 0x06, 0b01100000); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00110000); 
    single_data(0x04, 0b00000100, 0x04, 0b01001000); 
    single_data(0x05, 0b00000100, 0x05, 0b01001000); 
    single_data(0x06, 0b00000011, 0x06, 0b00110000); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00011000); 
    single_data(0x04, 0b00000100, 0x04, 0b00100100); 
    single_data(0x05, 0b00000100, 0x05, 0b00100100); 
    single_data(0x06, 0b00000011, 0x06, 0b00011000); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00001100); 
    single_data(0x04, 0b00000100, 0x04, 0b00010010); 
    single_data(0x05, 0b00000100, 0x05, 0b00010010); 
    single_data(0x06, 0b00000011, 0x06, 0b00001100); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00000110); 
    single_data(0x04, 0b00000100, 0x04, 0b00001001); 
    single_data(0x05, 0b00000100, 0x05, 0b00001001); 
    single_data(0x06, 0b00000011, 0x06, 0b00000110); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00000011); 
    single_data(0x04, 0b00000100, 0x04, 0b00000100); 
    single_data(0x05, 0b00000100, 0x05, 0b00000100); 
    single_data(0x06, 0b00000011, 0x06, 0b00000011); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00000110); 
    single_data(0x04, 0b00000100, 0x04, 0b00001001); 
    single_data(0x05, 0b00000100, 0x05, 0b00001001); 
    single_data(0x06, 0b00000011, 0x06, 0b00000110); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00001100); 
    single_data(0x04, 0b00000100, 0x04, 0b00010010); 
    single_data(0x05, 0b00000100, 0x05, 0b00010010); 
    single_data(0x06, 0b00000011, 0x06, 0b00001100); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00011000); 
    single_data(0x04, 0b00000100, 0x04, 0b00100100); 
    single_data(0x05, 0b00000100, 0x05, 0b00100100); 
    single_data(0x06, 0b00000011, 0x06, 0b00011000); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b00110000); 
    single_data(0x04, 0b00000100, 0x04, 0b01001000); 
    single_data(0x05, 0b00000100, 0x05, 0b01001000); 
    single_data(0x06, 0b00000011, 0x06, 0b00110000); _delay_ms(35);

    single_data(0x03, 0b00000011, 0x03, 0b01100000); 
    single_data(0x04, 0b00000100, 0x04, 0b10010000); 
    single_data(0x05, 0b00000100, 0x05, 0b10010000); 
    single_data(0x06, 0b00000011, 0x06, 0b01100000); _delay_ms(35);
     
    single_data(0x03, 0b00000011, 0x03, 0b11000000); 
    single_data(0x04, 0b00000100, 0x04, 0b00100000); 
    single_data(0x05, 0b00000100, 0x05, 0b00100000); 
    single_data(0x06, 0b00000011, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00000110, 0x03, 0b11000000); 
    single_data(0x04, 0b00001001, 0x04, 0b00100000); 
    single_data(0x05, 0b00001001, 0x05, 0b00100000); 
    single_data(0x06, 0b00000110, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00001100, 0x03, 0b11000000); 
    single_data(0x04, 0b00010010, 0x04, 0b00100000); 
    single_data(0x05, 0b00010010, 0x05, 0b00100000); 
    single_data(0x06, 0b00001100, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00011000, 0x03, 0b11000000); 
    single_data(0x04, 0b00100100, 0x04, 0b00100000); 
    single_data(0x05, 0b00100100, 0x05, 0b00100000); 
    single_data(0x06, 0b00011000, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00110000, 0x03, 0b11000000); 
    single_data(0x04, 0b01001000, 0x04, 0b00100000); 
    single_data(0x05, 0b01001000, 0x05, 0b00100000); 
    single_data(0x06, 0b00110000, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b01100000, 0x03, 0b11000000); 
    single_data(0x04, 0b10010000, 0x04, 0b00100000); 
    single_data(0x05, 0b10010000, 0x05, 0b00100000); 
    single_data(0x06, 0b01100000, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b11000000, 0x03, 0b11000000); 
    single_data(0x04, 0b00100000, 0x04, 0b00100000); 
    single_data(0x05, 0b00100000, 0x05, 0b00100000); 
    single_data(0x06, 0b11000000, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b01100000, 0x03, 0b11000000); 
    single_data(0x04, 0b10010000, 0x04, 0b00100000); 
    single_data(0x05, 0b10010000, 0x05, 0b00100000); 
    single_data(0x06, 0b01100000, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00110000, 0x03, 0b11000000); 
    single_data(0x04, 0b01001000, 0x04, 0b00100000); 
    single_data(0x05, 0b01001000, 0x05, 0b00100000); 
    single_data(0x06, 0b00110000, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00011000, 0x03, 0b11000000); 
    single_data(0x04, 0b00100100, 0x04, 0b00100000); 
    single_data(0x05, 0b00100100, 0x05, 0b00100000); 
    single_data(0x06, 0b00011000, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00001100, 0x03, 0b11000000); 
    single_data(0x04, 0b00010010, 0x04, 0b00100000); 
    single_data(0x05, 0b00010010, 0x05, 0b00100000); 
    single_data(0x06, 0b00001100, 0x06, 0b11000000); _delay_ms(35);
     
    single_data(0x03, 0b00000110, 0x03, 0b11000000); 
    single_data(0x04, 0b00001001, 0x04, 0b00100000); 
    single_data(0x05, 0b00001001, 0x05, 0b00100000); 
    single_data(0x06, 0b00000110, 0x06, 0b11000000); _delay_ms(35);
     
    }

    single_data(0x03, 0b00000110, 0x03, 0b01100000); 
    single_data(0x04, 0b00001001, 0x04, 0b10010000); 
    single_data(0x05, 0b00001001, 0x05, 0b10010000); 
    single_data(0x06, 0b00000110, 0x06, 0b01100000); _delay_ms(35);

    single_data(0x03, 0b00001100, 0x03, 0b00110000); 
    single_data(0x04, 0b00010010, 0x04, 0b01001000); 
    single_data(0x05, 0b00010010, 0x05, 0b01001000); 
    single_data(0x06, 0b00001100, 0x06, 0b00110000); _delay_ms(35);
    
    single_data(0x03, 0b00011000, 0x03, 0b00011000); 
    single_data(0x04, 0b00100100, 0x04, 0b00100100); 
    single_data(0x05, 0b00100100, 0x05, 0b00100100); 
    single_data(0x06, 0b00011000, 0x06, 0b00011000); 
 }

void clear() {
    write_data(0x01, 0b00000000);
    write_data(0x02, 0b00000000);
    write_data(0x03, 0b00000000);
    write_data(0x04, 0b00000000);
    write_data(0x05, 0b00000000);
    write_data(0x06, 0b00000000);
    write_data(0x07, 0b00000000);
    write_data(0x08, 0b00000000);
}

void emoji() {
        clear(); _delay_ms(3000);
        
        write_data(0x0A, 0b00011000);    
        write_data(0x03, 0b00011000); _delay_ms(70);
        write_data(0x04, 0b00100100); _delay_ms(70);
        write_data(0x05, 0b01000010); _delay_ms(3000);
    
        write_data(0x03, 0b00000000); _delay_ms(70);
        write_data(0x04, 0b00111100); _delay_ms(200);
           
        write_data(0x04, 0b00000000); _delay_ms(70);
        write_data(0x05, 0b01111110); _delay_ms(1500);
           
        write_data(0x04, 0b00111100); _delay_ms(70);
        write_data(0x05, 0b01000010); _delay_ms(200); 

        write_data(0x03, 0b00011000); _delay_ms(70);
        write_data(0x04, 0b00100100); _delay_ms(70);
        write_data(0x05, 0b01000010); _delay_ms(3000); 

        write_data(0x03, 0b00000000); _delay_ms(70);
        write_data(0x04, 0b00111100); _delay_ms(200); 

        write_data(0x04, 0b00000000); _delay_ms(70);
        write_data(0x05, 0b01111110); _delay_ms(200);
        
        write_data(0x04, 0b00111100); _delay_ms(70);
        write_data(0x05, 0b01000010); _delay_ms(200); 

        write_data(0x03, 0b00011000); _delay_ms(70);
        write_data(0x04, 0b00100100); _delay_ms(70);
        write_data(0x05, 0b01000010); _delay_ms(3000); 

        clear(); _delay_ms(3000);
}

int main(void) {
    SPI_SS_DDR  |= (1 << SPI_SS);
    SPI_SS_PORT |= (1 << SPI_SS);

    SPI_MOSI_DDR  |= (1 << SPI_MOSI);
    SPI_MISO_PORT |= (1 << SPI_MISO);
    SPI_SCK_DDR   |= (1 << SPI_SCK);

    SPCR |= (1 << SPR1);
    SPCR |= (1 << MSTR);
    SPCR |= (1 << SPE);

    write_data(0x0B, 0b00000111);
    write_data(0x0A, 0b00001111);
    write_data(0x0F, 0b00000000);
    write_data(0x0C, 0b00000001);

    clear();
    splash_octocat();

    while(1) {
        clear(); _delay_ms(3000);
        write_data(0x0A, 0b00000011);    

        ping_pong();
        
        bullseye();
        
        write_data(0x08, 0b00011000); _delay_ms(100);

        emoji();

        write_data(0x0A, 0b00000110);    
        write_data(0x07, 0b00011000);
        write_data(0x08, 0b00100100); _delay_ms(100);

        write_data(0x0A, 0b00001001);            
        write_data(0x06, 0b00011000);
        write_data(0x07, 0b00100100);
        write_data(0x08, 0b00100100); _delay_ms(100);

        write_data(0x0A, 0b00001100);            
        write_data(0x05, 0b00011000);
        write_data(0x06, 0b00100100);
        write_data(0x07, 0b00100100);
        write_data(0x08, 0b00011000); _delay_ms(100);

        write_data(0x0A, 0b00001111);            
        write_data(0x04, 0b00011000);
        write_data(0x05, 0b00100100);
        write_data(0x06, 0b00100100);
        write_data(0x07, 0b00011000);
        write_data(0x08, 0b00000000); _delay_ms(3000);

        //look right
        write_data(0x04, 0b00110000);
        write_data(0x05, 0b00001000);
        write_data(0x06, 0b00001000);
        write_data(0x07, 0b00110000); _delay_ms(75);

        write_data(0x05, 0b00010000);
        write_data(0x06, 0b00010000); _delay_ms(1000);

        //look left
        write_data(0x05, 0b00001000);
        write_data(0x06, 0b00001000); _delay_ms(75);

        write_data(0x04, 0b00011000);
        write_data(0x05, 0b00000100);
        write_data(0x06, 0b00000100);
        write_data(0x07, 0b00011000); _delay_ms(75);

        write_data(0x04, 0b00011000);
        write_data(0x05, 0b00100100);
        write_data(0x06, 0b00100100);
        write_data(0x07, 0b00011000);
        write_data(0x08, 0b00000000); _delay_ms(75);

        write_data(0x04, 0b00001100);
        write_data(0x05, 0b00010000);
        write_data(0x06, 0b00010000);
        write_data(0x07, 0b00001100); _delay_ms(75);

        write_data(0x05, 0b00001000);
        write_data(0x06, 0b00001000); _delay_ms(1000);

        //look straight
        write_data(0x05, 0b00010000);
        write_data(0x06, 0b00010000); _delay_ms(75);

        write_data(0x04, 0b00011000);
        write_data(0x05, 0b00100100);
        write_data(0x06, 0b00100100);
        write_data(0x07, 0b00011000);
        write_data(0x08, 0b00000000); _delay_ms(3000);

        //lower eyebrows
        single_data(0x01, 0b00000011, 0x01, 0b11000000); _delay_ms(75);

        single_data(0x01, 0b00111100, 0x01, 0b00111100);
        single_data(0x02, 0b00000011, 0x02, 0b11000000); _delay_ms(75);

        single_data(0x01, 0b11000000, 0x01, 0b00000011);
        single_data(0x02, 0b00111100, 0x02, 0b00111100);
        single_data(0x03, 0b00000011, 0x03, 0b11000000); _delay_ms(3000);

        for(char i = 15; i > 0; i--)
        {
            write_data(0x0A,i); _delay_ms(30);
        }
        
    }

    return(0);
}


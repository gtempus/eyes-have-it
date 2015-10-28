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

int main(void) {
    SPI_SS_DDR  |= (1 << SPI_SS);
    SPI_SS_PORT |= (1 << SPI_SS);

    SPI_MOSI_DDR  |= (1 << SPI_MOSI);
    SPI_MISO_PORT |= (1 << SPI_MISO);
    SPI_SCK_DDR   |= (1 << SPI_SCK);

    SPCR |= (1 << SPR1);
    SPCR |= (1 << MSTR);
    SPCR |= (1 << SPE);

    write_data(0x0B, 0b00000110);
    write_data(0x0A, 0b00001110);
    write_data(0x0F, 0b00000000);
    write_data(0x0C, 0b00000001);
    
    while(1) {
        //clear
        write_data(0x01, 0b00000000);
        write_data(0x02, 0b00000000);
        write_data(0x03, 0b00000000);
        write_data(0x04, 0b00000000);
        write_data(0x05, 0b00000000);
        write_data(0x06, 0b00000000);
        write_data(0x07, 0b00000000);
        write_data(0x08, 0b00000000);

        //show
        write_data(0x01, 0b00100100); _delay_ms(70);
        write_data(0x02, 0b01111110); _delay_ms(70);
        write_data(0x03, 0b01111110); _delay_ms(70);
        write_data(0x04, 0b00111100); _delay_ms(70);
        write_data(0x05, 0b10011000); _delay_ms(70);
        write_data(0x06, 0b01111000); _delay_ms(70);
        write_data(0x07, 0b00011000); _delay_ms(70);
        write_data(0x08, 0b00000000);
        _delay_ms(5000);        
    }
    return(0);
}


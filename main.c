#include <avr/io.h>
#include <util/delay.h>

#define DATA_PIN PB0     // Data pin (DS)
#define CLOCK_PIN PB1    // Clock pin (SH_CP)
#define LATCH_PIN PB2    // Latch pin (ST_CP)

void init() {
    // Set the Data(DS), Clock (SH_CP), Latch (ST_CP) lines as output
    DDRB|=(
        (1<<CLOCK_PIN) |
        (1<<LATCH_PIN) |
        (1<<DATA_PIN));
}


// macros to change data (DS)lines
#define dataHigh() (PORTB |= (1<<DATA_PIN))
#define dataLow()  (PORTB &= (~(1<<DATA_PIN)))

// Sends a clock pulse on Clock pin (SH_CP)
void pulse() {
   PORTB |= (1 << CLOCK_PIN);    //HIGH
   PORTB &= (~(1 << CLOCK_PIN)); //LOW
}

// Sends a clock pulse on Latch pin (ST_CP)
void latch() {
   PORTB |= (1 << LATCH_PIN); //HIGH
   _delay_loop_1(1);

   PORTB &= (~(1 << LATCH_PIN)); //LOW
   _delay_loop_1(1);
}


// write a single byte to shift register 
void shiftOut(uint8_t data) {
   // Order is MSB first
   for(uint8_t i = 0; i < 8; i++) {
      if (data & 0b00000001) {
         dataHigh();
      } else {
         dataLow();
      }

      pulse();       // Pulse the Clock pin
      data=data>>1;  // Now bring next bit at MSB position
   }
}

int main() {
    uint8_t data[40][6]={
        // Blue                    Green                   Red
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
        {0b10000000, 0b00000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000},
        {0b11000000, 0b00000000, 0b11000000, 0b00000000, 0b00000000, 0b00000000},
        {0b11100000, 0b00000000, 0b11100000, 0b00000000, 0b00000000, 0b00000000},
        {0b11110000, 0b00000000, 0b11110000, 0b00000000, 0b00000000, 0b00000000},
        {0b01111000, 0b00000000, 0b01111000, 0b00000000, 0b00000000, 0b00000000},
        {0b00111100, 0b00000000, 0b00111100, 0b00000000, 0b00000000, 0b00000000},
        {0b00011110, 0b00000000, 0b00011110, 0b00000000, 0b00000000, 0b00000000},
        {0b00001111, 0b00000000, 0b00001111, 0b00000000, 0b00000000, 0b00000000},
        {0b00000111, 0b10000000, 0b00000111, 0b10000000, 0b00000000, 0b00000000},
        {0b00000011, 0b11000000, 0b00000011, 0b11000000, 0b00000000, 0b00000000},
        {0b00000001, 0b11100000, 0b00000001, 0b11100000, 0b00000000, 0b00000000},
        {0b00000000, 0b11110000, 0b00000000, 0b11110000, 0b00000000, 0b00000000},
        {0b00000000, 0b01111000, 0b00000000, 0b01111000, 0b00000000, 0b00000000},
        {0b00000000, 0b00111100, 0b00000000, 0b00111100, 0b00000000, 0b00000000},
        {0b00000000, 0b00011110, 0b00000000, 0b00011110, 0b00000000, 0b00000000},
        {0b00000000, 0b00001111, 0b00000000, 0b00001111, 0b00000000, 0b00000000},
        {0b00000000, 0b00000111, 0b00000000, 0b00000111, 0b00000000, 0b00000000},
        {0b00000000, 0b00000011, 0b00000000, 0b00000011, 0b00000000, 0b00000000},
        {0b00000000, 0b00000001, 0b00000000, 0b00000001, 0b00000000, 0b00000000},
        {0b00000000, 0b00000011, 0b00000000, 0b00000011, 0b00000000, 0b00000000},
        {0b00000000, 0b00000111, 0b00000000, 0b00000111, 0b00000000, 0b00000000},
        {0b00000000, 0b00001111, 0b00000000, 0b00001111, 0b00000000, 0b00000000},
        {0b00000000, 0b00011110, 0b00000000, 0b00011110, 0b00000000, 0b00000000},
        {0b00000000, 0b00111100, 0b00000000, 0b00111100, 0b00000000, 0b00000000},
        {0b00000000, 0b01111000, 0b00000000, 0b01111000, 0b00000000, 0b00000000},
        {0b00000000, 0b11110000, 0b00000000, 0b11110000, 0b00000000, 0b00000000},
        {0b00000000, 0b11100000, 0b00000001, 0b11100000, 0b00000000, 0b00000000},
        {0b00000011, 0b11000000, 0b00000011, 0b11000000, 0b00000000, 0b00000000},
        {0b00000111, 0b10000000, 0b00000111, 0b10000000, 0b00000000, 0b00000000},
        {0b00001111, 0b00000000, 0b00001111, 0b00000000, 0b00000000, 0b00000000},
        {0b00011110, 0b00000000, 0b00011110, 0b00000000, 0b00000000, 0b00000000},
        {0b00111100, 0b00000000, 0b00111100, 0b00000000, 0b00000000, 0b00000000},
        {0b01111000, 0b00000000, 0b01111000, 0b00000000, 0b00000000, 0b00000000},
        {0b11110000, 0b00000000, 0b11110000, 0b00000000, 0b00000000, 0b00000000},
        {0b11100000, 0b00000000, 0b11100000, 0b00000000, 0b00000000, 0b00000000},
        {0b11000000, 0b00000000, 0b11000000, 0b00000000, 0b00000000, 0b00000000},
        {0b10000000, 0b00000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000},
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
        {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
    };

    init();

    while(1) {
        for(uint8_t i = 0; i < 40; i++) {
            for (uint8_t j = 0; j < 6; j++) {
                shiftOut(data[i][j]); 
            }

            // Move bits out to shift register at once
            latch();

            _delay_ms(30);
        }
        _delay_ms(1000);
    }
}

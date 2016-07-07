#include <avr/io.h>
#include <util/delay.h>

/***************************************

Configure Connections

****************************************/

#define HC595_PORT   PORTB
#define HC595_DDR    DDRB

#define HC595_DS_POS PB0      //Data pin (DS) pin location

#define HC595_SH_CP_POS PB1      //Shift Clock (SH_CP) pin location 
#define HC595_ST_CP_POS PB2      //Store Clock (ST_CP) pin location

/***************************************
Configure Connections ***ENDS***
****************************************/

//Initialize HC595 System



void HC595Init() {
   //Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output
    HC595_DDR|=(
        (1<<HC595_SH_CP_POS) |
        (1<<HC595_ST_CP_POS) |
        (1<<HC595_DS_POS));
}


//Low level macros to change data (DS)lines
#define HC595DataHigh() (HC595_PORT|=(1<<HC595_DS_POS))
#define HC595DataLow() (HC595_PORT&=(~(1<<HC595_DS_POS)))

//Sends a clock pulse on SH_CP line
void HC595Pulse() {
   //Pulse the Shift Clock
   HC595_PORT|=(1<<HC595_SH_CP_POS);    //HIGH
   HC595_PORT&=(~(1<<HC595_SH_CP_POS)); //LOW
}

//Sends a clock pulse on ST_CP line
void HC595Latch() {
   //Pulse the Store Clock
   HC595_PORT|=(1<<HC595_ST_CP_POS);//HIGH
   _delay_loop_1(1);

   HC595_PORT&=(~(1<<HC595_ST_CP_POS));//LOW
   _delay_loop_1(1);
}


/*

Main High level function to write a single byte to
Output shift register 74HC595. 

Arguments:
   single byte to write to the 74HC595 IC

Returns:
   NONE

Description:
   The byte is serially transfered to 74HC595
   and then latched. The byte is then available on
   output line Q0 to Q7 of the HC595 IC.

*/
void HC595Write(uint8_t data) {
   //Send each 8 bits serially

   //Order is MSB first
   for(uint8_t i = 0; i < 8; i++) {
      //Output the data on DS line according to the
      //Value of MSB
      if (data & 0b00000001) {
         //MSB is 1 so output high
         HC595DataHigh();
      } else {
         //MSB is 0 so output high
         HC595DataLow();
      }

      HC595Pulse();  //Pulse the Clock line
      data=data>>1;  //Now bring next bit at MSB position
   }

}

/*
 * Simple Delay function approx 0.5 seconds
 */
void wait(uint8_t t) {
   for(uint8_t i = 0; i < t; i++) {
      _delay_loop_2(0);
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

    //Initialize HC595 system
    HC595Init();

    while(1) {
        for(uint8_t i = 0; i < 40; i++) {
            for (uint8_t j = 0; j < 6; j++) {
                HC595Write(data[i][j]);   //Write the data to HC595
            }

            //Now all bits have been transferred to shift register
            //Move them to output latch at once
            HC595Latch();

            _delay_ms(30);
        }
        _delay_ms(1000);
    }
}

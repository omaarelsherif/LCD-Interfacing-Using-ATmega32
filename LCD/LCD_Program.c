#include "STD_TYPES.h"
#include <avr/delay.h>
#include "LCD_Private.h"
#include "DIO_Interface.h"
#include <avr/delay.h>

// Function to initialize the LCD based on the datasheet
void LCD_VoidInit()
{
    // Set data direction as output
    DIO_VoidSetPortDirection(DATA_PORT, 0b11111111);

    // Set pin directions as output
    DIO_VoidSetPinDirection(CFG_PORT, 0, 1);    // Pin0 : Rs
    DIO_VoidSetPinDirection(CFG_PORT, 1, 1);    // Pin1 : Rw
    DIO_VoidSetPinDirection(CFG_PORT, 2, 1);    // Pin2 : En

    // Wait for more than 30ms after Vdd rises to 4.5v
    _delay_ms(40);

    // Function set command (Rs = 0 , Rw = 0)
    // Command : 001DLNFXX
    // DL (data length) [0: 4-bit] [1: 8-bits]
    // N (number of lines) [0: 1 line] [1 : 2 lines]
    // F (character font) [0: 5*7 dots] [1 : 5*10 dots]
    // XX : don't care
    LCD_VoidWriteCommand(0b00111000);

    // Wait for more than 39μs
    _delay_ms(1);

    // Display on/off control command
    // Command : 00001DCB
    // D (display on or off) [0: off] [1: on]
    // C (cursor display) [0: off] [1: on]
    // B (cursor blink) [0: off] [1: on]
    LCD_VoidWriteCommand(0b00001111);

    // Wait for more than 1ms
    _delay_ms(1);

    // Display clear command
    // Command : 00000001
    LCD_VoidWriteCommand(0b00000001);

    // Wait for more than 1.53ms
    _delay_ms(2);
}

// Function to write command to the LCD
void LCD_VoidWriteCommand(u8 Command)
{
    // Set Rs = 0 to enable write command mode
    DIO_VoidSetPinValue(CFG_PORT, 0, 0);

    // Set Rw = 0 to enable write mode
    DIO_VoidSetPinValue(CFG_PORT, 1, 0);

    // Write command from the port
    DIO_VoidSetPortValue(DATA_PORT, Command);

    // Set En = 1 to enable the LCD
    DIO_VoidSetPinValue(CFG_PORT, 2, 1);    // set high level (raising edge)
    _delay_ms(1);                              // delay
    DIO_VoidSetPinValue(CFG_PORT, 2, 0);    // set low level (falling edge)
    _delay_ms(1);                              // delay
}

// Function to write data (character) to the LCD
void LCD_VoidWriteChar(u8 Character)
{
    // Set Rs = 1 to enable write data mode
    DIO_VoidSetPinValue(CFG_PORT, 0, 1);

    // Set Rw = 0 to enable write mode
    DIO_VoidSetPinValue(CFG_PORT, 1, 0);

    // Write data from the port
    DIO_VoidSetPortValue(DATA_PORT, Character);

    // Set En = 1 to enable the LCD
    DIO_VoidSetPinValue(CFG_PORT, 2, 1);    // set high level (raising edge)
    _delay_ms(1);                    		   // delay
    DIO_VoidSetPinValue(CFG_PORT, 2, 0);    // set low level (falling edge)
    _delay_ms(1);                              // delay
}

// Function to write data (string) to the LCD
void LCD_VoidWriteString(const u8* String)
{
    // Iterate through each character in the string
    for (u8 i = 0; String[i] != '\0'; i++)
    {
        // Call LCD_VoidWriteData to send the character to the LCD
        LCD_VoidWriteChar(String[i]);
        _delay_ms(200);
    }
}

// Function to write data (number) to the LCD
void LCD_VoidWriteNumber(u8 Number)
{
    // Initialize empty numbers
    u8 rev = 0;
    u8 x = 0;

    // Reverse number first 
    while(Number != 0)
    {
        rev = rev * 10 + (Number % 10);
        Number /= 10;
    }
    
    // Send number one by one 
    while(rev != 0)
    {
        x = rev % 10;
        rev /= 10;
        LCD_VoidWriteChar(x + 48);
    }
}


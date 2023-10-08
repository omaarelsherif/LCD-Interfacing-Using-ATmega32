/*
 * LCD
 * Author: OmarElsherif
 */

// Include libraries
#include "LIB/STD_TYPES.h"
#include "MCAL/DIO_Interface.h"
#include "HAL/LCD_Interface.h"
#include "HAL/LCD_Interface.h"

// Main function
void main(void)
{
	// Initialize the LCD
	LCD_VoidInit();

	// Write a message as string to LCD
	const u8 message[] = "Hello, World!";
	LCD_VoidWriteString(message);

	while(1)
	{

	}
}

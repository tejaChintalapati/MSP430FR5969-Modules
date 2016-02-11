/*
 * FRAM.c
 *
 *  Created on: Feb 11, 2016
 *  Author: Teja Chintalapati
 *	Contact: teja.chintalapati@gmail.com
 *	Phone: +91-8792-355-512
 *	Description: Contains code to read and write into FRAM
 *
 */

/******************************************************************************
 * INCLUDES
 */

#include "FRAM.h"

/******************************************************************************
 * DEFINITIONS
 */

//To know till what address FRAM is filled
#define	FRAM_FILL_LOCATION							0xBABA

/******************************************************************************
 * FUNCTION DEFINITION
 */

void FRAMWriteString(uint8_t *writeAddress, char *writeData)
{
	uint16_t *ptr;
	while(*writeData != '\0')
	{
		*(writeAddress++) = *writeData++;
		//Incrementing the address till which FRAM is filled
		ptr = (uint16_t *)FRAM_FILL_LOCATION;
		*ptr = *ptr + 1;
	}
}

void FRAMReadString(uint8_t *readAddress, char *readData, uint16_t dataLength)
{
	while(dataLength-- > 0)
		*readData++ = (*readAddress++);

}

void FRAMClearData(uint8_t *endAddress, uint8_t *startAddress)
{
	uint16_t *ptr;
	while(endAddress - startAddress + 1)
	{
		*(startAddress++) = 0xFF;
		//Decrementing the address till which FRAM is written
		ptr = (uint16_t *)FRAM_FILL_LOCATION;
		*ptr = *ptr - 1;
	}
	//We've deleted one extra location. So, add 1
	*ptr = *ptr + 1;
}

void FRAMClearAll(void)
{
	FRAMClearData((uint8_t *) 0xFFE0, (uint8_t *)0xC000);
	*lastFilledFRAMLocation = START_ADDRESS;
}

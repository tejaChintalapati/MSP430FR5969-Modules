/*
 *  FRAM.c
 *  Created on: Jan 29, 2016
 *  Author: Teja Chintalapati
 *	Contact: teja.chintalapati@gmail.com
 *	Phone: +91-8792-355-512
 *	Description: This file will initialise MCLK to 8MHz, SMCLK to 8MHz and ACLK to 32768Hz
 *
 */

#ifndef FRAM_SOURCE_H_
#define FRAM_SOURCE_H_

/******************************************************************************
 * FUNCTION DECLARATION
 */

/*
 * FRAMWriteString
 * Description		: Writes a string into FRAM
 * Arguments		:
 * 1. writeAddress	: Starting address location to write string
 * 2. writeData		: String that is to be written
 *
 */
void FRAMWriteString(uint8_t *writeAddress, char *writeData);

/*
 * FRAMReadString
 * Description		: 	Reads a string From FRAM
 * Arguments		:
 * 1. readAddress	: 	Starting address location from where string is to be read
 * 2. readData		: 	Buffer where data is to be stored
 * 3. dataLength	:	# Bytes of data to be read
 *
 */

void FRAMReadString(uint8_t *readAddress, char *readData, uint16_t dataLength);

/*
 * FRAMClearData
 * Description	   :	Clears data from 1st argument till second argument
 * Arguments	   :
 * 1. startAddress : 	Starting address location from where data is to be cleared
 * 2. endAddress   : 	End address location till where data is to be cleared
 *
 */

void FRAMClearData(uint8_t *startAddress, uint8_t *endAddress);

/*
 * FRAMClearAll
 * Description	   :	Clears all data in FRAM from 0xC000 till 0xFFE0
 *
 */

void FRAMClearAll(void);

#endif

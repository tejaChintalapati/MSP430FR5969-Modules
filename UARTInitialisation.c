/*
 * UARTInitialisation.c
 *
 *  Created on: Jan 19, 2016
 *  Author: Teja Chintalapati
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 tejaChintalapati
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * --/COPYRIGHT--*/

/******************************************************************************
 * INCLUDES
 */

#include "mainApp.h"

/******************************************************************************
 * DEFINITIONS
 */

void UARTInitialisation(void)
{
	// Configure UART
	EUSCI_A_UART_initParam param = {0};
	param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_ACLK;
	param.clockPrescalar = 3;
	param.firstModReg = 0;
	param.secondModReg = 146;
	param.parity = EUSCI_A_UART_NO_PARITY;
	param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
	param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
	param.uartMode = EUSCI_A_UART_MODE;
	param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

	if(STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A1_BASE, &param))
	{
		return;
	}

	EUSCI_A_UART_enable(EUSCI_A1_BASE);

	EUSCI_A_UART_clearInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);

	// Enable USCI_A0 RX interrupt
	EUSCI_A_UART_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT); // Enable interrupt
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A0_VECTOR)))
#endif
void USCI_A1_ISR(void)
{
	switch(__even_in_range(UCA1IV,USCI_UART_UCTXCPTIFG))
	{
	case USCI_NONE: break;
	case USCI_UART_UCRXIFG:
		if(EUSCI_A_UART_receiveData(EUSCI_A1_BASE) != '@')
			RXDataBuffer[rxBufferIndex++] = EUSCI_A_UART_receiveData(EUSCI_A1_BASE);
		else
			__low_power_mode_off_on_exit();
	case USCI_UART_UCTXIFG: break;
	case USCI_UART_UCSTTIFG: break;
	case USCI_UART_UCTXCPTIFG: break;
	}
}

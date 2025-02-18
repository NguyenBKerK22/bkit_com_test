/*
 * application.h
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "stdarg.h"
#include "stdlib.h"
#ifndef INC_HARDWARE_H_
#define INC_HARDWARE_H_
typedef enum{
	UART,
	SPI,
	I2C
}USER_CHOICE;
typedef enum{
	SLAVE,
	MASTER,
	NONE
}SPI_CONFIG;
struct protocol{
	USER_CHOICE user;
	UART_HandleTypeDef* uart;
	SPI_HandleTypeDef* spi;
	I2C_HandleTypeDef* i2c;
};
struct BKIT_COM_Hardware{
	struct protocol used_protocol;
	uint8_t rx_buffer[256];
	uint8_t tx_buffer[256];
	uint8_t rx_size;
	uint8_t state;
	uint8_t isDataCome;
};
typedef enum{
	RECEIVED_HEADER,
	RECEIVED_PACKET,
	SEND_PAYLOAD
}Hardware_StateTypedef;
typedef enum{
	BKIT_COM_OK 		= 	0x00U,
	BKIT_COM_ERROR		=	0x01U,	// Transmit in HW layer fail
	BKIT_COM_BUSY		=	0x02U,	// Waiting for message
	BKIT_COM_TIMEOUT	=	0x03U,
	BKIT_COM_FAIL		=	0x04U	// Wrong Message or Missing Message
}BKIT_COM_StateTypedef;
extern struct BKIT_COM_Hardware hardware;
extern I2C_HandleTypeDef hi2c2;
void BKIT_COM_HW_Init(USER_CHOICE user_choice, int arg1);
BKIT_COM_StateTypedef BKIT_COM_HW_Receive(uint8_t* buffer, uint32_t Timeout);
void BKIT_COM_HW_Send(uint8_t* buffer, int size);
#define BKIT_COM_HW_Init_UART(a) BKIT_COM_HW_Init(UART, a); // UART(1
#define BKIT_COM_HW_Init_SPI(a) BKIT_COM_HW_Init(SPI, a);
#define BKIT_COM_HW_Init_I2C(a) BKIT_COM_HW_Init(I2C, a);
#endif /* INC_HARDWARE_H_ */

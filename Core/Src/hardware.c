///*
// * application.c
// *
// *  Created on: Feb 7, 2025
// *      Author: ADMIN
// */
//
//#include "hardware.h"
///*
// * Hardware_Interface_Layer.c
// *
// *  Created on: Jan 31, 2025
// *      Author: ASUS
// */
//struct BKIT_COM_Hardware hardware;
//int flag_tx = 0;
//void BKIT_COM_HW_Init(USER_CHOICE user_choice, int arg1){
//	hardware.used_protocol.user = user_choice;
//	hardware.rx_size = 0; // size of header
//	hardware.isDataCome = 0;
//	hardware.state = RECEIVED_HEADER;
//	switch(user_choice){
//	case UART:
//		switch(arg1){
//		case 1:
//			hardware.used_protocol.uart = &huart1;
//			break;
//		case 2:
//			hardware.used_protocol.uart = &huart2;
//			break;
//		case 3:
//			hardware.used_protocol.uart = &huart3;
//			break;
//		default:
//			break;
//			HAL_UART_Receive_IT(hardware.used_protocol.uart, hardware.rx_buffer, 4);
////			HAL_UART_Receive_DMA(hardware.used_protocol.uart, hardware.rx_buffer, 4);
//		}
//		break;
//	case SPI:
//		switch(arg1){
//		case SLAVE:
//			hardware.used_protocol.spi = &hspi1;
//			HAL_SPI_TransmitReceive_IT(hardware.used_protocol.spi, hardware.tx_buffer ,hardware.rx_buffer , 4);
////			HAL_SPI_Receive_DMA(hardware.used_protocol.spi, hardware.rx_buffer, 4);
//			break;
//		case MASTER:
//			hardware.used_protocol.spi = &hspi2;
//			break;
//		default:
//			break;
//		}
//		break;
//	case I2C:
//		switch(arg1){
//		case 1:
//			hardware.used_protocol.i2c = &hi2c1;
//			break;
//		case 2:
////			hardware.used_protocol.i2c = &hi2c2;
//			break;
//		default:
//			break;
//		}
//		break;
//	default:
//		break;
//	}
//}
//BKIT_COM_StateTypedef BKIT_COM_HW_Receive(uint8_t* buffer, uint32_t Timeout){
//	if(hardware.used_protocol.spi == &hspi1){
//			if(buffer == NULL){
//				return BKIT_COM_ERROR;
//			}
//			uint32_t tickStart = HAL_GetTick();
//			while(hardware.isDataCome == 0){
//				if(HAL_GetTick() - tickStart >= Timeout){
//					return BKIT_COM_TIMEOUT;
//				}
//			}
//			hardware.isDataCome = 0;
//			hardware.rx_size = hardware.rx_buffer[3] + 4;
//			for(int i = 0; i < hardware.rx_size; i++){
//				buffer[i] = hardware.rx_buffer[i];
//			}
//			return BKIT_COM_OK;
//	}
//	HAL_GPIO_WritePin(SPI2_CSS_GPIO_Port, SPI2_CSS_Pin, RESET);
//	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(hardware.used_protocol.spi,  hardware.tx_buffer,hardware.rx_buffer, 4, 1000);
//	if(status == HAL_OK){
//		HAL_UART_Transmit(&huart1,hardware.rx_buffer, 4, Timeout);
//		status = HAL_SPI_TransmitReceive(hardware.used_protocol.spi,  hardware.tx_buffer,hardware.rx_buffer, 4 , 1000);
//	}
//	HAL_UART_Transmit(&huart1,hardware.rx_buffer, 4, Timeout);
//	HAL_GPIO_WritePin(SPI2_CSS_GPIO_Port, SPI2_CSS_Pin, SET);
//	//#define HAL_SPI_ERROR_NONE              (0x00000000U)   /*!< No error                               */
//	//#define HAL_SPI_ERROR_MODF              (0x00000001U)   /*!< MODF error                             */
//	//#define HAL_SPI_ERROR_CRC               (0x00000002U)   /*!< CRC error                              */
//	//#define HAL_SPI_ERROR_OVR               (0x00000004U)   /*!< OVR error                              */
//	//#define HAL_SPI_ERROR_DMA               (0x00000010U)   /*!< DMA transfer error                     */
//	//#define HAL_SPI_ERROR_FLAG              (0x00000020U)   /*!< Error on RXNE/TXE/BSY Flag             */
//	//#define HAL_SPI_ERROR_ABORT
//	return (BKIT_COM_StateTypedef)status;
//}
//void BKIT_COM_HW_Send(uint8_t* buffer){
//	switch(hardware.used_protocol.user){
//		case UART:
//			HAL_UART_Transmit(hardware.used_protocol.uart, (uint8_t*)buffer, 4, HAL_MAX_DELAY);
//			HAL_Delay(5);
//			HAL_UART_Transmit(hardware.used_protocol.uart, (uint8_t*)buffer + 4, * (buffer + 3), HAL_MAX_DELAY);
//		break;
//		case SPI:
//			if(hardware.used_protocol.spi == &hspi2){
//				HAL_GPIO_WritePin(SPI2_CSS_GPIO_Port, SPI2_CSS_Pin, RESET);
//				HAL_SPI_TransmitReceive(hardware.used_protocol.spi, (uint8_t*)buffer, (uint8_t*)hardware.rx_buffer, 4, HAL_MAX_DELAY);
//				HAL_Delay(5);
//				HAL_SPI_TransmitReceive(hardware.used_protocol.spi, (uint8_t*)buffer + 4, (uint8_t*)hardware.rx_buffer, * (buffer + 3), HAL_MAX_DELAY);
//				HAL_GPIO_WritePin(SPI2_CSS_GPIO_Port, SPI2_CSS_Pin, SET);
//			}
//			else{
//				for(int i=0;i<8;i++){
//
//				}
//			}
//		break;
//		case I2C:
//			break;
//		default:
//		break;
//	}
//}
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//	switch(hardware.state){
//		case RECEIVED_HEADER:
//			HAL_UART_Receive_IT(hardware.used_protocol.uart, hardware.rx_buffer, hardware.rx_buffer[3]);
//			hardware.state = RECEIVED_PACKET;
//			break;
//		case RECEIVED_PACKET:
//			hardware.isDataCome = 1;
//			HAL_UART_Receive_IT(hardware.used_protocol.uart, hardware.rx_buffer, 4);
//			hardware.state = RECEIVED_HEADER;
//			break;
//		default:
//			break;
//	}
//}
//void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef * hspi){
//	switch(hardware.state){
//		case RECEIVED_HEADER:
//			HAL_SPI_TransmitReceive_IT(hardware.used_protocol.spi, hardware.tx_buffer + 4, hardware.rx_buffer + 4, hardware.rx_buffer[3]);
//			hardware.state = RECEIVED_PACKET;
//			break;
//		case RECEIVED_PACKET:
//			hardware.isDataCome = 1;
//			HAL_SPI_TransmitReceive_IT(hardware.used_protocol.spi, hardware.tx_buffer, hardware.rx_buffer, 4);
//			hardware.state = RECEIVED_HEADER;
//			break;
//		default:
//			break;
//	}
//}
/*
 * application.c
 *
 *  Created on: Feb 7, 2025
 *      Author: ADMIN
 */

#include "hardware.h"
/*
 * Hardware_Interface_Layer.c
 *
 *  Created on: Jan 31, 2025
 *      Author: ASUS
 */
struct BKIT_COM_Hardware hardware;
void BKIT_COM_HW_Init(USER_CHOICE user_choice, int arg1){
	hardware.used_protocol.user = user_choice;
	hardware.rx_size = 0; // size of header
	hardware.isDataCome = 0;
	hardware.state = RECEIVED_HEADER;
	switch(user_choice){
	case UART:
		switch(arg1){
		case 1:
			hardware.used_protocol.uart = &huart1;
			break;
		case 2:
			hardware.used_protocol.uart = &huart2;
			break;
		case 3:
			hardware.used_protocol.uart = &huart3;
			break;
		default:
			break;
			HAL_UART_Receive_IT(hardware.used_protocol.uart, hardware.rx_buffer, 4);
//			HAL_UART_Receive_DMA(hardware.used_protocol.uart, hardware.rx_buffer, 4);
		}
		break;
	case SPI:
		switch(arg1){
		case SLAVE:
			hardware.used_protocol.spi = &hspi1;
			HAL_SPI_TransmitReceive_IT(hardware.used_protocol.spi, hardware.tx_buffer ,hardware.rx_buffer , 4);
//			HAL_SPI_Receive_DMA(hardware.used_protocol.spi, hardware.rx_buffer, 4);
			break;
		case MASTER:
			hardware.used_protocol.spi = &hspi2;
			break;
		default:
			break;
		}
		break;
	case I2C:
		switch(arg1){
		case 1:
			hardware.used_protocol.i2c = &hi2c1;
			break;
		case 2:
//			hardware.used_protocol.i2c = &hi2c2;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
BKIT_COM_StateTypedef BKIT_COM_HW_Receive(uint8_t* buffer, uint32_t Timeout){
	// Slave
	if(hardware.used_protocol.spi == &hspi1){
		if(!buffer){
			return BKIT_COM_ERROR;
		}
		// timer here

		if(hardware.isDataCome){
			hardware.isDataCome = 0;
			hardware.rx_size = hardware.rx_buffer[3] + 4;
			for(int i = 0; i < hardware.rx_size; i++){
				buffer[i] = hardware.rx_buffer[i];
			}
			return BKIT_COM_OK;
		}
		return BKIT_COM_BUSY;
	}
	// Master
	HAL_GPIO_WritePin(SPI2_CSS_GPIO_Port, SPI2_CSS_Pin, RESET);
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(hardware.used_protocol.spi,  hardware.tx_buffer,hardware.rx_buffer, 4, 2000);
	if(status == HAL_OK){
		HAL_UART_Transmit(&huart1,hardware.rx_buffer, 4, Timeout);
		status = HAL_SPI_TransmitReceive(hardware.used_protocol.spi,  hardware.tx_buffer, hardware.rx_buffer + 4, 4 , 2000);
	}
	HAL_UART_Transmit(&huart1,hardware.rx_buffer, 8, Timeout);
	HAL_GPIO_WritePin(SPI2_CSS_GPIO_Port, SPI2_CSS_Pin, SET);
	return (BKIT_COM_StateTypedef)status;
}
void BKIT_COM_HW_Send(uint8_t* buffer,int size){
	switch(hardware.used_protocol.user){
		case UART:
			HAL_UART_Transmit(hardware.used_protocol.uart, (uint8_t*)buffer, 4, HAL_MAX_DELAY);
			HAL_Delay(5);
			HAL_UART_Transmit(hardware.used_protocol.uart, (uint8_t*)buffer + 4, * (buffer + 3), HAL_MAX_DELAY);
		break;
		case SPI:
			if(hardware.used_protocol.spi == &hspi2){
				HAL_GPIO_WritePin(SPI2_CSS_GPIO_Port, SPI2_CSS_Pin, RESET);
				HAL_SPI_TransmitReceive(hardware.used_protocol.spi, (uint8_t*)buffer, (uint8_t*)hardware.rx_buffer, 4, HAL_MAX_DELAY);
				HAL_Delay(3);
				HAL_SPI_TransmitReceive(hardware.used_protocol.spi, (uint8_t*)buffer + 4, (uint8_t*)hardware.rx_buffer, * (buffer + 3), HAL_MAX_DELAY);
				HAL_GPIO_WritePin(SPI2_CSS_GPIO_Port, SPI2_CSS_Pin, SET);
			}
			else{
				for(int i = 0; i < size; i++){
					hardware.tx_buffer[i] = buffer[i];
				}
				hardware.used_protocol.spi->Instance->DR = hardware.tx_buffer[0];
				hardware.state = SEND_PAYLOAD;
			}
		break;
		case I2C:
			break;
		default:
		break;
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	switch(hardware.state){
		case RECEIVED_HEADER:
			HAL_UART_Receive_IT(hardware.used_protocol.uart, hardware.rx_buffer, hardware.rx_buffer[3]);
			hardware.state = RECEIVED_PACKET;
			break;
		case RECEIVED_PACKET:
			hardware.isDataCome = 1;
			HAL_UART_Receive_IT(hardware.used_protocol.uart, hardware.rx_buffer, 4);
			hardware.state = RECEIVED_HEADER;
			break;
		default:
			break;
	}
}
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef * hspi){
	switch(hardware.state){
		case RECEIVED_HEADER:
			HAL_SPI_TransmitReceive_IT(hardware.used_protocol.spi, hardware.tx_buffer + 4, hardware.rx_buffer + 4, hardware.rx_buffer[3]);
			hardware.state = RECEIVED_PACKET;
			break;
		case RECEIVED_PACKET:
			hardware.isDataCome = 1;
			HAL_SPI_TransmitReceive_IT(hardware.used_protocol.spi, hardware.tx_buffer, hardware.rx_buffer, 4);
			hardware.state = RECEIVED_HEADER;
			break;
		case SEND_PAYLOAD:
			HAL_SPI_TransmitReceive_IT(hardware.used_protocol.spi, hardware.tx_buffer + 4, hardware.rx_buffer, hardware.tx_buffer[3]);
			hardware.state = RECEIVED_HEADER;
			break;
		default:
			break;
	}
}

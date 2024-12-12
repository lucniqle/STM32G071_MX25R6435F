/*
 * MX25R6435F.h
 *
 *  Created on: Nov 12, 2024
 *      Author: Lukas
 */

#ifndef INC_MX25R6435F_H_
#define INC_MX25R6435F_H_

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "MX25R6435F_desc.h"

typedef enum{
  MX_OK       = 0x00U,
  MX_ERROR    = 0x01U,
  MX_BUSY     = 0x02U,
} MX_Err;

void Set_CS_Pin(GPIO_PinState State);

void Delay_ms(uint32_t delay);

uint8_t SPI_Send(uint8_t *pData, uint16_t size, uint32_t timeout);

uint8_t SPI_Receive(uint8_t *pData, uint16_t size, uint32_t timeout);

MX_Err MX_Init(void);

MX_Err MX_Get_ID(uint8_t *data);

MX_Err MX_Get_Status(uint8_t *data);

MX_Err MX_Config_Read(uint8_t *data);

MX_Err MX_Config_Write(uint8_t status, uint16_t cfg);

MX_Err MX_Enable_Write(void);

MX_Err MX_Disable_Write(void);

bool MX_Available(void);

bool MX_Write_Enabled(void);

MX_Err MX_Erase_Sector(uint32_t address);

MX_Err MX_Erase_Block32(uint32_t address);

MX_Err MX_Erase_Block64(uint32_t address);

MX_Err MX_Read_Bytes(uint8_t *data, uint32_t address, uint32_t size);

MX_Err MX_Write_Page(uint8_t *pData, uint32_t address, uint32_t size);

MX_Err MX_Write_Bytes(uint8_t *pData, uint32_t address, uint32_t size);

MX_Err MX_Enter_Deep_Power_Down(void);

void MX_Exit_Deep_Power_Down(void);


#endif /* INC_MX25R6435F_H_ */

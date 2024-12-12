/*
 * MX25R6435F.c
 *
 *  Created on: Nov 12, 2024
 *      Author: Lukas
 */

#include <stdio.h>
#include <stdlib.h>
#include "MX25R6435F.h"

/**
* @brief Initiates the memory for use
* @param None
* @retval Status
*/
MX_Err MX_Init(void){
	uint8_t command = 0;

	Set_CS_Pin(GPIO_PIN_RESET);
	command = RESET_ENABLE_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command reset enable to MX\r\n");
		Set_CS_Pin(GPIO_PIN_RESET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	Delay_ms(1);

	Set_CS_Pin(GPIO_PIN_RESET);
	command = RESET_MEMORY_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command reset MX to MX\r\n");
		Set_CS_Pin(GPIO_PIN_RESET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Get memory chip ID
* @param None
* @retval Status - ID
*/
MX_Err MX_Get_ID(uint8_t *data){
	uint8_t command = 0;

	Set_CS_Pin(GPIO_PIN_RESET);
	command = READ_ID_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command read ID to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	else{
		if(SPI_Receive(data, 3, 1000) != HAL_OK){
			printf("Error receiving ID\r\n");
			Set_CS_Pin(GPIO_PIN_SET);
			return MX_ERROR;
		}
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Get memory status register
* @param None
* @retval Status - Status Register
*/
MX_Err MX_Get_Status(uint8_t *data){
	uint8_t command = 0;

	Set_CS_Pin(GPIO_PIN_RESET);
	command = READ_STATUS_REG_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command get status to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	else{
		if(SPI_Receive(data, 1, 1000) != HAL_OK){
			printf("Error receiving status\r\n");
			Set_CS_Pin(GPIO_PIN_SET);
			return MX_ERROR;
		}
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Enable memory for write operation
* @param None
* @retval Status
*/
MX_Err MX_Enable_Write(void){
	uint8_t command = 0;

	Set_CS_Pin(GPIO_PIN_RESET);
	command = WRITE_ENABLE_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command enable write to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Disable memory for write operations
* @param None
* @retval Status
*/
MX_Err MX_Disable_Write(void){
	uint8_t command = 0;

	Set_CS_Pin(GPIO_PIN_RESET);
	command = WRITE_DISABLE_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command disable write to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Check if memory is available for next operation
* @param None
* @retval Available(true)/Not Available (false)
*/
bool MX_Available(void){
	uint8_t data;

	MX_Get_Status(&data);
	if((data & MX25R6435F_SR_WIP) == 0x01){
		return false;
	}
	return true;
}

/**
* @brief Check if memory is available for write operation
* @param None
* @retval Available(true)/Not Available (false)
*/
bool MX_Write_Enabled(void){
	uint8_t data;

	MX_Get_Status(&data);
	if((data & MX25R6435F_SR_WEL) != 0x02){
		return false;
	}
	return true;
}

/**
* @brief Read memory configuration registers
* @param None
* @retval Status - Configuration registers
*/
MX_Err MX_Config_Read(uint8_t *data){
	uint8_t command = 0;

	Set_CS_Pin(GPIO_PIN_RESET);
	command = READ_CFG_REG_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command read cfg to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	else{
		if(SPI_Receive(data, 2, 1000) != HAL_OK){
			printf("Error receiving cfg\r\n");
			Set_CS_Pin(GPIO_PIN_SET);
			return MX_ERROR;
		}
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Write configuration to memory
* @param status: status register
* @param cfg: configuration registers
* @retval Available(true)/Not Available (false)
*/
MX_Err MX_Config_Write(uint8_t status, uint16_t cfg){
	uint8_t command = 0;
	uint8_t data[3] = {status, (cfg >> 8) & 0xFF, cfg & 0xFF};

	while(!MX_Available()){
		printf("MX Busy\r\n");
		Delay_ms(10);
	}

	if(MX_Enable_Write() != MX_OK){
		printf("Error setting write");
		return MX_ERROR;
	}

	if(!MX_Write_Enabled()){
		printf("MX write not available\r\n");
		return MX_ERROR;
	}

	Set_CS_Pin(GPIO_PIN_RESET);
	command = WRITE_STATUS_CFG_REG_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command write cfg reg to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	if(SPI_Send(data, 3, 1000) != HAL_OK){
		printf("Error sending cfg to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;

}

/**
* @brief Erase sector (0x1000)
* @param address: Sector address
* @retval Status
*/
MX_Err MX_Erase_Sector(uint32_t address){
	uint8_t command = 0;
	uint8_t addr[3] = {(address >> 16) & 0xFF, (address >> 8) & 0xFF, address & 0xFF};

	if(address >= (MX25R6435F_FLASH_SIZE / MX25R6435F_SECTOR_SIZE)){
		printf("Invalid Sector Addr: %ld\r\n", address);
		return MX_ERROR;
	}

	while(!MX_Available()){
		printf("MX Busy\r\n");
		Delay_ms(10);
	}

	if(MX_Enable_Write() != MX_OK){
		printf("Error setting write");
		return MX_ERROR;
	}

	if(!MX_Write_Enabled()){
		printf("MX write not available\r\n");
		return MX_ERROR;
	}

	Set_CS_Pin(GPIO_PIN_RESET);
	command = SECTOR_ERASE_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command erase sector to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	if(SPI_Send(addr, 3, 1000) != HAL_OK){
		printf("Error sending erases sector addr to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Erase block (0x8000)
* @param address: Block address
* @retval Status
*/
MX_Err MX_Erase_Block32(uint32_t address){
	uint8_t command = 0;
	uint8_t addr[3] = {(address >> 16) & 0xFF, (address >> 8) & 0xFF, address & 0xFF};

	if(address >= (MX25R6435F_FLASH_SIZE / MX25R6435F_SUBBLOCK_SIZE)){
		printf("Invalid Block32 Addr: %ld\r\n", address);
		return MX_ERROR;
	}

	while(!MX_Available()){
		printf("MX Busy\r\n");
		Delay_ms(10);
	}

	if(MX_Enable_Write() != MX_OK){
		printf("Error setting write");
		return MX_ERROR;
	}

	if(!MX_Write_Enabled()){
		printf("MX write not available\r\n");
		return MX_ERROR;
	}

	Set_CS_Pin(GPIO_PIN_RESET);
	command = SUBBLOCK_ERASE_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command erase block32 to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	if(SPI_Send(addr, 3, 1000) != HAL_OK){
		printf("Error sending erases block32 addr to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Erase block (0x10000)
* @param address: Block address
* @retval Status
*/
MX_Err MX_Erase_Block64(uint32_t address){
	uint8_t command = 0;
	uint8_t addr[3] = {(address >> 16) & 0xFF, (address >> 8) & 0xFF, address & 0xFF};

	if(address >= (MX25R6435F_FLASH_SIZE / MX25R6435F_BLOCK_SIZE)){
		printf("Invalid Block64 Addr: %ld\r\n", address);
		return MX_ERROR;
	}

	while(!MX_Available()){
		printf("MX Busy\r\n");
		Delay_ms(10);
	}

	if(MX_Enable_Write() != MX_OK){
		printf("Error setting write");
		return MX_ERROR;
	}

	if(!MX_Write_Enabled()){
		printf("MX write not available\r\n");
		return MX_ERROR;
	}

	Set_CS_Pin(GPIO_PIN_RESET);
	command = BLOCK_ERASE_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command erase block64 to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	if(SPI_Send(addr, 3, 1000) != HAL_OK){
		printf("Error sending erases block64 addr to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Erase memory
* @param None
* @retval Status
*/
MX_Err MX_Erase_Chip(void){
	uint8_t command = 0;

	while(!MX_Available()){
		printf("MX Busy\r\n");
		Delay_ms(10);
	}

	if(MX_Enable_Write() != MX_OK){
		printf("Error setting write");
		return MX_ERROR;
	}

	if(!MX_Write_Enabled()){
		printf("MX write not available\r\n");
		return MX_ERROR;
	}

	Set_CS_Pin(GPIO_PIN_RESET);
	command = CHIP_ERASE_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command erase chip to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Read bytes from memory
* @param address: Starting read address
* @param size: Size to read
* @retval Status - Data Read
*/
MX_Err MX_Read_Bytes(uint8_t *data, uint32_t address, uint32_t size){
	uint8_t command = 0;
	uint32_t addr = address;


	if(address + size > (MX25R6435F_FLASH_SIZE)){
		printf("Final address bigger than memory capacity: %ld\r\n", address + size);
		return MX_ERROR;
	}

	Set_CS_Pin(GPIO_PIN_RESET);
	command = READ_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command read bytes to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	else{
		if(SPI_Send(&addr, 3, 1000) != HAL_OK){
			printf("Error send read bytes addr\r\n");
			Set_CS_Pin(GPIO_PIN_SET);
			return MX_ERROR;
		} else{
			if(SPI_Receive(data, size, 1000) != HAL_OK){
				printf("Error receiving read bytes\r\n");
				Set_CS_Pin(GPIO_PIN_SET);
				return MX_ERROR;
			}
		}
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Write page to memory
* @param pData: Data to be written
* @param address: Starting write address
* @param size: Size to write (not bigger than 1 page (256 bytes))
* @retval Status
*/
MX_Err MX_Write_Page(uint8_t *pData, uint32_t address, uint32_t size){
	uint8_t command = 0;
	uint32_t addr = address;
	uint32_t current_size;

	if(address > (MX25R6435F_FLASH_SIZE / MX25R6435F_PAGE_SIZE)){
		printf("Invalid Page Addr: %ld\r\n", address);
		return MX_ERROR;
	}

	current_size = MX25R6435F_PAGE_SIZE - (address % MX25R6435F_PAGE_SIZE);

	if(size > current_size){
		printf("Not enough space left in page(free : %ld\r\n", current_size);
		return MX_ERROR;
	}

	while(!MX_Available()){
		printf("MX Busy\r\n");
		Delay_ms(10);
	}

	if(MX_Enable_Write() != MX_OK){
		printf("Error setting write");
		return MX_ERROR;
	}

	if(!MX_Write_Enabled()){
		printf("MX write not available\r\n");
		return MX_ERROR;
	}

	Set_CS_Pin(GPIO_PIN_RESET);
	command = PAGE_PROG_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending command write bytes to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	if(SPI_Send(&addr, 3, 1000) != HAL_OK){
		printf("Error sending write bytes addr to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	if(SPI_Send(pData, size, 1000) != HAL_OK){
		printf("Error sending write bytes to MX\r\n");
		Set_CS_Pin(GPIO_PIN_SET);
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Write bytes to memory
* @param pData: Data to be written
* @param address: Starting write address
* @param size: Size to write
* @retval Status
*/
MX_Err MX_Write_Bytes(uint8_t *pData, uint32_t address, uint32_t size){
	uint8_t command = 0;
	uint32_t current_size, current_addr, end_addr;

	if((address + size) > MX25R6435F_FLASH_SIZE){
		printf("Invalid Addr or too big: %ld\r\n", address);
		return MX_ERROR;
	}

	current_size = MX25R6435F_PAGE_SIZE - (address % MX25R6435F_PAGE_SIZE);

	if(current_size > size){
		current_size = size;
	}

	current_addr = address;
	end_addr = address + size;

	do{
		while(!MX_Available()){
			printf("MX Busy\r\n");
			Delay_ms(10);
		}

		if(MX_Enable_Write() != MX_OK){
			printf("Error setting write");
			return MX_ERROR;
		}

		if(!MX_Write_Enabled()){
			printf("MX write not available\r\n");
			return MX_ERROR;
		}

		Set_CS_Pin(GPIO_PIN_RESET);
		command = PAGE_PROG_CMD;
		if(SPI_Send(&command, 1, 1000) != HAL_OK){
			printf("Error sending command write bytes to MX\r\n");
			Set_CS_Pin(GPIO_PIN_SET);
			return MX_ERROR;
		}
		if(SPI_Send(&current_addr, 3, 1000) != HAL_OK){
			printf("Error sending write bytes addr to MX\r\n");
			Set_CS_Pin(GPIO_PIN_SET);
			return MX_ERROR;
		}
		if(SPI_Send(pData, current_size, 1000) != HAL_OK){
			printf("Error sending write bytes to MX\r\n");
			Set_CS_Pin(GPIO_PIN_SET);
			return MX_ERROR;
		}

		Set_CS_Pin(GPIO_PIN_SET);

		current_addr += current_size;
		pData += current_size;
		current_size = ((current_addr + MX25R6435F_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : MX25R6435F_PAGE_SIZE;
	} while(end_addr > current_addr);

	return MX_OK;
}

/**
* @brief Enter low power mode
* @param None
* @retval Status
*/
MX_Err MX_Enter_Deep_Power_Down(void){
	uint8_t command = 0;

	Set_CS_Pin(GPIO_PIN_RESET);
	command = DEEP_POWER_DOWN_CMD;
	if(SPI_Send(&command, 1, 1000) != HAL_OK){
		printf("Error sending enter deep power down to MX\r\n");
		return MX_ERROR;
	}
	Set_CS_Pin(GPIO_PIN_SET);

	return MX_OK;
}

/**
* @brief Exit low power mode
* @param None
* @retval None
*/
void MX_Exit_Deep_Power_Down(void){

	Set_CS_Pin(GPIO_PIN_RESET);
	Delay_ms(1);
	Set_CS_Pin(GPIO_PIN_SET);
	Delay_ms(1);

}

/**
* @brief Set CS pin
* @param None
* @retval None
*/
void Set_CS_Pin(GPIO_PinState State){
	HAL_GPIO_WritePin(GPIOA, CSMX_Pin, State);
	Delay_ms(1);
}

/**
* @brief Make a delay
* @param delay: Delay in milliseconds
* @retval None
*/
void Delay_ms(uint32_t delay){
	HAL_Delay(delay);
}

/**
* @brief Send data in SPI
* @param pData: Data to be sent
* @param size: Size to send
* @param timeout: Operation timeout
* @retval Status
*/
uint8_t SPI_Send(uint8_t *pData, uint16_t size, uint32_t timeout){
	return HAL_SPI_Transmit(&hspi1, pData, size, timeout);
}

/**
* @brief Receive data in SPI
* @param pData: Data received
* @param size: Size to be received
* @param timeout: Operation timeout
* @retval Status
*/
uint8_t SPI_Receive(uint8_t *pData, uint16_t size, uint32_t timeout){
	return HAL_SPI_Receive(&hspi1, pData, size, timeout);
}

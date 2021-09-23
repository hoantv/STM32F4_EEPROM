/*
 * eeprom.c
 *
 *  Created on: Sep 23, 2021
 *      Author: HoanTV
 */

#include "eeprom.h"
#include "stm32f4xx_hal.h"

uint32_t nextBlockAddress;
void EepromInit() {
	uint32_t flashAddress = EEPROM_START_ADDRESS;
	uint32_t sectorStatus = *(uint32_t*) flashAddress;
	if (sectorStatus == SECTOR_ERASE) {
		HAL_FLASH_Unlock();
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flashAddress, SECTOR_INUSE);
		HAL_FLASH_Lock();
	} else {
		while (nextBlockAddress < EEPROM_END_ADDRESS) {
			flashAddress += BLOCK_SIZE;
			if (*(uint32_t*) flashAddress == EMPTY_BLOCK) {
				nextBlockAddress = flashAddress;
				break;
			}
		}
	}
}
void EepromWrite(uint32_t virAdd, volatile void *wrBuf, uint32_t Nsize) {
	uint32_t flashAddress = nextBlockAddress;
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flashAddress, virAdd);
	flashAddress += 4;
	for (uint32_t i = 0; i < Nsize; i++) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, flashAddress,
				((uint8_t*) wrBuf)[i]);
		flashAddress++;
	}
	HAL_FLASH_Lock();
	nextBlockAddress += BLOCK_SIZE;
}

void EepromRead(uint32_t virAdd, volatile void *rdBuf) {
	uint32_t flashAddress = nextBlockAddress;
	while (flashAddress > EEPROM_START_ADDRESS + BLOCK_SIZE) {
		flashAddress -= BLOCK_SIZE;
		if (*(uint32_t*) flashAddress == virAdd) {
			flashAddress += 4;
			for (uint32_t i = 0; i < BLOCK_SIZE-4; i++) {
				*((uint8_t*) rdBuf + i) = *(uint8_t*) flashAddress;
				flashAddress++;
			}
			break;
		}
	}

}

void EepromEraseSector(uint8_t sectorID) {
	HAL_FLASH_Unlock();
	FLASH_Erase_Sector(sectorID, FLASH_VOLTAGE_RANGE_3);
	HAL_FLASH_Lock();
}

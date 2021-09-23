/*
 * eeprom.h
 *
 *  Created on: Sep 23, 2021
 *      Author: HoanTV
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_
#include <stdint.h>

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define SECTOR_SIZE					(uint32_t)0x20000
#define BLOCK_SIZE 256
#define EMPTY_BLOCK  0xFFFFFFFF
#define EEPROM_START_ADDRESS		ADDR_FLASH_SECTOR_6
#define EEPROM_END_ADDRESS			EEPROM_START_ADDRESS+SECTOR_SIZE -BLOCK_SIZE

//============= sector stauts==================
#define SECTOR_ERASE  0xFFFFFFFF
#define SECTOR_INUSE  0x00000000

void EepromInit();
void EepromWrite(uint32_t virAdd, volatile void *wrBuf, uint32_t Nsize);
void EepromRead(uint32_t virAdd, volatile void *rdBuf);
void EepromEraseSector(uint8_t sectorID);

#endif /* INC_EEPROM_H_ */

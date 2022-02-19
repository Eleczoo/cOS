/**
 * @file fat32.c
 * @brief FAT32 LIB
 * @version 0.1
 * @date 13-02-2022
 */

#include "fat32.h"
#include "../ata/ata.h"
#include "../../../stdlibs/string.h"
#include "../../../stdlibs/stdlib.h"
#include "../../screen/print/print.h"

/**
 * @brief Change the endiannes of a value (16 bits)
 * @param uin16_t The value to modify
 */
void swap_endian_int(uint16_t *val)
{
	*val = (*val << 8) | (*val >> 8);
}

/**
 * @brief Change the endiannes of a value (32 bits)
 * @param uin32_t The value to modify
 */
void swap_endian_long(uint32_t *val)
{
	*val = (*val << 24) | ((*val << 8) & 0x00ff0000) | ((*val >> 8) & 0x0000ff00) | (*val >> 24);
}

/**
 * @brief Parse the boot sector and stores the most important
 * informations inside a BootSector struct
 * 
 * @return BootSector information
 */
BootSector fat32_parse_bootsector()
{
	BootSector bs;

	bs.BytsPerSec 	= ata_read_word(0, BYTSPERSEC_OFFSET);
	bs.SecPerClus 	= ata_read_byte(0, SECPERCLUS_OFFSET);
	bs.RsvdSecCnt 	= ata_read_word(0, RSVDSECCNT_OFFSET);
	bs.NumFATs 		= ata_read_byte(0, NUMFATS_OFFSET);
	bs.FATSz32 		= ata_read_dword(0, FATSz32_OFFSET);
	bs.RootClus 	= ata_read_dword(0, ROOTCLUS_OFFSET);

	bs.RootDirSector = bs.RsvdSecCnt + (bs.NumFATs * bs.FATSz32);

	return bs;
}

/**
 * @brief Parse a file entry and return a struct with the infos
 * @param uint8_t* Pointer to the sector of the disk where the entry is
 * @param uint16_t offset of the entry from the begining of the sector (must be multiple of 32)
 * @return BootSector information
 */
FileEntry fat32_parse_fileentry(uint8_t *sector, uint16_t offset)
{
	FileEntry tmpEntry;

	PARSE_INFO_CHAR(tmpEntry, Name,         sector, NAME_OFFSET + offset)
	PARSE_INFO_CHAR(tmpEntry, Attr, sector, ATTR_OFFSET + offset)
	PARSE_INFO_CHAR(tmpEntry, CrtTimeTenth, sector, CRTTIMETENTH_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, CrtTime,      sector, CRTTIME_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, CrtDate,      sector, CRTDATE_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, LstAccDate,   sector, LSTACCDATE_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, FstClusHi,    sector, FSTCLUSHI_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, WrtTime,      sector, WRTTIME_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, WrtDate,      sector, WRTDATE_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, FstClusLO,    sector, FSTCLUSLO_OFFSET + offset)
	PARSE_INFO_LONG(tmpEntry, fileSize,     sector, FILESIZE_OFFSET + offset)

	return tmpEntry;
}
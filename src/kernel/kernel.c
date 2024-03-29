/**
 * @file kernel.c
 * @brief KERNEL entry point
 * @version 0.1
 * @date 02-02-2022
 */

// ! ---------------- INCLUDES  -----------------
#include "drivers/disk/ata/ata.h"
#include "drivers/disk/fat32/fat32.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"
#include "drivers/timer/timer.h"
#include "interrupts/interrupts.h"
#include "stdlibs/stdlib.h"
#include "stdlibs/string.h"

#include <stdint.h>

// ! ----------------- DEFINES ------------------
#define DISPLAY_LOGO 0

// ! --------------- PROTOTYPES  ----------------
void init_kernel();

extern int main()
{
	init_kernel();

	pong_run();

	// BootSector_t bs = fat32_parse_bootsector();
	//  FileList_t file_list = fat32_list_files(bs);

	// for (int i = 0; i < file_list.size; i++)
	// {
	// 	k_print(file_list.list[i].clean_name);
	// 	k_print("\n");
	// }

	// file_list = fat32_list_files(bs);

	// for (int i = 0; i < file_list.size; i++)
	// {
	// 	k_print(file_list.list[i].clean_name);
	// 	k_print("\n");
	// }

	// FilePointer_t fp = fat32_openfile(bs, "test10.txt");
	// fp				 = fat32_openfile(bs, "test08.txt");

	return 0;
}

void init_kernel()
{
	// ! HERE, PUT EVERYTHING THAT NEEDS TO BE DONE TO SETUP THE KERNEL
	init_malloc();

	// idt setup
	init_idt();
	// Disable ALL Interrupts
	port_byte_out(0x21, 0xFF);
	// Enable keyboard interupts
	init_keyboard();
	// Init timer and enable timer interrupt
	init_timer(20);
	// Enable interrupts
	asm volatile("sti");

#if DISPLAY_LOGO == 1
	k_print("            /$$$$$$   /$$$$$$		\n"
			"           /$$__  $$ /$$__  $$		\n"
			"  /$$$$$$$| $$  \\ $$| $$  \\__/	\n"
			" /$$_____/| $$  | $$|  $$$$$$ 		\n"
			"| $$      | $$  | $$ \\____  $$	\n"
			"| $$      | $$  | $$ /$$  \\ $$	\n"
			"|  $$$$$$$|  $$$$$$/|  $$$$$$/		\n"
			" \\_______/ \\______/  \\______/	\n");

#endif
}
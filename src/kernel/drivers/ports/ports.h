/**
 * @file ports.h
 * @brief PORT IN AND OUT COMMUNICATION 
 * @version 0.1
 * @date 02-02-2022
 * Source : https://github.com/dhavalhirdhav/LearnOS/blob/master/drivers/ports.h
 */

#ifndef __PORTS_H__
#define __PORTS_H__

#include <stdint.h>

uint8_t port_byte_in (uint16_t port);
void port_byte_out (uint16_t port, uint8_t data);

uint16_t port_word_in (uint16_t port);
void port_word_out (uint16_t port, uint16_t data);

uint32_t port_long_in(uint32_t port);
void port_long_out(uint32_t port, uint32_t value);

#endif
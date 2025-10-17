#ifndef __DS1307_H
#define __DS1307_H
#include "stdint.h"

uint8_t bcd_to_dec(uint8_t bcd);
uint8_t dec_to_bcd(uint8_t dec);
void DS1307_SET_TIME(uint8_t hour, uint8_t min, uint8_t sec);
void DS1307_GET_TIME(uint8_t *hour, uint8_t *min, uint8_t *sec);

#endif
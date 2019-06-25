/*
 * MAX7219.c
 *
 * Created: 2018-03-21 오후 2:03:12
 *  Author: kiki
 */ 

#include "MAX7219.h"

extern SPI_HandleTypeDef hspi1;

static void MAX7219_Select(void);
static void MAX7219_Deselect(void);
static void MAX7219_Tx(uint8_t data);

void MAX7219_Init()
{
	/* Deselect SS */
	MAX7219_Deselect();
}

static void MAX7219_Select()
{	
	MAX7219_CS_PORT &= ~MAX7219_CS_PIN;
}

static void MAX7219_Deselect()
{
	MAX7219_CS_PORT |= MAX7219_CS_PIN;
}

static void MAX7219_Tx(uint8_t data)
{
	uint8_t rxdata;
	HAL_SPI_TransmitReceive(&hspi1, &data, &rxdata, 1, 0xffffffff);
}

void MAX7219_Write(uint8_t index, uint8_t reg, uint8_t data)
{
	if(index >= MAX7219_IC_NUM) return;
	
	MAX7219_Select();
	
	/* NOOP to following ic */
	for(int i = index; i < MAX7219_IC_NUM-1; i++)
	{
		MAX7219_Tx(MAX7219_REG_NOOP);
		MAX7219_Tx(MAX7219_REG_NOOP);
	}	
	
	/* Write register */
	MAX7219_Tx(reg);
	MAX7219_Tx(data);
	
	/* NOOP to previous ic */
	for(int i = 0; i < index; i++)
	{
		MAX7219_Tx(MAX7219_REG_NOOP);
		MAX7219_Tx(MAX7219_REG_NOOP);
	}
	
	MAX7219_Deselect();	
}

void MAX7219_Digit(uint8_t index, uint8_t digit, int8_t value)
{
	if(index >= MAX7219_IC_NUM) return;
	if(digit > 0x07) return;
	
	MAX7219_Write(index, digit+1, value);
}

void MAX7219_Decode(uint8_t index, uint8_t value)
{
	if(index >= MAX7219_IC_NUM) return;
	
	MAX7219_Write(index, MAX7219_REG_DECODE, value);
}

void MAX7219_Intensity(uint8_t index, uint8_t value)
{
	if(index >= MAX7219_IC_NUM) return;
	if(value > 0x0F) value = 0x0F;
	
	MAX7219_Write(index, MAX7219_REG_INTENSITY, value);
}

void MAX7219_ScanLimit(uint8_t index, uint8_t value)
{
	if(index >= MAX7219_IC_NUM) return;
	if(value > 0x07) value = 0x07;
	
	MAX7219_Write(index, MAX7219_REG_SCANLIMIT, value);
}

void MAX7219_ShutDown(uint8_t index, uint8_t value)
{
	if(index >= MAX7219_IC_NUM) return;
	if(value > 0x01) value = 0x01;
	
	MAX7219_Write(index, MAX7219_REG_SHUTDOWN, value);	
}

void MAX7219_Test(uint8_t index, uint8_t value)
{
	if(index >= MAX7219_IC_NUM) return;
	if(value > 0x01) value = 0x01;
	
	MAX7219_Write(index, MAX7219_REG_TEST, value);
}

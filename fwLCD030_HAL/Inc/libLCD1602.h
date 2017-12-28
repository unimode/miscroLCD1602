/*
 * libLCD1602.h
 *
 *  Created on: Jun 13, 2017
 *      Author: romanp
 */

#ifndef __LIBLCD1602_H__
#define __LIBLCD1602_H__

void SendByte(char ByteToSend, int IsData);
void Cursor(char Row, char Col);
void ClearLCDScreen(void);
void InitializeLCD(void);
void PrintStr(char *Text);

#endif

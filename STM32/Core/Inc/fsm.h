/*
 * fsm.h
 *
 *  Created on: Dec 10, 2023
 *      Author: dell
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "string.h"
#include "stdio.h"
#include "software_timer.h"

#define MAX_BUFFER_SIZE  30

#define INIT 			0
#define CHECK			1
#define PROCESS_COMMAND	2
#define WAIT			3
#define RESPONE			4
#define REPEAT			5

UART_HandleTypeDef huart2;

uint8_t temp;
uint8_t buffer_flag;

extern int command_flag;

extern int command_status;
extern int uart_status;

void command_parser_fsm();
void uart_communication_fsm();


#endif /* INC_FSM_H_ */

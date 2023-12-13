/*
 * fsm.c
 *
 *  Created on: Dec 10, 2023
 *      Author: dell
 */


#include "fsm.h"

uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;

uint32_t ADC_value;

uint8_t buffer_flag = 0;

int command_flag;

int command_status = CHECK;
int uart_status = WAIT;

char* get_command(){
	return (char*) buffer;
}
void clear_buffer(){
	for (int i = 0; i < MAX_BUFFER_SIZE; i++){
		buffer[i] = '\0';
	}
	index_buffer = 0;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		buffer[index_buffer++] = temp;
		if (index_buffer >= MAX_BUFFER_SIZE) index_buffer = 0;
		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}
void command_parser_fsm(){
	switch (command_status) {
		case INIT:
			clear_buffer();
			command_status = CHECK;
			break;
		case CHECK:
			if (temp == '!'){
				command_status = PROCESS_COMMAND;
			}
			break;
		case PROCESS_COMMAND:
			if (temp == '#'){
				command_status = CHECK;
				uart_status = RESPONE;
			}
			if (index_buffer == 0){
				command_status = CHECK;
				clear_buffer();
			}
			break;
		default:
			break;
	}
}
void uart_communication_fsm(){
	switch (uart_status) {
		case WAIT:
			break;
		case RESPONE:
			if (strcmp(get_command(), "!RST#") == 0){
				command_flag = 1;
				uart_status = REPEAT;
				setTimer1(3000);
			}
			else {
				uart_status = WAIT;
			}
			clear_buffer();
			break;
		case REPEAT:
			if (timer1_flag == 1){
				command_flag = 1;
				setTimer1(3000);
			}
			if (strcmp(get_command(), "!OK#") == 0){
				uart_status = WAIT;
			}
			break;
		default:
			break;
	}
}

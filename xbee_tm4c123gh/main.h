/*
 * main.h
 *
 *  Created on: 26 Tem 2020
 *      Author: Celil SÝNCANLI
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/debug.h"
#include "driverlib/timer.h"

#define SYSCTL_PERIPH_MAIN_UART SYSCTL_PERIPH_UART0
#define MAIN_UART_INT           INT_UART0
#define MAIN_UART_BASE          UART0_BASE
#define MAIN_UART_RX            GPIO_PA0_U0RX
#define MAIN_UART_TX            GPIO_PA1_U0TX
#define MAIN_UART_PORT          GPIO_PORTA_BASE
#define MAIN_UART_RX_PIN        GPIO_PIN_0
#define MAIN_UART_TX_PIN        GPIO_PIN_1


void main_uart_init(bool);
void interrupt_Main_uart(void);
void on_load(char *message);


bool uart_flag = false;
bool break_flag = false;


char buffer_main[100];
int  uart_counter_main;

int  steer_degree = 74;
int  speed = 1;

#endif /* MAIN_H_ */

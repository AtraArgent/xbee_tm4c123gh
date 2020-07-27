

/**
 * main.c
 */
#include "main.h"
int main(void)
{
    main_uart_init(uart_flag == true);
}

void main_uart_init(bool flag)
{
    if(flag == true)
    {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_MAIN_UART);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    IntDisable(MAIN_UART_INT);
    UARTDisable(MAIN_UART_BASE);

    GPIOPinConfigure(MAIN_UART_RX);
    GPIOPinConfigure(MAIN_UART_TX);
    GPIOPinTypeUART(MAIN_UART_PORT, MAIN_UART_RX_PIN | MAIN_UART_TX_PIN);

    UARTClockSourceSet(MAIN_UART_BASE, UART_CLOCK_PIOSC);
    UARTConfigSetExpClk(
            MAIN_UART_BASE, SysCtlClockGet(), 115200,
            UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTFIFODisable(MAIN_UART_BASE);
    UARTIntEnable(MAIN_UART_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntRegister(MAIN_UART_BASE, interrupt_Main_uart);

    UARTEnable(MAIN_UART_BASE);
    IntEnable(MAIN_UART_INT);
    }
    else{
        IntDisable(MAIN_UART_INT);
        UARTDisable(MAIN_UART_BASE);
    }

}

void interrupt_Main_uart(void)
{
    uint32_t IntStatus;

    IntStatus = UARTIntStatus(MAIN_UART_BASE, true);
    UARTIntClear(MAIN_UART_BASE, IntStatus);

    buffer_main[uart_counter_main++] = UARTCharGetNonBlocking(MAIN_UART_BASE);;
    if (sizeof(buffer_main) == sizeof(char) * 6 && buffer_main[0] == '*')
    {
        on_load(buffer_main);
        uart_counter_main = 0;
    }
}
void on_load(char *message)
{
    steer_degree = atoi((char*) message[1]) * 10 + atoi((char*) message[2]);
    if (message[3] == '1')
    {
        break_flag = true;
    }
    else
    {
        break_flag = false;
    }
    speed = atoi((char*) message[4]) * 10 + atoi((char*) message[5]);
}

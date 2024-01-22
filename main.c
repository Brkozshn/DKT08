#include <msp430.h>
#include "submain.h"

/*
 * main.c
 */
int main(void)
{

    initHardware();
    initSoftware();


    taskManager();

}

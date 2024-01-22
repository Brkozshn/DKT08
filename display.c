/******************** (C) COPYRIGHT 2022 ORION EE ********************************
* File Name          : display.c
* Author             : ONUR KAYIKCI
* Version            : V1.0
* Date               : 22/09/2022
* Description        : display algorithms
********************************************************************************/
#include <msp430.h>
#include "main.h"
#include "cnc.h"
#include "timeout.h"
#include "ram.h"
#include "button.h"
#include "lcd.h"
#include "telemetry.h"
#include "display.h"
#include "submain.h"
#include <stdbool.h>
#include "DS1302.h"
//#include "modbus.h"


char empty_row[16] = {"                "};


void checkDayValidation()
{
    switch (system_status.temp_system_month)
    {
    case JAN:
    case MAR:
    case MAY:
    case JUL:
    case AUG:
    case OCT:
    case DEC:
        if(system_status.temp_system_day > 31)
        {
            system_status.temp_system_day = 1;
        }
        break;
    case APR:
    case JUN:
    case SEP:
    case NOV:
        if(system_status.temp_system_day > 30)
        {
            system_status.temp_system_day = 1;
        }
        break;
    case FEB:
        if(system_status.temp_system_year % 4 == 0)
        {
            if(system_status.temp_system_day > 29)
            {
            system_status.temp_system_day = 1;

            }
        }
        else
        {
            if(system_status.temp_system_day > 28)
            {
            system_status.temp_system_day = 1;
            }
        }
        break;
    }

    if(system_status.temp_system_day == 0)
    {
    switch (system_status.temp_system_month)
        {
        case JAN:
        case MAR:
        case MAY:
        case JUL:
        case AUG:
        case OCT:
        case DEC:
                system_status.temp_system_day = 31;
            break;
        case APR:
        case JUN:
        case SEP:
        case NOV:
                system_status.temp_system_day = 30;
            break;
        case FEB:
            if(system_status.temp_system_year % 4 == 0)
            {
                system_status.temp_system_day = 29;
            }
            else
            {
                system_status.temp_system_day = 28;
            }

            break;
        }
    }
}

void checkMonthValidation()
{
    switch (system_status.temp_system_month)
    {
    case JAN:
    case MAR:
    case MAY:
    case JUL:
    case AUG:
    case OCT:
    case DEC:
        if(system_status.temp_system_day > 31)
        {
            system_status.temp_system_day = 31;
        }
        break;
    case APR:
    case JUN:
    case SEP:
    case NOV:
        if(system_status.temp_system_day > 30)
        {
            system_status.temp_system_day = 30;
        }
        break;
    case FEB:
        if(system_status.temp_system_year % 4 == 0)
        {
            if(system_status.temp_system_day > 29)
            {
            system_status.temp_system_day = 29;

            }
        }
        else
        {
            if(system_status.temp_system_day > 28)
            {
            system_status.temp_system_day = 28;
            }
        }
        break;
    }
}

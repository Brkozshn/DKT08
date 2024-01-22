/*
 * utilities.c
 *
 *  Created on: 17 Tem 2019
 *      Author: P50
 */
#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "ram.h"
#include <string.h>
#include "utilities.h"


#define MAX_INT_DIGIT_CNT 10
#define MAX_FLT_DIGIT_CNT 2
#define ZERO_ASCII_BASE	0x30

/*  Function 	: num2str
 *  Inputs		: -
 *	Return		: -
 *	Desc			: Convert given integer number into integer_str string
 */
u8 num2str(u32 number, char *integer_str) /* MAX_INT_DIGIT_CNT */
{
	u32 digit;  // float vs int sure hesaplama

	u8 i,j;

	u8 integer_digits[MAX_INT_DIGIT_CNT];
	char integer_tmp_str[MAX_INT_DIGIT_CNT];

	/* Get INTEGER STR */
	for(i= 0; i < MAX_INT_DIGIT_CNT; i++)
		{
			digit = number;
			/* Divide by 10'n*/
			for(j=0; j < i; j++)
			{
				digit = digit/10;
			}

			integer_digits[i] = (u8)(digit %10);
			integer_tmp_str[i]	  = integer_digits[i] + ZERO_ASCII_BASE;

			if ((digit == 0))
			{
				break;
			}
		}

	if ( i != 0)
	{
		i--;
	}
	/* Convert integer string */
	for( j = 0; j <= i; j++)
	{
		integer_str[j] = integer_tmp_str[i-j];
	}
	integer_str[j] = '\0';

	return TRUE;


}

/*  Function 	: num2str_flt
 *  Inputs		: -
 *	Return		: -
 *	Desc			: Convert given floating number's 'floating part' into float_str string
 */
u8 num2str_flt(float number, char *float_str) /* MAX_INT_DIGIT_CNT */
{
	u32 integer_part;
	float flt_part,float_int;
	u16 i;

	integer_part = (u32)number;
	flt_part 	 	 = number - integer_part;

	float_int = flt_part;
	for( i = 0; i <= MAX_FLT_DIGIT_CNT; i++)
	{
		float_int = float_int*10;
		float_str[i] = (u8)float_int%10 + ZERO_ASCII_BASE;
	}

	float_str[i] = '\0';

//	num2str((u32)float_int, float_str);

	return TRUE;
}

/*  Function 	: num2strf_int
 *  Inputs		: -
 *	Return		: -
 *	Desc			: Convert given floating number's 'integer part' into int_str string
 */
u8 num2strf_int(float number, char *int_str) /* MAX_INT_DIGIT_CNT */
{
	u32 integer_part;



	integer_part = (u32)number;

	/* Get int STR*/
	num2str(integer_part, int_str);

	return TRUE;
}

/*  Function 	: num2strf
 *  Inputs		: -
 *	Return		: -
 *	Desc			: Convert given floating number into number_str string
 */
u8 num2strf(float number, char *number_str) /* MAX_INT_DIGIT_CNT */
{
	u32 integer_part;
	float flt_part;

	char float_str[MAX_FLT_DIGIT_CNT];

	integer_part = (u32)number;
	flt_part 	 = number - integer_part;

	/* Get int STR*/
	num2str(integer_part, number_str);

	/* Add . Dot*/
	strcat(number_str, ".");

	/* Get FLT STR*/
	num2str_flt(flt_part, float_str);

	strcat(number_str, float_str);

	return TRUE;
}



NODE * CreateNode(NODE * previous,char* str){
    NODE * node;
    //Yeni düðüm için bellekten yer ayrýlýyor.
    node=(NODE *)malloc(sizeof(NODE));
    if(node){
        //Yeni düðüme veri kaydediliyor.
        node->str=str;
        //NULL anlamý sonrasýnda düðüm olmadýðýdýr.
        node->next=NULL;
        //Bir önceki düðümün adresi yeni oluþturulan
        //düðümün bir önceki düðüm adresine kaydediliyor.
        if(previous){
            node->previous=previous;
            previous->next=node;
        }else{
            //root ise önceki düðümü yok.
            node->previous=NULL;
            node->previous->previous=NULL;
        }
    }
    return node;
}


NODE_FOR_CONFIG * CreateNode_For_Config(NODE_FOR_CONFIG * previous,char* str, u16 min_value, u16 max_value, u16 rate_value){
    NODE_FOR_CONFIG * node;
    //Yeni düðüm için bellekten yer ayrýlýyor.
    node=(NODE_FOR_CONFIG *)malloc(sizeof(NODE_FOR_CONFIG));
    if(node){
        //Yeni düðüme veri kaydediliyor.
        node->str = str;
        node->min_value = min_value;
        node->max_value = max_value;
        node->rate_value = rate_value;

        //ilk node oluþtururken node içindeki deðeri min'e eþitledik
        node->node_value = min_value;

        //NULL anlamý sonrasýnda düðüm olmadýðýdýr.
        node->next=NULL;
        //Bir önceki düðümün adresi yeni oluþturulan
        //düðümün bir önceki düðüm adresine kaydediliyor.
        if(previous){
            node->previous=previous;
            previous->next=node;
        }else{
            //root ise önceki düðümü yok.
            node->previous=NULL;
            node->previous->previous=NULL;
        }
    }
    return node;
}







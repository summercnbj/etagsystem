/*
 * cTools.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */
#include "itracker88Platform.h"
#include "cTools.h"



int stringlen(uint8* string)
{
	int string_length =0;
	if(string !=NULL)
	{
		string_length = strlen(string);
	}
	return string_length;
}



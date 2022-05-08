/*
 ============================================================================
 Name        : Ring_Buffer.c
 Author      : Madhavakumar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include "main.h"


int main(void)
{
	int stat = 1;

	demo_app_init();

	while(1)
	{
		stat = demo_app_task();

		if(stat == EXIT_SUCCESS)
		{
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

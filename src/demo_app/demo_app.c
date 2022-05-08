/*
 * demo_app.c
 *
 *  Created on: 30-Apr-2022
 *      Author: Madhavakumar
 */


#include "demo_app.h"
#include "ring_buffer.h"



#define BUFFER_SIZE				7
#define NORMAL					1


ring_buffer_t g_circular_buffer;
unsigned char g_array[BUFFER_SIZE];



void demo_app_init()
{
	memset(&g_circular_buffer,0,sizeof(g_circular_buffer));
	ring_buffer_initialize(&g_circular_buffer, g_array, BUFFER_SIZE);
}


int demo_app_task()
{
	static char elements[BUFFER_SIZE]={0};   // Since BUFFER_SIZE will be the maximum amount of elements that can be read/writen.
	int operation_no, status, element_count, count_successful;
	//static char elements;
	//static int operation_no, status, element_count;

	system("cls");

	printf("------------------\n");
	printf("Simple ring buffer\n");
	printf("------------------\n");

	ring_buffer_display_buffer(&g_circular_buffer);
	ring_buffer_display_operations_list();

	fflush(stdin);     // to flush the '\n' character given in the previous scanf
	printf("\nOperation number: ");
	scanf("%d", &operation_no);

	switch(operation_no)
	{
	case 0:    // Exit
		return EXIT_SUCCESS;
		break;
	case 1:    // Write
		fflush(stdin);     // to flush the '\n' character given in the previous scanf
		printf("\nEnter the no. of items to be writen: ");
		scanf("%d", &element_count);
		fflush(stdin);     // to flush the '\n' character given in the previous scanf
		printf("Enter the items that need to be writen: ");
		scanf("%s", elements);

		status = ring_buffer_write(&g_circular_buffer, element_count, elements, &count_successful);
		//status = ring_buffer_enqueue(&g_circular_buffer, elements);

		system("cls");
		printf("------------------\n");
		printf("Simple ring buffer\n");
		printf("------------------\n");
		ring_buffer_display_buffer(&g_circular_buffer);
		ring_buffer_display_operations_list();
		printf("\nOperation number: 1\n");
		printf("\nEnter the no. of items to be writen: %d\n", element_count);
		printf("Enter the items that need to be writen: %s\n\n", elements);

		printf("\nNo. of items writen: %d", count_successful);
		if(status == OVERFLOW)
		{
			printf("\nOVERFLOW !!");
		}
		fflush(stdin);
		getch();
		break;
	case 2:    // Read
		fflush(stdin);     // to flush the '\n' character given in the previous scanf
		printf("\nEnter the no. of items to be read: ");
		scanf("%d", &element_count);
		//printf("%c\n", element);

		status = ring_buffer_read(&g_circular_buffer, element_count, elements, &count_successful);
		//status = ring_buffer_dequeue(&g_circular_buffer, &elements);

		system("cls");
		printf("------------------\n");
		printf("Simple ring buffer\n");
		printf("------------------\n");
		ring_buffer_display_buffer(&g_circular_buffer);
		ring_buffer_display_operations_list();
		printf("\nOperation number: 2\n");
		printf("\nEnter the no. of items to be read: %d\n\n", element_count);
		printf("No. of items read: %d\n", count_successful);
		for(int i = 0; i < count_successful; i++)
		{
			printf("%c ", elements[i]);
		}
		if(status == UNDERFLOW)
		{
			printf("\nUNDERFLOW !!");
		}
		fflush(stdin);
		getch();
		break;
	default:    // Invalid
		printf("INVALID OPERATION NUMBER!\n");
		fflush(stdin);
		getch();
	}
	return NORMAL;
}



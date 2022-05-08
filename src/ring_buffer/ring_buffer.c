/*
 * ring_buffer.c
 *
 *  Created on: 06-Apr-2022
 *      Author: Madhavakumar
 */

// no file header - not good

#include "ring_buffer.h"




static int ring_buffer_enqueue(ring_buffer_t *circular_queue_ptr, char item);
static int ring_buffer_dequeue(ring_buffer_t *circular_queue_ptr, char *item);






void ring_buffer_initialize(ring_buffer_t *circular_queue_ptr, unsigned char *buff_array, int buffer_size)
{
	for(int j = 0; j < buffer_size; j++)
	{
		buff_array[j] = '_';
	}

	circular_queue_ptr->buffer = buff_array;

	circular_queue_ptr->front = 0;
	circular_queue_ptr->rear = 0;
	circular_queue_ptr->size = buffer_size;
	circular_queue_ptr->values_stored_count = 0;
}


void ring_buffer_display_buffer(ring_buffer_t *circular_queue_ptr)
{
	printf("\n\n");
	for(int i = 0; i < (circular_queue_ptr->size); i++)
	{
		printf("%c  ", circular_queue_ptr->buffer[i]);
	}
	printf("\n");
	for(int j = 0; j < circular_queue_ptr->size; j++)
	{
		if(j == circular_queue_ptr->front)
		{
			if(j == circular_queue_ptr->rear)
			{
				printf("fr ");
			}
			else
			{
				printf("f  ");
			}
		}
		else if(j == circular_queue_ptr->rear)
		{
			printf("r  ");
		}
		else
		{
			printf("   ");
		}
	}
	printf("\n\n\n");
}


void ring_buffer_display_operations_list()
{
	printf("Operations\n");
	printf("----------\n");
	printf("0) Exit\n");
	printf("1) Write\n");
	printf("2) Read\n");
}


static int ring_buffer_enqueue(ring_buffer_t *circular_queue_ptr, char item)
{
	if(circular_queue_ptr->values_stored_count == circular_queue_ptr->size)
	{
		return OVERFLOW;
	}

	if(circular_queue_ptr->values_stored_count != 0)
	{
		if(circular_queue_ptr->rear == (circular_queue_ptr->size - 1))
		{
			circular_queue_ptr->rear = 0;
		}
		else
		{
			circular_queue_ptr->rear++;
		}
	}
	circular_queue_ptr->buffer[circular_queue_ptr->rear] = item;
	circular_queue_ptr->values_stored_count++;
	return SUCCESSFUL;
}


/*
// function header
int ring_buffer_enqueue2(ring_buffer_t *pcircular_queue, char item)
{
	// check overflow condition
	if(pcircular_queue->count == pcircular_queue->size)
	{
		return OVERFLOW;
	}

	// write the value into current write index
	pcircular_queue->buffer[pcircular_queue->rear] = item;
	pcircular_queue->count++;

	// update rear index
	pcircular_queue->rear++;
	if(pcircular_queue->rear >= pcircular_queue->size)
	{
		pcircular_queue->rear=0;
	}

	return SUCCESSFUL;
}
*/


static int ring_buffer_dequeue(ring_buffer_t *circular_queue_ptr, char *item)
{
	if(circular_queue_ptr->values_stored_count == 0)
	{
		return UNDERFLOW;
	}
	*item = circular_queue_ptr->buffer[circular_queue_ptr->front];
	circular_queue_ptr->buffer[circular_queue_ptr->front] = '_';
	circular_queue_ptr->values_stored_count--;
	if(circular_queue_ptr->values_stored_count != 0)
	{
		//
		if(circular_queue_ptr->front == (circular_queue_ptr->size - 1))
		{
			circular_queue_ptr->front = 0;
		}
		else
		{
			circular_queue_ptr->front++;
		}
	}
	return SUCCESSFUL;
}


int ring_buffer_read(ring_buffer_t *buffer_ptr, int read_count, char *elements, int *count_successful)
{
	int write_index = 0;
	char read_element = '\0';
	//int ind;
	int stat = 0;

	for(write_index = 0; write_index < read_count; write_index++)
	{
		stat = ring_buffer_dequeue(buffer_ptr, &read_element);
		if(stat == UNDERFLOW)
		{
			*count_successful = write_index;
			return UNDERFLOW;
		}
		else
		{
			elements[write_index] = read_element;
		}
	}
	*count_successful = write_index;
	return SUCCESSFUL;
}


int ring_buffer_write(ring_buffer_t *buffer_ptr, int write_count, char *elements, int *count_successful)
{
	int read_index = 0;
	int stat = 0;

	for(read_index = 0; read_index < write_count; read_index++)
	{
		stat = ring_buffer_enqueue(buffer_ptr, elements[read_index]);
		if(stat == OVERFLOW)
		{
			*count_successful = read_index;
			return OVERFLOW;
		}
	}
	*count_successful = read_index;
	return SUCCESSFUL;
}


// ________________________ END ___________________________

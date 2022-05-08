/*
 * ring_buffer.h
 *
 *  Created on: 06-Apr-2022
 *      Author: Madhavakumar
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stdio.h>

#define	SUCCESSFUL		0
#define	UNDERFLOW		1
#define	OVERFLOW		2


typedef struct
{
	unsigned char	*buffer;
	int 	front;
	int		rear;
	int		size;
	int		values_stored_count;
	//int     count;
} ring_buffer_t;


void ring_buffer_initialize(ring_buffer_t *circular_queue_ptr, unsigned char *buff_array, int buffer_size);
void ring_buffer_display_buffer(ring_buffer_t *circular_queue_ptr);
void ring_buffer_display_operations_list(); // lengthy name is bad, display menu is good
//
int ring_buffer_read(ring_buffer_t *buffer_ptr, int read_count, char *elements, int *count_successful);
int ring_buffer_write(ring_buffer_t *buffer_ptr, int write_count, char *elements, int *count_successful);


#endif /* RING_BUFFER_H_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:23:01 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/18 15:58:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

//TODO maybe use a macro an
t_circular_queue	*circular_queue_create(size_t size, size_t elem_size)
{
	t_circular_queue	*queue;

	queue = malloc(sizeof(t_circular_queue));
	if (queue == NULL)
		return (NULL);
	queue->size = size;
	queue->start = 0;
	queue->end = 0;
	queue->elem_size = elem_size;
	queue->buffer = calloc(size, elem_size);
	if (queue->buffer == NULL)
	{
		free(queue);
		return (NULL);
	}
	return (queue);
}

void	circular_queue_destroy(t_circular_queue *queue)
{
	if (queue != NULL)
	{
		free(queue->buffer);
		free(queue);
	}
}

int	circular_queue_add(t_circular_queue *queue, void *element)
{
	size_t	index;

	index = (queue->end + 1) % queue->size;
	printf("circular_queue_add: %zu %zu %zu %zu %zu\n", index, queue->start, queue->end, queue->size, queue->elem_size);
	if (index == queue->start)
	{
		printf("circular_queue_add: buffer full : %zu %zu %zu %zu\n", index, queue->start, queue->end, queue->size);
		return (1);
	}
	memcpy(queue->buffer + (queue->end * queue->elem_size), element, queue->elem_size);
	queue->end = index;
	return (0);
}

int	circular_queue_pop(t_circular_queue *queue, void *result)
{
	void	*ptr;

	printf("circular_queue_pop: %zu %zu %zu\n", queue->start, queue->end, queue->size);
	if (queue->start == queue->end)
	{
		printf("circular_queue_pop: empty: %zu %zu %zu\n", queue->start, queue->end, queue->size);
		return (1);
	}
	ptr = queue->buffer + (queue->start * queue->elem_size);
	queue->start = (queue->start + 1) % queue->size;
	memcpy(result, ptr, queue->elem_size);
	// *result = *ptr;
	return	(0);
}

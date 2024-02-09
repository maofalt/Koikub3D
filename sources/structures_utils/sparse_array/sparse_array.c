/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 02:06:24 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"

t_sparse_array	*sparse_array_init(size_t elem_size, size_t capacity)
{
	t_sparse_array	*array;

	array = malloc(sizeof(t_sparse_array));
	if (array == NULL)
		return (NULL);
	array->elem_size = elem_size;
	array->size = 0;
	array->capacity = capacity;
	array->indices = malloc(capacity * sizeof(array->indices[0]));
	array->buffer = ft_calloc(capacity, elem_size);
	if (array->indices == NULL || array->buffer == NULL)
	{
		free(array->indices);
		free(array->buffer);
		free(array);
		return (NULL);
	}
	ft_memset(array->indices, -1, capacity * sizeof(array->indices[0]));
	return (array);
}

void	sparse_array_destroy(t_sparse_array *array)
{
	if (array == NULL)
		return ;
	free(array->indices);
	free(array->buffer);
	free(array);
}

void	*sparse_array_get(t_sparse_array *array, int index)
{
	int		index_in_buffer;

	if (index >= array->size || index < 0)
		return (NULL);
	index_in_buffer = array->indices[index];
	if (index_in_buffer == -1)
		return (NULL);
	return (array->buffer + index_in_buffer * array->elem_size);
}


int	sparse_array_growth(t_sparse_array *array)
{
	void	*new_buffer;
	int		*new_indices;
	size_t	new_capacity;

	new_capacity = array->capacity * 2;
	new_buffer = ft_calloc(new_capacity, array->elem_size);
	new_indices = malloc(new_capacity * sizeof(new_indices[0]));
	if (new_buffer == NULL || new_indices == NULL)
	{
		free(new_buffer);
		free(new_indices);
		return (1);
	}
	ft_memset(new_indices, -1, new_capacity * sizeof(new_indices[0]));
	ft_memcpy(new_buffer, array->buffer, array->size * array->elem_size);
	free(array->buffer);
	free(array->indices);
	array->buffer = new_buffer;
	array->indices = new_indices;
	array->capacity = new_capacity;
	return (0);
}

int	sparse_array_add(t_sparse_array *array, const void *elem)
{
	int		index;

	index = 0;
	if (array->size == array->capacity)
		if (sparse_array_growth(array))
			return (-1);
	while (array->indices[index] != -1)
		index++;
	array->indices[index] = array->size;
	ft_memcpy(array->buffer + array->size * array->elem_size, elem, array->elem_size);
	array->size++;
	return (index);
}

int	sparse_array_add_fast(t_sparse_array *array, const void *elem)
{
	if (array->size == array->capacity)
		if (sparse_array_growth(array))
			return (-1);
	array->indices[array->size] = array->size;
	ft_memcpy(array->buffer + array->size * array->elem_size, elem, array->elem_size);
	array->size++;
	return (array->size - 1);
}

void	sparse_array_remove(t_sparse_array *array, int index)
{
	int		index_in_buffer;

	if (index >= array->size || index < 0)
		return ;
	index_in_buffer = array->indices[index];
	if (index_in_buffer == -1)
		return ;
	ft_memmove(array->buffer + index_in_buffer * array->elem_size,
		array->buffer + (index_in_buffer + 1) * array->elem_size,
		(array->size - index - 1) * array->elem_size);
	array->size--;
	while (index < array->size)
	{
		if (array->indices[index] > index_in_buffer)
			array->indices[index]--;
		index++;
	}
	array->indices[index] = -1;
}

void	sparse_array_remove_all(t_sparse_array *array)
{
	array->size = 0;
	ft_memset(array->indices, -1, array->capacity * sizeof(array->indices[0]));
}

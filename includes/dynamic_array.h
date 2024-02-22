/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:38:57 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 18:51:15 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

# include <stddef.h>

typedef struct s_dynamic_array
{
	void	*buffer;
	size_t	elem_size;
	size_t	size;
	size_t	capacity;
}			t_dynamic_array;

t_dynamic_array	*dynamic_array_init(size_t elem_size, size_t capacity);
void			dynamic_array_destroy(t_dynamic_array *array);
void			*dynamic_array_get(t_dynamic_array *array, size_t index);
void			*dynamic_array_growth(t_dynamic_array *array);
void			*dynamic_array_add(t_dynamic_array *array, void *element);
void			dynamic_array_remove(t_dynamic_array *array, size_t index);
void			*dynamic_array_new_element(t_dynamic_array *array);

#endif

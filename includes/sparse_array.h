/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:24:58 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 02:13:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPARSE_ARRAY_H
# define SPARSE_ARRAY_H

# include <stddef.h>

typedef struct s_sparse_array
{
	int			*indices;
	void		*buffer;
	size_t		elem_size;
	int			size;
	int			capacity;
}				t_sparse_array;

t_sparse_array	*sparse_array_init(size_t elem_size, size_t capacity);
void			sparse_array_destroy(t_sparse_array *array);
void			*sparse_array_get(t_sparse_array *array, int index);
int				sparse_array_growth(t_sparse_array *array);
int				sparse_array_add(t_sparse_array *array, const void *const elem);
int				sparse_array_add_fast(t_sparse_array *array,
					const void *const elem);
void			sparse_array_remove(t_sparse_array *array, int index);
void			sparse_array_remove_all(t_sparse_array *array);

#endif

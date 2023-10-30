/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_array_container.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:12:43 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/30 23:27:52 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_nodes(t_list **a, t_list **b)
{
	t_list	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_lst_node_array(t_list **arr, int size,
	int (*comparison_function)(t_list *, t_list *))
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (comparison_function(arr[j], arr[j + 1]) > 0)
				swap_nodes(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

// t_list	**sorted_lst_nodes_array(t_list *lst,
// 	int (*comparison_function)(t_list *, t_list *))
// {
// 	int		size;
// 	t_list	**arr;
// 	int		i;

// 	size = ft_lstsize(lst);
// 	arr = malloc(sizeof(t_list *) * size);
// 	if (!arr)
// 		return (NULL);
// 	i = 0;
// 	while (lst)
// 	{
// 		arr[i++] = lst;
// 		lst = lst->next;
// 	}
// 	sort_node_pointers(arr, size, comparison_function);
// 	return (arr);
// }

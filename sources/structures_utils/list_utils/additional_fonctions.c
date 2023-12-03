/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fonctions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 23:29:11 by olimarti          #+#    #+#             */
/*   Updated: 2023/12/03 23:47:34 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_utils.h"

void	lst_move_node(t_list **list, t_list **node)
{
	t_list	*next_tmp;

	next_tmp = (*node)->next;
	ft_lstadd_front(list, (*node));
	(*node) = next_tmp;
}

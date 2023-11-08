/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:27:10 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:44:33 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCTURES_UTILS_H
# define STRUCTURES_UTILS_H

# include	"structures.h"
# include	"libft.h"

//---LINKED LIST---

void		lst_move_node(t_list **list, t_list **node);

//---SEGMENTS---

t_tree_node	*create_tree_node(void);
void		destroy_tree_node(t_tree_node	*node);
void		destroy_tree(t_tree_node **tree, void (*del)(t_tree_node *));

t_list		*create_segment_node(void);
t_list		*create_initialized_segment_node(t_segment_d segment);
int			add_segment_to_lst(t_list **lst, t_segment_d segment);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fonctions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:24:57 by motero            #+#    #+#             */
/*   Updated: 2023/10/11 23:41:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_FONCTIONS_H
# define LIST_FONCTIONS_H

# include	"libft.h"
# include	"structures.h"

/*############################################################################*/
/*                           ADDITION LIST FONCTIONS                          */
/*############################################################################*/

t_list	*create_segment_node(void);
t_list	*create_initialized_segment_node(t_segment_d segment);
int		add_segment_to_lst(t_list **lst, t_segment_d segment);

#endif
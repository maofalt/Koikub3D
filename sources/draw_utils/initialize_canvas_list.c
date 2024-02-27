/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_canvas_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 01:05:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 01:07:06 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

t_list	*initialize_canvas_and_add_to_list(
	t_canvas_init_entry *entry,
	t_list **canvas_list)
{
	t_canvas	*canvas;
	t_list		*new_node;

	canvas = initialize_canvas(entry);
	if (!canvas)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (free_canvas(canvas), NULL);
	new_node->next = NULL;
	new_node->content = canvas;
	ft_lstadd_back(canvas_list, new_node);
	return (new_node);
}

void	free_canvas_list(t_list *canvas_list)
{
	t_list	*current_node;
	t_list	*next_node;

	current_node = canvas_list;
	while (current_node)
	{
		next_node = current_node->next;
		free_canvas((t_canvas *)current_node->content);
		free(current_node);
		current_node = next_node;
	}
	current_node = NULL;
}

t_canvas_init_entry	*get_canvas_init_table(t_modus_state state,
	t_setup_by_game_state *canvas_setups)
{
	size_t	i;

	i = 0;
	printf("state: %d\n", state);
	while (canvas_setups[i].game_state != END_GAME_STATE)
	{
		printf("canvas_setups[%zu].game_state: %d\n", i,
			canvas_setups[i].game_state);
		if (canvas_setups[i].game_state == state)
			return (canvas_setups[i].canvas_configurations);
		i++;
	}
	return (NULL);
}

t_list	*initialize_canvas_list(t_modus_state state,
	t_setup_by_game_state *canvas_setups)
{
	t_canvas_init_entry			*canvas_init_table;
	t_list						*canvas_list;
	t_list						*new_node;
	size_t						i;
	size_t						nbr_canvas;

	canvas_init_table = get_canvas_init_table(state, canvas_setups);
	if (!canvas_init_table)
		return (NULL);
	canvas_list = NULL;
	i = 0;
	nbr_canvas = get_init_table_size(canvas_init_table);
	while (i < nbr_canvas)
	{
		new_node = initialize_canvas_and_add_to_list(
				&canvas_init_table[i], &canvas_list);
		if (!new_node)
			return (free_canvas_list(canvas_list), NULL);
		i++;
	}
	return (canvas_list);
}

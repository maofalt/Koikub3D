/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 19:53:30 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

bool	g_interactive_canvas_types[END_MARKER]
	= {
[MAP] = true,
[UI] = true,
[BUTTON] = true,
[GAME] = true,
[FINAL] = false,
[FIN_TEMP] = false
};

bool	is_valid_canvas(t_canvas *canvas)
{
	return (g_interactive_canvas_types[canvas->type]);
}

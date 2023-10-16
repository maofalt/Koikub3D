/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 03:58:35 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 06:37:28 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENGINE_H
# define ENGINE_H

# include "structures.h"

void	player_handle_event(t_cub *data);
int		render(t_cub *data);

#endif

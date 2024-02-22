/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager_update.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:31:28 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/19 22:28:47 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ressources_managers.h"
#include "settings.h"
#include "structures.h"

//TODO: add delta time;
void	texture_manager_update(t_texture_manager *texture_manager)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		texture_update(texture_manager->textures + i, 16);
		++i;
	}
}

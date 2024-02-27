/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_physics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:29:54 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 22:30:04 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "game_loop.h"

static void	normalize_vector_3d(t_vector4d *vec)
{
	double	reverse_lenght;
	double	lenght;

	lenght = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (lenght == 0)
		return ;
	reverse_lenght = 1 / lenght;
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
	vec->vec[2] *= reverse_lenght;
}

static inline double	dot_product_3d(
	const t_vector4d *const vec1,
	const t_vector4d *const vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + +vec1->z * vec2->z);
}

static void	apply_collision_correction(
	t_entity *self,
	t_game_data *game_data,
	double dt)
{
	t_vector4d			sliding_vector;
	t_vector4d			new_pos;
	double				dot_product;
	t_collision_info	collision_info;
	int					i;

	i = 5;
	new_pos.vec = self->physics.pos.vec + self->physics.velocity.vec * dt;
	collision_info
		= check_collision_cylinder(new_pos, DEFAULT_PLAYER_RADIUS,
			DEFAULT_PLAYER_HEIGHT, &game_data->game_view_render);
	while (collision_info.collision && --i)
	{
		normalize_vector_3d(&collision_info.collision_normal);
		dot_product = dot_product_3d(&self->physics.velocity,
				&collision_info.collision_normal);
		sliding_vector.vec = self->physics.velocity.vec
			- 1.0 * dot_product * collision_info.collision_normal.vec;
		self->physics.velocity = sliding_vector;
		new_pos.vec = self->physics.pos.vec
			+ self->physics.velocity.vec * dt;
		collision_info
			= check_collision_cylinder(new_pos, DEFAULT_PLAYER_RADIUS,
				DEFAULT_PLAYER_HEIGHT, &game_data->game_view_render);
	}
}

void	apply_physics_entity(
	t_entity *entity,
	t_game_data *game_data,
	double dt)
{
	t_vector4d		new_pos;

	entity->physics.velocity.vec = entity->physics.velocity.vec
		+ entity->physics.acceleration.vec * dt;
	entity->physics.velocity.vec *= 1 - entity->physics.friction * dt;
	if (entity->physics.collision_model.type
		== COLLISION_MODEL_DYNAMIC_CYLINDER)
		apply_collision_correction(entity, game_data, dt);
	new_pos.vec = entity->physics.pos.vec + entity->physics.velocity.vec * dt;
	entity->physics.pos = new_pos;
}

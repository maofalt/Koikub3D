/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:03:06 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/13 02:05:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_LOOP_H
# define GAME_LOOP_H

# include "structures.h"

int					game_init(t_cub *data, t_canvas *canvas);
void				game_render(t_cub *data);
void				game_update(t_cub *data);
int					game_loop(void *self, t_cub *data);
void				game_post_process_frame(t_3d_render *render);

void				game_update_camera(t_game_data *data);

int					game_render_init(t_cub *data, t_game_data *game_data,
						t_canvas *canvas);
void				game_render_destroy(t_game_data *game_data);
void				game_destroy(t_game_data *data);

void				count_fps(void);

// Precomputation
void				game_precalculate_map(t_game_data *game_data);

void				compute_sector_center(t_bsp_tree_node_data *sector);
void				compute_sector_floor_ceiling(t_game_data *game_data,
						t_bsp_tree_node_data *sector);
void				compute_segment_normal(t_game_data *game_data,
						t_segment_d *segment);
void				compute_segment_orientation(__attribute_maybe_unused__ t_game_data *game_data,
						t_segment_d *segment, t_bsp_tree_node_data *sector);

void				compute_segment_size(__attribute_maybe_unused__ t_game_data *game_data,
						t_segment_d *segment);

void				compute_segment_oriented_textures(__attribute_maybe_unused__ t_game_data *game_data,
						t_segment_d *segment, t_bsp_tree_node_data *sector);
void				compute_segment_floor_ceil(
						__attribute_maybe_unused__ t_game_data *game_data,
						t_segment_d *segment,
						t_bsp_tree_node_data *sector);

// ENTITY
t_entity			*entity_default_spawn(t_game_data *game_data);
t_entity			*entity_player_spawn(t_game_data *game_data, t_spawn spawn);
t_entity			*entity_torch_spawn(t_game_data *game_data, t_spawn spawn);
t_entity			*entity_monster_spawn(t_game_data *game_data, t_spawn spawn);

void				entity_player_update_movements(t_entity *self,
						t_game_data *game_data);

void				entity_monster_update_movements(t_entity *self,
						t_game_data *game_data);

void				entity_torch_update(t_entity *self, t_game_data *game_data);

void				entities_update(t_game_data *game_data);
void				entities_draw(t_game_data *game_data);
void				entities_destroy_marked(t_game_data *game_data);
void				entities_destroy_all(t_game_data *game_data);

// COLLISION
bool				segment_circle_intersection(t_segment_d *segment,
						t_circle *circle);
t_collision_info	check_collision_cylinder(t_vector4d pos, double radius,
						double height, t_3d_render *render);

#endif

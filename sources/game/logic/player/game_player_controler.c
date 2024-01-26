/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_player_controler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 04:12:47 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/25 17:38:30 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "matrix.h"
#include "maths_utils.h"

// void player_handle_event(t_cub *data)
// {
// 	t_point2d translation;
// 	t_point2d forward;
// 	t_point2d right;
// 	t_matrix3x3 transformation;
// 	t_point2d new_translation;
// 	double angle_movement;
// 	double old_z;

// 	// Get the movement directions (still in world coordinates)
// 	translation.x = data->inputs.action_states[a_move_right] - data->inputs.action_states[a_move_left];
// 	translation.y = data->inputs.action_states[a_move_forward] - data->inputs.action_states[a_move_backward];

// 	translation.vec *= 0.2;
// 	// Get forward and right vectors from player's dir (assuming it's normalized)
// 	forward = vector4d_to_point2d(&game_data->state.player.dir);

// 	// Compute the right vector (perpendicular) from the forward vector
// 	right.x = -forward.y;
// 	right.y = forward.x;

// 	// Convert world coordinates translation to player's local coordinates
// 	new_translation.x = translation.x * right.x + translation.y * forward.x;
// 	new_translation.y = translation.x * right.y + translation.y * forward.y;
// 	translation = new_translation;

// 	// Apply the translation to the player's position
// 	transformation = translation_matrix(translation);
// 	translation = matrix_vector_multiply(transformation, vector4d_to_point2d(&game_data->state.player.pos));
// 	old_z = game_data->state.player.pos.z + 0.2 * (data->inputs.action_states[a_move_down] - data->inputs.action_states[a_move_up]);
// 	game_data->state.player.pos = point2d_to_vector4d(&translation);
// 	game_data->state.player.pos.z = old_z;
// 	// Handle the turning of the player
// 	angle_movement = 0.1 * (data->inputs.action_states[a_turn_right] - data->inputs.action_states[a_turn_left]);
// 	transformation = rotation_matrix(angle_movement);
// 	t_point2d rotated_dir = matrix_vector_multiply(transformation, vector4d_to_point2d(&game_data->state.player.dir));
// 	game_data->state.player.dir = point2d_to_vector4d(&rotated_dir);
// 	game_data->state.player.right = game_data->state.player.dir;
// 	game_data->state.player.right.x = -game_data->state.player.dir.y;
// 	game_data->state.player.right.y = game_data->state.player.dir.x;

// 	data->game_data.state.player_camera.dir = game_data->state.player.dir;
// 	data->game_data.state.player_camera.right = game_data->state.player.right;
// 	data->game_data.state.player_camera.pos = game_data->state.player.pos;

// }

#define PLAYER_RADIUS 0.5
#define PLAYER_HEIGHT 1.5

// TODO move this to a separate file
static double point_space_partitioning_v4d(t_segment_d *separator, t_vector4d *point)
{
	t_vector4d ab;
	t_vector4d ap;

	ab.vec = separator->point_b.vec - separator->point_a.vec;
	ap.vec = point->vec - separator->point_a.vec;
	return (ab.x * ap.y - ab.y * ap.x);
}

static t_tree_node *bsp_search_point_fast(t_tree_node *tree, t_vector4d *point)
{
	t_tree_node *child;
	// t_segment_d	separator;
	double point_side;

	if (!tree || !tree->left || !tree->right)
		return (tree);
	// separator = ;
	point_side = point_space_partitioning_v4d(&((t_bsp_tree_node_data *)tree->data)->separator, point);
	if (point_side > 0)
		child = bsp_search_point_fast(tree->right, point);
	else
		child = bsp_search_point_fast(tree->left, point);
	return (child);
}

static void normalize_vector_3d(t_vector4d *vec)
{
	t_vector4d	product;
	double 		reverse_lenght;

	product.vec = vec->vec;
	product.vec *= product.vec;
	reverse_lenght = 1 / sqrt(product.x + product.y + product.z);
	vec->vec *= reverse_lenght;
}

int check_ray_reach_dest(t_vector4d origin, t_vector4d dest, t_3d_render *render);

typedef struct s_collision_info
{
	bool collision;
	t_vector4d collision_normal;
} t_collision_info;

t_vector4d bsp_collision_normal(t_vector4d origin, t_vector4d dest, t_3d_render *render);

// bool lineSegmentCircleIntersection(LineSegment line, Circle circle) {
//     t_v4d lineVec = subtract(line.end, line.start);
//     t_v4d circleVec = subtract(circle.center, line.start);
//     float lineLengthSquared = dot(lineVec, lineVec);
//     float t = dot(circleVec, lineVec) / lineLengthSquared;
//     t = fmaxf(0, fminf(1, t)); // Clamping t
//     t_v4d closestPoint = {line.start.x + t * lineVec.x, line.start.y + t * lineVec.y, 0, 0};
//     t_v4d distVec = subtract(circle.center, closestPoint);
//     return dot(distVec, distVec) <= circle.radius * circle.radius;
// }

static double dot_product_3d(t_vector4d *vec1, t_vector4d *vec2)
{
	// double result = vec1->x * vec2->x + vec1->y * vec2->y;
	double result = vec1->x * vec2->x + vec1->y * vec2->y + +vec1->z * vec2->z;
	return result;
}

static double dot_product_2d(t_point2d *vec1, t_point2d *vec2)
{
	double result = vec1->x * vec2->x + vec1->y * vec2->y;
	return result;
}

typedef struct s_circle
{
	t_vector4d center;
	double radius;
} t_circle;

bool segment_circle_intersection(t_segment_d *segment, t_circle *circle)
{
	t_vector4d line_vec;
	t_vector4d circle_vec;
	double line_length_squared;
	double t;
	t_vector4d closest_point;
	t_vector4d dist_vec;

	line_vec.vec = segment->point_b.vec - segment->point_a.vec;
	circle_vec.vec = circle->center.vec - segment->point_a.vec;
	line_length_squared = dot_product_3d(&line_vec, &line_vec);
	t = dot_product_2d(&circle_vec, &line_vec) / line_length_squared;
	t = fmaxf(0, fminf(1, t)); // Clamping t
	closest_point.vec = segment->point_a.vec + t * line_vec.vec;
	dist_vec.vec = circle->center.vec - closest_point.vec;
	return (dot_product_2d(&dist_vec, &dist_vec) <= circle->radius * circle->radius);
}

bool player_wall_intersection(t_segment_d *segment, t_vector4d *player_pos)
{
	t_circle circle;
	t_segment_d *portal_dest;

	circle.center = *player_pos;
	circle.radius = PLAYER_RADIUS / 2;
	if (segment_circle_intersection(segment, &circle))
	{
		if (segment->data.type == PORTAL)
		{
			if ((player_pos->z - (PLAYER_HEIGHT / 2) > segment->data.ceil) && (player_pos->z + (PLAYER_HEIGHT / 2) < segment->data.floor))
			{
				portal_dest = segment->data.data.portal.destination;
				if (player_pos->z - (PLAYER_HEIGHT / 2) > portal_dest->data.ceil && player_pos->z + (PLAYER_HEIGHT / 2) < portal_dest->data.floor)
					return (false);
				return true;
			}
		}
		else
		{
			// return (player_pos->z - (PLAYER_HEIGHT / 2) > segment->data.ceil && player_pos->z + (PLAYER_HEIGHT / 2) < segment->data.floor);
			return (true);
		}
		return (false);
	}
	return (false);
}

t_vector4d bsp_check_player_collision(t_3d_render *render, t_vector4d *player_pos)
{
	t_tree_node *node;
	t_bsp_tree_node_data *data;
	t_segment_d *segment;
	t_list *seg_list;
	t_vector4d collision_normal;

	collision_normal = (t_vector4d){{0, 0, 0, 0}};
	node = bsp_search_point_fast(render->map->bsp, player_pos);
	data = node->data;
	seg_list = data->sector_segments;

	collision_normal.z += (data->sector_data.ceil > (player_pos->z
		- (PLAYER_HEIGHT / 2)));
	collision_normal.z -= data->sector_data.floor < (player_pos->z
		+ (PLAYER_HEIGHT / 2));
	while (seg_list)
	{
		segment = seg_list->content;
		if (player_wall_intersection(segment, player_pos))
		{
			collision_normal.vec += segment->data.normal.vec;
		}
		seg_list = seg_list->next;
	}
	return (collision_normal);
}

t_collision_info is_collision(t_vector4d current_pos, t_vector4d new_pos, t_3d_render *render)
{
	t_collision_info collision_info;

	collision_info.collision_normal = bsp_check_player_collision(render, &new_pos);
	if (collision_info.collision_normal.x != 0 || collision_info.collision_normal.y != 0 || collision_info.collision_normal.z != 0)
	{
		printf("collision detected\n");
		collision_info.collision = true;
		// normalize_vector_3d(&collision_info.collision_normal);
	}
	else
		collision_info.collision = false;
	return collision_info;
}

void player_handle_event(t_cub *data, t_game_data *game_data)
{
	// Get the movement directions (still in world coordinates)
	t_vector4d translation;

	translation.x = data->inputs.action_states[a_move_right] - data->inputs.action_states[a_move_left];
	translation.y = data->inputs.action_states[a_move_forward] - data->inputs.action_states[a_move_backward];
	translation.z = data->inputs.action_states[a_move_down] - data->inputs.action_states[a_move_up];

	// Scale the translation vector
	const double translation_scale = 0.2;
	translation.x *= translation_scale;
	translation.y *= translation_scale;
	translation.z *= translation_scale;

	// Get forward and right vectors from player's dir (assuming it's normalized)
	t_point2d forward = vector4d_to_point2d(&game_data->state.player.dir);
	t_point2d right = {{-forward.y, forward.x}};

	// Convert world coordinates translation to player's local coordinates
	t_vector4d new_translation;
	new_translation.x = translation.y * forward.x + translation.x * right.x;
	new_translation.y = translation.y * forward.y + translation.x * right.y;
	new_translation.z = translation.z;
	translation = new_translation;

	// Apply the translation to the player's position with acceleration
	const double acceleration = 0.1;
	game_data->state.player.velocity.x += translation.x * acceleration;
	game_data->state.player.velocity.y += translation.y * acceleration;
	game_data->state.player.velocity.z += translation.z * acceleration;

	// Apply deceleration to gradually slow down the player's velocity
	const double deceleration = 0.05;
	game_data->state.player.velocity.x *= (1 - deceleration);
	game_data->state.player.velocity.y *= (1 - deceleration);
	game_data->state.player.velocity.z *= (1 - deceleration);

	// Update player's position with collision detection
	t_vector4d new_pos = game_data->state.player.pos;
	new_pos.x += game_data->state.player.velocity.x;
	new_pos.y += game_data->state.player.velocity.y;
	new_pos.z += game_data->state.player.velocity.z;

	t_collision_info collision_info;

	/* code */

	// new_pos.vec += 0.5 * game_data->state.player.velocity.vec;
	collision_info = is_collision(game_data->state.player.pos, new_pos, &data->game_data.game_view_render);
	collision_info.collision &= !(data->inputs.action_states[a_decrease_sector_floor] && data->inputs.action_states[a_increase_sector_floor]);// && data->inputs.action_states[a_move_left] && data->inputs.action_states[a_move_right]);
	if (collision_info.collision)
	{
		// Calculate the sliding vector based on the collision normal

		// double dot_product = 1;//dot_product_3d(&game_data->state.player.velocity, &collision_info.collision_normal);

		double dot_product = dot_product_3d(&game_data->state.player.velocity, &collision_info.collision_normal);

		// if (dot_product > 0)
		// 	dot_product *= -1;

		printf("dot_product: %f\n", dot_product);
		printf("collision_info.collision_normal: %f, %f, %f\n", collision_info.collision_normal.x, collision_info.collision_normal.y, collision_info.collision_normal.z);
		printf("game_data->state.player.velocity: %f, %f, %f\n", game_data->state.player.velocity.x, game_data->state.player.velocity.y, game_data->state.player.velocity.z);
		t_vector4d sliding_vector;
		// if (dot_product < 0)
		// 	collision_info.collision_normal.vec *= -1;

		sliding_vector.x = game_data->state.player.velocity.x - 1.02 * dot_product * collision_info.collision_normal.x; // dot_product * collision_info.collision_normal.x; //
		sliding_vector.y = game_data->state.player.velocity.y - 1.02 * dot_product * collision_info.collision_normal.y; // dot_product * collision_info.collision_normal.y; //
		sliding_vector.z = game_data->state.player.velocity.z - 1.02 * dot_product * collision_info.collision_normal.z; // dot_product * collision_info.collision_normal.z; //

		// Update the player's velocity with the sliding vector
		game_data->state.player.velocity = sliding_vector;
		new_pos.x = game_data->state.player.pos.x + game_data->state.player.velocity.x;
		new_pos.y = game_data->state.player.pos.y + game_data->state.player.velocity.y;
		new_pos.z = game_data->state.player.pos.z + game_data->state.player.velocity.z;
	}

	game_data->state.player.pos = new_pos;

	// Handle the turning of the player
	const double angle_scale = 0.1;
	double angle_movement = angle_scale * (data->inputs.action_states[a_turn_right] - data->inputs.action_states[a_turn_left]);
	t_matrix3x3 transformation = rotation_matrix(angle_movement);
	t_point2d rotated_dir = matrix_vector_multiply(transformation, vector4d_to_point2d(&game_data->state.player.dir));
	game_data->state.player.dir = point2d_to_vector4d(&rotated_dir);
	game_data->state.player.right = game_data->state.player.dir;
	game_data->state.player.right.x = -game_data->state.player.dir.y;
	game_data->state.player.right.y = game_data->state.player.dir.x;

	// Update game state

}

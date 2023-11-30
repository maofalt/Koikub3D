

#include "structures.h"
#include "draw_utils.h"
#include "ressources_managers.h"
#include <assert.h>

double	calc_seg_coef(
			t_segment_d *segment
			);

int project_wall(t_3d_render *render,
					t_segment_d *wall,
					t_segment_d *projected_top,
					t_segment_d *projected_bottom
					);

static inline void	draw_vertical_line(
			t_canvas *canvas,
			t_img_data	*image,
			int 	img_x,
			int 		screen_x,
			int 		screen_top,
			const int	screen_bottom
			)
{
	uint32_t	*img = (void *)image->addr;
	int			offset;
	int			offset_img;
	double		y = 0;

	img_x = img_x % image->size.x;
	double factor  =  (double)image->size.y / (double) (screen_bottom - screen_top);
	y = fmax(-screen_top, y);
	while (screen_top + y < screen_bottom)
	// while (y * factor < image->size.y)
	{
		if (y + screen_top >= canvas->size.y)
			return;
		if (img_x > canvas->size.x)
			return;
		// if (y + screen_top < 0)
		// 	return;
		offset = (screen_top + y) * canvas->size.x + screen_x;
		offset_img = (((int)(factor * y) % image->size.y) * image->size.x) + img_x;
		canvas->pixels[offset].d = img[offset_img];
		++y;
	}
}

static inline void	draw_vertical_line_color(
			t_canvas *canvas,
			const int x,
			int top,
			int bottom,
			const t_color color
			)
{
	int					offset;

	// assert(x >= 0);
	// assert(x < canvas->size.x);
	// assert(top >= 0);
	// assert(bottom <= canvas->size.y);
	top = fmax((double)top, 0);
	bottom = fmin((double)bottom, canvas->size.y);
	while (top < bottom)
	{
		offset = top * canvas->size.x + x;
		canvas->pixels[offset] = color;
		++top;
	}
}

t_segment_d	transform_camera_relative_segment(
	t_segment_d segment,
	t_camera *camera);

int	relative_segment_clip_front(t_segment_d *segment);

t_vector4d	project_point(t_3d_render *render, t_vector4d point);

static int	project_segment(
	t_3d_render *render,
	t_segment_d segment,
	t_segment_d *projected_seg)
{
	segment = transform_camera_relative_segment(segment, render->camera);
	if (relative_segment_clip_front(&segment))
		return (1);
	segment.point_a = project_point(render, segment.point_a);
	segment.point_b = project_point(render, segment.point_b);
	// if (segment.point_a.x < segment.point_b.x)
	// {
	// 	*projected_seg = segment;
	// }
	// else
	// {
	// 	projected_seg->point_a = segment.point_b;
	// 	projected_seg->point_b = segment.point_a;
	// }
	return (0);
}

int	draw_player(t_3d_render *render)
{
	t_segment_d	scaled_segment;

	scaled_segment.point_a = render->camera->pos;
	scaled_segment.point_b.vec = render->camera->pos.vec + render->camera->dir.vec;
	scaled_segment.point_a.vec *= 10;
	scaled_segment.point_b.vec *= 10;
	scaled_segment.point_a.vec += render->middle.vec;
	scaled_segment.point_b.vec += render->middle.vec;
	draw_segment_canvas(render->canvas, &scaled_segment,
		(t_color){.d = 0xFFFFFFFF});
	return (0);
}

typedef enum e_side
{
	SIDE_ON			= 0b0000,
	SIDE_LEFT		= 0b0001,
	SIDE_RIGHT		= 0b0010,
	SIDE_INTERSECT	= 0b0011,
}	t_side;


static t_side	point_segment_side(t_segment_d *separator, t_vector4d *segment_point)
{
	t_vector4d	ab;
	t_vector4d	ap;
	double		cross_product;

	ab.vec = separator->point_b.vec - separator->point_a.vec;
	ap.vec = segment_point->vec - separator->point_a.vec;
	cross_product = ab.x * ap.y - ab.y * ap.x;
	if (cross_product > 0)
		return (SIDE_RIGHT);
	else if (cross_product < 0)
		return (SIDE_LEFT);
	else
		return (SIDE_ON);
}

void invert_if_needed(t_3d_render *render, t_segment_d *segment)
{
	t_side side;
	t_vector4d	tmp;

	side = point_segment_side(segment, &render->camera->pos);
	if (side == SIDE_LEFT)
	{
		// if ()
		tmp = segment->point_a;
		segment->point_a = segment->point_b;
		segment->point_b = tmp;
	}
	else
	{

	}

}

void draw_wall_texture(
	t_3d_render *render,
	t_segment_d *wall,
	double left,
	double right
)
{
	t_segment_d projected_top;
	t_segment_d projected_bot;
	double coef_top;
	double coef_bot;
	double texture_width = texture_get_frame(wall->data.data.wall.texture.texture)->size.x;

	t_segment_d	relative_segment;
	t_segment_d	clipped_relative_segment;
	// left = 0;
	// right = render->canvas->size.x;

	invert_if_needed(render, wall);

	relative_segment = transform_camera_relative_segment(*wall, render->camera);
	// if (relative_segment.point_a.x > relative_segment.point_b.x)
	// {
	// 	t_vector4d	tmp;
	// 	tmp = relative_segment.point_a;
	// 	relative_segment.point_a = relative_segment.point_b;
	// 	relative_segment.point_b = tmp;
	// }
	printf("%f, %f, -> %f, %f\n", wall->point_a.x, wall->point_a.y, wall->point_b.x, wall->point_b.y);



	clipped_relative_segment = relative_segment;
	if (relative_segment_clip_front(&clipped_relative_segment))
		return ;


	double clipped_relative_segment_max_y = fmax(clipped_relative_segment.point_a.y,clipped_relative_segment.point_b.y);
	double clipped_relative_segment_min_y = fmin(clipped_relative_segment.point_a.y,clipped_relative_segment.point_b.y);
	double relative_segment_max_y = fmax(relative_segment.point_a.y,relative_segment.point_b.y);
	double relative_segment_min_y = fmin(relative_segment.point_a.y,relative_segment.point_b.y);

	double u0;
	double u1;
	if(fabs(clipped_relative_segment.point_b.x - clipped_relative_segment.point_a.x) > fabs(relative_segment.point_a.y - relative_segment.point_b.y))
	{
		double relative_segment_width = relative_segment.point_b.x - relative_segment.point_a.x;
		assert(relative_segment_width != 0);
		u0 = ((clipped_relative_segment.point_a.x - relative_segment.point_a.x) * texture_width) / relative_segment_width;
		u1 = ((clipped_relative_segment.point_b.x - relative_segment.point_a.x) * texture_width) / relative_segment_width;
		// printf("clipped_relative_segment.point_a.x %f, relative_segment.point_a.x %f, texture_width: %f, relative_segment_width: %f\n", clipped_relative_segment.point_a.x, relative_segment.point_a.x, texture_width, relative_segment_width);

	}
	else
	{
		double relative_segment_width = relative_segment.point_b.y - relative_segment.point_a.y;
		assert(relative_segment_width != 0);
		u0 = ((clipped_relative_segment.point_a.y - relative_segment.point_a.y) * texture_width) / relative_segment_width;
		u1 = ((clipped_relative_segment.point_b.y - relative_segment.point_a.y) * texture_width) / relative_segment_width;
		// printf("clipped_relative_segment.point_a.y %f, relative_segment.point_a.y %f, texture_width: %f, relative_segment_width: %f\n", clipped_relative_segment.point_a.y, relative_segment.point_a.y, texture_width, relative_segment_width);
	}

	printf("relative_segment: %f, %f, -> %f, %f\n", relative_segment.point_a.x, relative_segment.point_a.y, relative_segment.point_b.x, relative_segment.point_b.y);

	// u0 = 0;
	// u0 = texture_width;
	printf("u0 %f, u1 %f\n", u0, u1);
	// u0 = 0;
	// u1 = texture_width;
	// u1 = fabs(u1);
	// u0 = fabs(u0);

	if (project_wall(render, wall, &projected_top, &projected_bot))
		return ;

	coef_bot = calc_seg_coef(&projected_bot);
	coef_top = calc_seg_coef(&projected_top);
	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
	double x = left;
	double top = projected_top.point_a.y;
	double bot = projected_bot.point_a.y;
	printf("projected_top.point_a.x:%f, (projected_top.point_b.x%f\n", projected_top.point_a.x, projected_top.point_b.x);

	while (x < right)
	{
		// double alpha = (x - projected_top.point_a.x) / (projected_top.point_b.x - projected_top.point_a.x);
		// // Interpolate the reciprocal of the z-value for perspective correction
		// double one_over_z = (1 - alpha) / relative_segment.point_b.y + alpha / relative_segment.point_a.y;
		// double txtx = (((alpha) * (u0 / relative_segment.point_a.y) + (1 - alpha) * (u1 / relative_segment.point_b.y))) / one_over_z;

		// double alpha = (x - projected_top.point_a.x) / (projected_top.point_b.x - projected_top.point_a.x);
		// // Interpolate the reciprocal of the z-value for perspective correction
		// double one_over_z = (1 - alpha) / clipped_relative_segment.point_b.y + alpha / clipped_relative_segment.point_a.y;
		// // double txtx = (((alpha) * (u0 / relative_segment.point_a.y) + (1 - alpha) * (u1 / relative_segment.point_b.y))) / one_over_z;
		// double txtx = (((alpha) * (u0 / clipped_relative_segment.point_a.y) + (1 - alpha) * (u1 / clipped_relative_segment.point_b.y))) / one_over_z;
	// printf
			// Calculate the alpha for the current x-coordinate
		double alpha = (x - projected_top.point_a.x) / (projected_top.point_b.x - projected_top.point_a.x);

		// Interpolate the reciprocal of the z-value for perspective correction
		double one_over_z = (1 - alpha) / clipped_relative_segment.point_a.y + alpha /  clipped_relative_segment.point_b.y;

		// Calculate the interpolated texture coordinate using perspective correction
		double txtx = (((1 - alpha) * (u0 / clipped_relative_segment.point_a.y) + alpha * (u1 / clipped_relative_segment.point_b.y))) / one_over_z;
		txtx = fmin(fmax(0, txtx), texture_width);
		// printf("clipped_relative_segment.point_a.y %f , relative_segment.point_b.y: %f\n",clipped_relative_segment.point_a.y, clipped_relative_segment.point_b.y);
		// printf("x: %f, , txtx :%f, u0: %f, u1 %f, alpha : %f \n", x ,txtx, u0, u1, alpha);


		draw_vertical_line(render->canvas,
			texture_get_frame(wall->data.data.wall.texture.texture), txtx,
			x, top, bot);

		// draw_vertical_line_color(render->canvas,
		// 				x, top, bot, (t_color) {.a=txtx, .r = 255, .g = 0, .b=255});

		// Increment y-coordinates for next line
		top += coef_top;
		bot += coef_bot;
		x++;
	}

	relative_segment = *wall;
	relative_segment.point_a.vec *= 10;
	relative_segment.point_b.vec *= 10;
	relative_segment.point_a.vec += render->middle.vec;
	relative_segment.point_b.vec += render->middle.vec;
	draw_player(render);
	draw_segment_canvas(render->canvas, &relative_segment, (t_color) {.d=0xFFFF0000});
	put_pixel_on_virtual_canvas(render->canvas, (t_point2d){.x=relative_segment.point_a.x, .y=relative_segment.point_a.y}, (t_color){.d=0xFF00FF00});
	put_pixel_on_virtual_canvas(render->canvas, (t_point2d){.x=relative_segment.point_b.x, .y=relative_segment.point_b.y}, (t_color){.d=0xFF0000FF});
}

//###########################################




//this is a GPT refacto
void draw_wall_texture_old(
	t_3d_render *render,
	t_segment_d *wall,
	double left,
	double right
)
{
	t_segment_d projected_top;
	t_segment_d projected_bot;
	double coef_top;
	double coef_bot;

	// If wall projection fails, exit the function
	if (project_wall(render, wall, &projected_top, &projected_bot))
		return ;

	// Save original unclipped x-coordinates for depth interpolation
	double original_left_x = projected_top.point_a.x;
	double original_right_x = projected_top.point_b.x;

	// Save original z values for interpolation
	double original_z_left = projected_top.point_a.z;
	double original_z_right = projected_top.point_b.z;

	// Clip x-coordinates against the screen borders
	left = fmax(projected_top.point_a.x, left);
	right = fmin(projected_top.point_b.x, right);

	// Interpolate new z-values based on the clipped x-coordinates
	double proportion_left = (left - original_left_x) / (original_right_x - original_left_x);
	double proportion_right = (right - original_left_x) / (original_right_x - original_left_x);

	double z_left = original_z_left + proportion_left * (original_z_right - original_z_left);
	double z_right = original_z_left + proportion_right * (original_z_right - original_z_left);

	// 	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	// projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	// projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	// projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);

	printf("z_left %f, \n", z_left);
	printf("z_right %f, \n", z_right);
	// Calculate segment coefficients
	coef_bot = calc_seg_coef(&projected_bot);
	coef_top = calc_seg_coef(&projected_top);
	printf("projected_top.point_a.y %f, \n", projected_top.point_a.y);
	printf("projected_bot.point_a.y %f, \n", projected_bot.point_a.y);
	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);



	// Calculate texture width and texture coordinates

	t_segment_d	relative_segment;
	t_segment_d	clipped_relative_segment;
	// left = 0;
	// right = render->canvas->size.x;

	relative_segment = transform_camera_relative_segment(*wall, render->camera);
	if (relative_segment.point_a.x > relative_segment.point_b.x)
	{
		t_vector4d	tmp;
		tmp = relative_segment.point_a;
		relative_segment.point_a = relative_segment.point_b;
		relative_segment.point_b = tmp;
	}

	clipped_relative_segment = relative_segment;
	if (relative_segment_clip_front(&clipped_relative_segment))
		return ;

	double texture_width = texture_get_frame(wall->data.data.wall.texture.texture)->size.x;
	double u0 = 0;
	double u1 = texture_width;

	if(fabs(clipped_relative_segment.point_b.x - clipped_relative_segment.point_a.x) > fabs(relative_segment.point_a.y - relative_segment.point_b.y))
	{
		double relative_segment_width = fabs(relative_segment.point_b.x - relative_segment.point_a.x);
		assert(relative_segment_width != 0);
		u0 = (fabs(clipped_relative_segment.point_a.x - relative_segment.point_a.x) * texture_width) / relative_segment_width;
		u1 = (fabs(clipped_relative_segment.point_b.x - relative_segment.point_a.x) * texture_width) / relative_segment_width;
		printf("clipped_relative_segment.point_a.x %f, relative_segment.point_a.x %f, texture_width: %f, relative_segment_width: %f\n", clipped_relative_segment.point_a.x, relative_segment.point_a.x, texture_width, relative_segment_width);

	}
	else
	{
		double relative_segment_width = fabs(relative_segment.point_b.y - relative_segment.point_a.y);
		assert(relative_segment_width != 0);
		u0 = (fabs(clipped_relative_segment.point_a.y - relative_segment.point_a.y) * texture_width) / relative_segment_width;
		u1 = (fabs(clipped_relative_segment.point_b.y - relative_segment.point_a.y) * texture_width) / relative_segment_width;
		printf("clipped_relative_segment.point_a.y %f, relative_segment.point_a.y %f, texture_width: %f, relative_segment_width: %f\n", clipped_relative_segment.point_a.y, relative_segment.point_a.y, texture_width, relative_segment_width);

	}

	printf("u0, %f, u1 %f\n", u0, u1);
	// Loop over the x-coordinates from left to right
	for (double x = left; x < right; ++x) {
		// Calculate the alpha for the current x-coordinate
		double alpha = (x - left) / (right - left);

		// Interpolate the reciprocal of the z-value for perspective correction
		double one_over_z = (1 - alpha) / z_left + alpha / z_right;

		// Calculate the interpolated texture coordinate using perspective correction
		double txtx = (((1 - alpha) * (u0 / z_left) + alpha * (u1 / z_right))) / one_over_z;

		// Draw the vertical line with interpolated texture coordinate and y-coordinates
		draw_vertical_line(render->canvas,
			texture_get_frame(wall->data.data.wall.texture.texture), txtx,
			x, projected_top.point_a.y, projected_bot.point_a.y);

		// Increment y-coordinates for next line
		projected_top.point_a.y += coef_top;
		projected_bot.point_a.y += coef_bot;
	}
}



// void	draw_wall_texture(
// 		t_3d_render *render,
// 		t_segment_d	*wall,
// 		double left,
// 		double right
// 	)
// {
// 	t_segment_d		projected_top;
// 	t_segment_d		projected_bot;
// 	double			coef_top;
// 	double			coef_bot;

// 	if (project_wall(render, wall, &projected_top, &projected_bot))
// 		return ;

// 	left =  fmax(projected_top.point_a.x, left);
// 	right = fmin(projected_top.point_b.x, right);

// 	double proportion_left = (left - projected_top.point_a.x) / (projected_top.point_b.x - projected_top.point_a.x);
// 	double proportion_right = (right - projected_top.point_a.x) / (projected_top.point_b.x - projected_top.point_a.x);

// 	double z_left = projected_top.point_a.z + (projected_top.point_b.z - projected_top.point_a.z) * proportion_left;
// 	double z_right = projected_top.point_a.z + (projected_top.point_b.z - projected_top.point_a.z) * proportion_right;
// 	projected_top.point_a.z = z_left;
// 	projected_top.point_b.z = z_right;


// 	coef_bot = calc_seg_coef(&projected_bot);
// 	coef_top = calc_seg_coef(&projected_top);
// 	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
// 	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
// 	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
// 	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);


// 	double x = 0;


// 	// double factor  =  texture_get_frame(wall->data.data.wall.texture.texture)->size.y / fmin((projected_bot.point_a.y - projected_top.point_a.y), (projected_bot.point_b.y - projected_top.point_b.y));

// 	double u0 = 0;
// 	double u1 = 255;
// 	double z0 = projected_top.point_a.z;
// 	double z1 = projected_top.point_b.z;


// 	double txtx;
// 	while (left + x < right)
// 	{

// 		// printf("factors :%f, bot:%f, top:%f \n", factor, projected_bot.point_a.y, projected_top.point_a.y);
// 		double alpha = x / (right - left);
// 		printf("alph: %f, z0: %f, z1: %f\n",alpha, z0, z1);
// 		u1 = texture_get_frame(wall->data.data.wall.texture.texture)->size.x;
// 		// txtx = (((1-alpha) * (u0 / z0) + alpha * (u1 / z1))) / ((((1-alpha) / z0) + alpha/z1));
// 		txtx = (((1-alpha) * (u0 / z0) + alpha * (u1 / z1))) / ((((1-alpha) / z0) + alpha/z1));
// 		// draw_solid_wall_line(render->canvas, x, projected_top.point_a.y,
// 		// 	projected_bot.point_a.y);
// 		draw_vertical_line(render->canvas,
// 			texture_get_frame(wall->data.data.wall.texture.texture), txtx,
// 				left + x ,projected_top.point_a.y, projected_bot.point_a.y);
// //
// 		u1 = 255;
// 		txtx = (((1-alpha) * (u0 / z0) + alpha * (u1 / z1))) / ((((1-alpha) / z0) + alpha/z1));

// 		// draw_vertical_line_color(render->canvas,
// 		// 		left + x ,projected_top.point_a.y, projected_bot.point_a.y, (t_color) {.a=txtx, .r = 255, .g = 0, .b=255});

// 		projected_top.point_a.y += coef_top;
// 		projected_bot.point_a.y += coef_bot;
// 		++x;
// 	}

// }
// 		draw_vertical_line(canvas, image, x, 500, 90+ x/10, 200 - x/10);


// void	draw_solid_wall(
// 	t_3d_render *render,
// 	t_segment_d	*wall,
// 	double left,
// 	double right
// 	)
// {
// 	t_segment_d		projected_top;
// 	t_segment_d		projected_bot;
// 	double			coef_top;
// 	double			coef_bot;

// 	if (project_wall(render, wall, &projected_top, &projected_bot))
// 		return ;
// 	left = fmax(projected_top.point_a.x, left);
// 	right = fmin(projected_top.point_b.x, right);
// 	coef_bot = calc_seg_coef(&projected_bot);
// 	coef_top = calc_seg_coef(&projected_top);
// 	projected_top.point_a.y += coef_top * (left - projected_top.point_a.x);
// 	projected_top.point_b.y += coef_top * (right - projected_top.point_b.x);
// 	projected_bot.point_a.y += coef_bot * (left - projected_bot.point_a.x);
// 	projected_bot.point_b.y += coef_bot * (right - projected_bot.point_b.x);
// 	double x;
// 	while (x + left < right)
// 	{
// 		draw_solid_wall_line(render, left, , projected_top.point_a.y,
// 			projected_bot.point_a.y);
// 		projected_top.point_a.y += coef_top;
// 		projected_bot.point_a.y += coef_bot;
// 		++x;
// 	}
// }

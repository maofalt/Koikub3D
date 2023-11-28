

#include "structures.h"
#include "ressources_managers.h"

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

//this is a GPT refacto
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
	double texture_width = texture_get_frame(wall->data.data.wall.texture.texture)->size.x;
	double u0 = 1;  // Starting texture coordinate
	double u1 = texture_width - 1;  // Ending texture coordinate

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

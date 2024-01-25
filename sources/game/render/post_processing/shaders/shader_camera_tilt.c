#include <math.h>
#include "draw_utils.h"
#include "structures.h"
#include "maths_utils.h"
#include "render_3D.h"

// Function to calculate the rotation based on camera movement
double calculate_rotation(double offset, double amplitude, double frequency)
{
	return amplitude * sin(offset * frequency);
}
//TODO move this in .h
static double dot_product_3d(t_vector4d *vec1, t_vector4d *vec2)
{
	const t_v4d	product = vec1->vec * vec2->vec;

	return (product[0] + product[1] + product[2]);
}

t_color shader_small_camera_tilt(t_color original_color, int offset, t_3d_render *render, double movement_offset)
{


	// movement_offset = dot_product_3d(&render->camera->velocity, &render->camera->right);
	movement_offset =  render->camera->tilt;//movement_offset;
	// printf("movement_offset: %f\n", movement_offset);
	double movement_offset_x = movement_offset;
	double movement_offset_y = movement_offset;

	// Calculate the rotation for x and y coordinates
	double rotation_x; // = 3;  //calculate_rotation(movement_offset_x, 1, 3);
	double rotation_y; // = -3;  //calculate_rotation(movement_offset_y, 1, 3);

	rotation_x = movement_offset * 30; //+1*  render->camera->tilt;//render->camera->velocity.x * 10;
	rotation_y = movement_offset * 30  ; //+ 0.5*    render->camera->tilt;//render->camera->velocity.x * 10;

	// Apply the rotation to the offset
	int x = offset % render->width;
	int y = offset / render->width;

	// Apply small camera rotation effect to the x and y coordinates
	double rotation_intensity = 0.01; // Adjust the intensity of the rotation effect
	double new_x = (x - render->width / 2) * cos(rotation_x * rotation_intensity) - (y - render->height / 2) * sin(rotation_x * rotation_intensity) + render->width / 2;
	double new_y = (x - render->width / 2) * sin(rotation_y * rotation_intensity) + (y - render->height / 2) * cos(rotation_y * rotation_intensity) + render->height / 2;

	int new_offset = (int)new_y * render->width + (int)new_x;

	// Check if the new offset is within the canvas bounds
	if (new_offset >= 0 && new_offset < render->width * render->height && new_x >= 0 && new_x < render->width && new_y >= 0 && new_y < render->height)
	{
		// Apply the rotation effect to the original color
		original_color = render->buffers.color_bis[new_offset];
	}

	return original_color;
}

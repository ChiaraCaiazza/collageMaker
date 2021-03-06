#include "imageUtils.h"
#include <math.h>

int get_width(const VipsImage *image) {
	return vips_image_get_width(image);
}

int get_height(const VipsImage *image) {
	return vips_image_get_height(image);
}

//horizontal image resolution in pixels per millimeter
double get_horiz_resol(const VipsImage *image) {
	return vips_image_get_xres(image);
}

//vertical image resolution in pixels per millimeter
double get_vert_resol(const VipsImage *image) {
	return vips_image_get_yres(image);
}

int min_resol(VipsImage **img_array, int num_elem){
	int i, res_min_index = 0;
	double res_min = get_horiz_resol(img_array[0]) * get_vert_resol(img_array[0]);
	for (i=1; i < num_elem; i++) {
		int resolution = get_horiz_resol(img_array[i]) * get_vert_resol(img_array[i]);
		if ( resolution < res_min){
			res_min = resolution;
			res_min_index = i;
		}
	}
	return res_min_index;
}

int min_height(VipsImage **img_array, int num_elem){
	int i, i_app = 0;
	int min = get_height(img_array[0]);
	for (i=1; i<num_elem; i++){
		int height = get_height(img_array[i]);
		if (height < min){
			min = height;
			i_app = i;
		}
	}
	return i_app;
}

int min_width(VipsImage **img_array, int num_elem){
	int i, i_app = 0;
	int min = get_width(img_array[0]);
	for (i=1; i<num_elem; i++){
		int width = get_width(img_array[i]);
		if (width < min){
			min = width;
			i_app = i;
		}
	}
	return i_app;
}

double* image_width_over_height(VipsImage **img_array, int num_elem){
	int i;
	double* ret = (double*)malloc(sizeof(double)*num_elem);
	for (i=0; i<num_elem; i++)
		ret[i] = (double)get_width(img_array[i]) / (double)get_height(img_array[i]);
	return ret;
}
	
int* find_best_match(double* images_ratio, double* frames_ratio, int num_elem){
	int i, j;
	int remaining = num_elem;
	int image_index, frame_index;
	double min;
	int* ret = (int*)malloc(sizeof(int)*num_elem);
	double** matrix = (double**)malloc(sizeof(double*)*num_elem);
	for (i=0; i < num_elem; i++){		
		matrix[i] = (double*)malloc(sizeof(double)*num_elem);
	}
	for (i=0; i<num_elem; i++){	//for every image
		for (j=0; j<num_elem; j++){	//for every frame
			if (frames_ratio[j] > images_ratio[i])
				matrix[i][j] = frames_ratio[j]-images_ratio[i];
			else
				matrix[i][j] = images_ratio[i]-frames_ratio[j];
		}
	}
	while (remaining!=0){
		image_index = 0;
		frame_index = 0;
		min = matrix[0][0];
		for (i=0; i<num_elem; i++){
			for (j=0; j<num_elem; j++){
				if (matrix[i][j] < min){					
					min = matrix[i][j];
					image_index = i;
					frame_index = j;
				}
			}
		}
		ret[frame_index] = image_index;
		remaining--;
		for (i=0; i<num_elem; i++){
			matrix[image_index][i] = 10.0;
			matrix[i][frame_index] = 10.0;
		}	
	}
	return ret;
}

VipsImage* create_blank_canvas(int width, int height)
{
	VipsImage *canvas, *canvas_drawable;
	vips_black (&canvas, width, height, NULL);
	vips_colourspace(canvas, &canvas_drawable, VIPS_INTERPRETATION_sRGB, NULL);
	
	return canvas_drawable;
}

void protect_image_from_flood(VipsImage* image)
{
	vips_draw_rect1(image, 255.0, 0, 0, get_width(image), get_height(image), NULL);
}


//new_x = x * cos(alpha) - y * sin(alpha)
//new_y = x * sin(alpha) + y * cos(alpha)
void rotate_image(VipsImage** image, double rotation)
{
	VipsImage* temp_image;
	double rotation_rad = rotation / (180.0 / M_PI);
	double a, b, c, d;
	a = cos(rotation_rad);
	b = -sin(rotation_rad);
	c = sin(rotation_rad);
	d = cos(rotation_rad);
	
	vips_affine (*image , &temp_image, a, b, c, d, NULL);
	*image = temp_image;
}



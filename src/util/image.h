#ifndef UTIL_IMAGE_H_
#define UTIL_IMAGE_H_

#include <gtk/gtk.h>

#include "../util/vector.h"

typedef struct
{
    int width;
    int height;
    bool *raster;
    int x_root;
    int y_root;
    int trueWidth;
    int trueHeight;
    char character;
} Image;

Image *img_create(GdkPixbuf *bmp);

void img_free(Image *img);

Image *img_crop(Image *img, int x, int y, int width, int height);

void img_crop_ip(Image *img, int x, int y, int width, int height);

Image *img_crop_border(Image *img, bool ip);

void img_print(const Image *img);

Image *img_extract_character(Image *img);

void _img_explore_character(Image *img, Vector *pixels, int x, int y);

Image *img_normalize(Image *img, int size);

int img_get_orientation_factor(Image *image);

Image *img_autorotate(Image *img);

Image *img_rotate(Image *img, int degrees);

#endif /* UTIL_IMAGE_H_ */

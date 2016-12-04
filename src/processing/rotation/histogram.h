//
// Created by tristan9 on 12/4/16.
//

#ifndef CROCRODILE_HISTOGRAM_H
#define CROCRODILE_HISTOGRAM_H

#include "../../util/maths.h"
#include "rotation.h"

void gray_histogram(Image *surface, int *array);
void v_histogram(Image *surface, int *array);
void v_histogram_bounds(Image *surface, int *array, Rectangle *bounds);
void h_histogram(Image *surface, int *array);
void h_histogram_bounds(Image *surface, int *array, Rectangle *bounds);
void r_histogram(Image *surface, int *array, int angle);
Matrix *hrlsa(Matrix *matrix);
Matrix *vrlsa(Matrix *matrix);

#endif //CROCRODILE_HISTOGRAM_H

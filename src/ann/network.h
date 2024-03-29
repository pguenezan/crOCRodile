#ifndef ANN_NETWORK_H
#define ANN_NETWORK_H

#include "../util/vector.h"
#include "../util/maths.h"

typedef struct
{
    Vector *layers;
    char *name;
} Network;

typedef struct
{
    Matrix *a;
    Matrix *w;
    Matrix *z;
    int depth;
} Layer;

Layer *lyr_create(int inputSize, int nbExample, int prevInput, int depth);

void lyr_free(Layer *lyr);

Network *net_create(int inputSize, int nb, char *name);

void net_free(Network *net);

void net_randomizeLayer(Network *net, int depth);

void net_loadLayerWeights(Network *net, int depth);

void net_addLayer(Network *net, int nbUnit);

void net_loadInput(Network *net, float *input);

// ========== Forward ===========

void lyr_forward(Layer *previous, Layer *current);

void net_forward(Network *net);

// ========== Backward ==========

Vector *net_backward(Network *net, Matrix *y);

// ========== Num check =========

float net_cost(Network *net, Matrix *y);

Vector *net_numGrad(Network *net, Matrix *y);

#endif /* ANN_NETWORK_H */

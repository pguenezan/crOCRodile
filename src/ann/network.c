#include "network.h"

#include "../util/string.h"

#include <stdio.h>
#include <time.h>

Layer *lyr_create(int inputSize, int nbExample, int prevInput, int depth)
{
    Layer *lyr = (Layer *) malloc(sizeof(Layer));
    lyr->depth = depth;
    lyr->weights = mat_create(inputSize, prevInput, NULL);
    lyr->act = mat_create(inputSize, nbExample, NULL);
    return lyr;
}

void lyr_free(Layer *lyr)
{
    mat_free(lyr->weights, true);
    mat_free(lyr->act, true);
    free(lyr);
}

Network *net_create(int inputSize, int nbExample, char *name)
{
    Network *net = (Network *) malloc(sizeof(Network));
    net->name = name;
    net->layers = vec_create(2);
    vec_add(net->layers, lyr_create(inputSize, nbExample, 0, 0));
    return net;
}

void net_free(Network *net)
{
    for(int i = 0; i < net->layers->size; ++i)
        lyr_free((Layer *) vec_get(net->layers, i));
    vec_free(net->layers, false);
    free(net);
}

void net_randomizeLayer(Network *net, int depth)
{
    Layer *lyr = (Layer *) vec_get(net->layers, depth);
    srand((unsigned int) time(NULL));
    for(int i = 0; i < lyr->weights->width * lyr->weights->height; ++i)
    {
        lyr->weights->mat[i] = (float) rand() / (float) (RAND_MAX);
    }
}

void net_loadLayerWeights(Network *net, int depth)
{
    Layer *lyr = (Layer *) vec_get(net->layers, depth);
    char *path = str_con(5, "res/network/", net->name, "_", depth, ".layer");
    FILE *file = fopen(path, "w");
    for(int i = 0; i < lyr->weights->height * lyr->weights->width; ++i)
    {
        fread(lyr->weights->mat, sizeof(float), 1, file);
    }
    fclose(file);
}

void net_addLayer(Network *net, int nbUnit)
{
    Layer *fl = (Layer *) vec_get(net->layers, 0);
    int nbExample = fl->act->height;
    Layer *ll = (Layer *) vec_get(net->layers, net->layers->size - 1);
    int last = ll->weights->width;
    Layer *lyr = lyr_create(nbUnit, nbExample, last, net->layers->size);
    vec_add(net->layers, lyr);
}

void net_loadInput(Network *net, float *input)
{
    Layer *fl = (Layer *) vec_get(net->layers, 0);
    free(fl->act->mat);
    fl->act->mat = input;
}

// ========== Forward ==========

void lyr_forward(Layer *previous, Layer *current)
{
    mat_free(current->act, true);
    current->act = mat_multiply(previous->act, current->weights);
}

void net_forward(Network *net)
{
    for(int i = 1; i < net->layers->size; ++i)
        lyr_forward(vec_get(net->layers, i - 1), vec_get(net->layers, i));
}


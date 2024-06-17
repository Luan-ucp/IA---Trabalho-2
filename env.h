
#include <stdbool.h>
#include <stdlib.h>

#ifndef ENV_H
#define ENV_H

typedef struct
{
    int row;
    int col;
} Movement;

typedef struct {
    bool cheiro;
    bool vento;
} Sensation;

//Propriedades de cada lugar do ambiente
typedef struct{
    int row, col; //indice do lugar em um grid
    bool buraco; //se tem buraco
    bool monstro; //se tem monstro
    bool ouro; //se tem ouro
    Sensation sensation; //Sensações que podem ser percebidas pelo agente
} Place;

//O ambiente é uma matriz de lugares (grid)
typedef struct{
    int height, width;
    Place** grid;
} Enviroment;

Enviroment newEnviroment(int height, int width);
void delEnviroment(Enviroment* E);
void initEnviroment(Enviroment E, int numBuraco, int numMonstro);
bool isNeighbor(Place p, Place q);
Place* getPlace(Enviroment E, int i, int j);
void initSensations(Enviroment E);

#endif
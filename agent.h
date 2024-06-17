#include "env.h"

#ifndef AGENT_H
#define AGENT_H

typedef struct {
    Place* onde;
    bool comOuro;
    bool temFlecha;
    int score;
}Agent;

typedef struct 
{
    int row, col;
    bool buraco;
    bool monstro;
    bool vento;
    bool cheiro;
    bool seguro;
    bool visitado;
}PositionMap;

typedef struct
{
   int height;
   int width;
   PositionMap** grid;
} Map;

Map newMap(int height, int width);
void delMap(Map* map);
// bool RunAdventure(Map* map, Enviroment env);
// void SetMapVariable(Map* map, Agent agent);
// void InferMapHazards(Map* map);
void SetSafePlaces(Agent agent, Map* map);
void SetSafePosition(int row, int col, Map* map);
void printPos(int row, int col, Map* map);

void printSimulation(Agent A, Enviroment E);
bool move(Agent* A, Enviroment E, Place* target);
Agent newAgent(Enviroment E);
void sense(Agent A, Map* map);
Movement getMovement(Agent agent, Enviroment enviroment, Map map);

#endif 
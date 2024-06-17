#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "agent.h"

Agent newAgent(Enviroment E)
{
    Agent A;
    A.score = 0;
    A.temFlecha = true;
    A.onde = &E.grid[0][0];
    return A;
}

Map newMap(int height, int width)
{
    Map map;
    map.height = height;
    map.width = width;
    printf("map width %d %d\n", map.width, width);
    map.grid = malloc(map.height * sizeof(PositionMap*));

    if (map.grid != NULL)
    {
        for(int i = 0; i < map.height; i++)
        {
            map.grid[i] = malloc(width * sizeof(PositionMap));
            for (int j = 0; j < 0; j++)
            {
                map.grid[i][j].buraco = false;
                map.grid[i][j].monstro = false;
                map.grid[i][j].cheiro = false;
                map.grid[i][j].vento = false;
                map.grid[i][j].seguro = false;
                map.grid[i][j].row = i;
                map.grid[i][j].col = j;
            }
        }
    }

    return map;
}

void delMap(Map* map)
{
    if (map != NULL)
    {
        for(int i; i <map->height; i++)
        {
            free(map->grid[i]);
        }
        free(map->grid);
    }
}

void SetSafePlaces(Agent agent, Map* map)
{
    SetSafePosition(agent.onde->row + 1, agent.onde->col, map);
    SetSafePosition(agent.onde->row, agent.onde->col + 1, map);
    SetSafePosition(agent.onde->row - 1, agent.onde->col, map);
    SetSafePosition(agent.onde->row, agent.onde->col - 1, map);
}

void SetSafePosition(int row, int col, Map* map)
{
    if (row < 0 || row >= map->height || col < 0 || col >= map->width)
    {
        printf("Invalid position. \n");
        return;
    }
    
    map->grid[row][col].seguro = true;

    printf("Position (%d, %d) is safe. \n", row, col);
}

void printPos(int row, int col, Map* map)
{
    if (row < 0 || row >= map->height || col < 0 || col >= map->width)
    {
        printf("Invalid position %d %d %d %d. \n", row, col, map->height, map->width );
        return;
    }

    printf("Position (%d, %d). is %s \n", row, col, map->grid[row][col].seguro ? "safe" : "unsafe");
}

void sense(Agent agent, Map *map)
{
    if (agent.onde->sensation.cheiro)
    {
        printf("Aqui há um cheiro monstruoso. \n");
        map->grid[agent.onde->row][agent.onde->col].cheiro = true;

        printf("cheiro: %s\n", map->grid[agent.onde->row][agent.onde->col].cheiro ? "true" : "false");
    }

    if (agent.onde->sensation.vento)
    {
        printf("Aqui está batendo um vento estranho. \n");
        map->grid[agent.onde->row][agent.onde->col].vento = true;

        printf("vento: %s\n", map->grid[agent.onde->row][agent.onde->col].vento ? "true" : "false");
    }

    if (!agent.onde->sensation.cheiro && !agent.onde->sensation.vento)
    {
        printf("Aqui está seguro. \n");
        SetSafePlaces(agent, map);
    }
}

bool move(Agent* A, Enviroment E, Place* target){
/*
    Movimenta o agente para a posição Place, desde que esta seja uma vizinha de
    cleaner.ondeCleaner e que a bateria de C não esteja vazia.
*/
    if (isNeighbor(*A->onde, *target))
    {
        A->onde = target;
        A->score--;
        if (A->onde->monstro)
        {
            if (A->temFlecha)
            {
                printf("Matou o monstro. \n");
                A->score -= 10;
                A->onde->monstro = false;
            }
            else
            {
                printf("Pego pelo monstro.\n");
                A->score -= 1000;
            }
        }

        if (A->onde->buraco)
        {
            printf("Caiu no buraco. \n");
            A->score -= 1000;
        }

        if (A->onde->ouro)
        {
            printf("O ouro está aqui! \n");
            A->comOuro = true;
        }

        if (A->comOuro && A->onde->row==E.height-1 && A->onde->col==E.width-1)
        {
            printf("Escapou com o ouro! Parabéns. \n");
        }

        return true;
    }
    return false;
}

void printSimulation(Agent A, Enviroment E)
{
    for (int i=0; i<E.height; i++)
    {
        for (int j=0; j<E.width; j++)
        {
            if (&E.grid[i][j]==A.onde)
            {
                printf("O ");
            }
            else
            {
                printf("_ ");
            }
        }
        
        printf("\n");
    }
}
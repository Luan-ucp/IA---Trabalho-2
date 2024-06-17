#include "env.h"
#include <time.h>
#include <stdio.h>
//#include <unistd.h>
//#include <windows.height> função sleep no windows

void setSensation(Place* p, Place* v){

    if (isNeighbor(*v,*p))
    {
        if (v->buraco)
            p->sensation.vento = true;
        if (v->monstro)
            p->sensation.cheiro = true;
    }
}

/*------------------------------------------------------------------------------
    Funções básicas do ambiente
------------------------------------------------------------------------------*/

Enviroment newEnviroment(int height, int width){
    Enviroment E;
    E.height = height; E.width = width;
    E.grid = malloc(E.height*sizeof(Place*));

    if (E.grid!=NULL)
    {
        for (int i=0; i<height; i++)
        {
            E.grid[i] = malloc(E.width*sizeof(Place));

            if (E.grid[i]!= NULL)
            {
                for (int j=0; j<width; j++)
                {
                    E.grid[i][j].buraco = false;
                    E.grid[i][j].monstro = false;
                    E.grid[i][j].ouro = false;
                    E.grid[i][j].sensation.cheiro = false;
                    E.grid[i][j].sensation.vento = false;
                    E.grid[i][j].row = i;
                    E.grid[i][j].col = j;
                }
            }
        }
    }
    return E;
}

void delEnviroment(Enviroment* E){
    if (E!=NULL)
    {
        for (int i=0; i < E->height; i++)
        {
            free(E->grid[i]);
        }

        free(E->grid);
    }
}

void initEnviroment(Enviroment E, int numBuraco, int numMonstro){
/*
    Inicializa sujeiras no ambiente.
*/
    srand(time(NULL));
    
    //Inicializa buracos
    while (numBuraco>0)
    {
        int i, j;
        i = rand()%E.height;
        j = rand()%E.width;
        if (i!=0 && i!=E.height-1 && j!=0 && j!=E.width-1){
            if (!E.grid[i][j].buraco){
                E.grid[i][j].buraco = true;
                numBuraco--;
            }
        }
    }

    //Inicializa monstros
    while (numMonstro>0){
        int i, j;
        i = rand()%E.height;
        j = rand()%E.width;
        if (i!=0 && i!=E.height-1 && j!=0 && j!=E.width-1)
        {
            if (!E.grid[i][j].buraco && !E.grid[i][j].monstro)
            {
                E.grid[i][j].monstro = true;
                numMonstro--;
            }
        }
    }
    
    //Inicializa ouro
    bool gold = false;
    while (!gold)
    {
        int i, j;
        i = rand()%E.height;
        j = rand()%E.width;
        if (i!=0 && i!=E.height-1 && j!=0 && j!=E.width-1){
            if (!E.grid[i][j].buraco && !E.grid[i][j].monstro ){
                E.grid[i][j].ouro = true;
                gold = true;
            }
        }
    }

    initSensations(E);
}

void initSensations(Enviroment E){
    //Itera sobre posições no grid
    for (int i=0; i<E.height; i++)
        for (int j=0; j<E.width; j++){
            //Itera sobre vizinhos
            for (int k=0; k<E.height; k++)
                for (int l=0; l<E.width; l++){
                    setSensation(&E.grid[i][j],&E.grid[k][l]);
                }
        }
}

bool isNeighbor(Place p, Place q){
/*
    Considerando vizinhança-4 (em cruz). No exemplo abaixo, as posições marcadas
    como v são vizinhas de o, enquanto aquelas marcadas como u não são.
    u v u
    v o v
    u v u
*/
    if (p.row == q.row || p.col == q.col)
    {
        if (p.row == q.row + 1 || p.row == q.row - 1)
        {
            return true;
        }
        if (p.col == q.col + 1 || p.col == q.col - 1)
        {
            return true;
        }
    }
    return false;
}

Place* getPlace(Enviroment E, int i, int j){
/*
    Retorna ponteiro para Place com indices i e j no grid.
*/
    return &E.grid[i][j];
}


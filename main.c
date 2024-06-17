#include <stdio.h>
#include <stdbool.h>
#include "agent.h"
#include "env.h"

#define NUM_MONSTRO 1
#define NUM_BURACO 1

#define TAM_SALA 5

int main() 
{
    Enviroment enviroment = newEnviroment(TAM_SALA, TAM_SALA);
    initEnviroment(enviroment, NUM_BURACO, NUM_MONSTRO);

    Agent agent = newAgent(enviroment);

    Map map = newMap(TAM_SALA, TAM_SALA);

    printf("%d map.width\n", map.width);
    printf("%d map.h\n", map.height);
//     initMap(map);

    printf("Você está em uma sala com dimensões %d x %d. \n",
            enviroment.height,
            enviroment.width);

    printf("Nesta sala há %d buracos, %d monstros e uma barra de ouro. \n", 
            NUM_BURACO, 
            NUM_MONSTRO);

    printf("Seu objetivo é chegar na posição (%d,%d) em posse do ouro.",
            enviroment.height - 1,
            enviroment.width - 1);

    printf("Fazendo a menor quantidade de movimentos possível. \n");
    printf("Você começa na posição (0,0). Boa sorte! \n");

    char mov;
    while(!(agent.comOuro && agent.onde->row == enviroment.height-1 && agent.onde->col == enviroment.width-1))
    {
        printf("Score atual: %d \n", agent.score);
        printSimulation(agent,enviroment);
        sense(agent, &map);
        
        printPos(agent.onde->row, agent.onde->col, &map);
        printPos(agent.onde->row + 1, agent.onde->col, &map);
        printPos(agent.onde->row - 1, agent.onde->col, &map);
        printPos(agent.onde->row, agent.onde->col + 1, &map);
        printPos(agent.onde->row, agent.onde->col - 1, &map);

        printf("Para onde você deseja se mover? \n");
        scanf(" %c", &mov);
        
        if (mov == 's')
        {
            if (agent.onde->row < enviroment.height-1)
            {
                move(&agent,enviroment,&enviroment.grid[agent.onde->row+1][agent.onde->col]);
            }
        }

        if (mov == 'w')
        {
            if (agent.onde->row > 0)
            {
                move(&agent, enviroment, &enviroment.grid[agent.onde->row-1][agent.onde->col]);
            }
        }

        if (mov == 'd')
        {
            if (agent.onde->col < enviroment.width-1)
            {
                move(&agent, enviroment, &enviroment.grid[agent.onde->row][agent.onde->col+1]);
            }
        }

        if (mov == 'a')
        {
            if (agent.onde->col > 0)
            {
                move(&agent, enviroment,&enviroment.grid[agent.onde->row][agent.onde->col-1]);
            }
        }
    }

    printf("Score final: %d \n", agent.score);

    return 0;
}
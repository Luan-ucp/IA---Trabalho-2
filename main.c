#include <stdio.h>
#include <stdbool.h>
#include "agent.h"
#include "env.h"
#include <unistd.h>

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
    char movProx = '*';
    int i = 0, j = 0;
    while(!(agent.comOuro && agent.onde->row == enviroment.height-1 && agent.onde->col == enviroment.width-1))
    {
        movProx = '*';
        printf("Score atual: %d \n", agent.score);
        printSimulation(agent,enviroment);
        sense(agent, &map);
        
        // printPos(agent.onde->row, agent.onde->col, &map);
        // printPos(agent.onde->row + 1, agent.onde->col, &map);
        // printPos(agent.onde->row - 1, agent.onde->col, &map);
        // printPos(agent.onde->row, agent.onde->col + 1, &map);
        // printPos(agent.onde->row, agent.onde->col - 1, &map);

        // int i, j;
        // for(i=0; i < TAM_SALA; i++){
        //     for(j=0; j < TAM_SALA; j++){
                
        //         if(map.grid[i][j].seguro){
        //             printf("Seguro: (%d, %d)\n", i, j);
        //         }
        //         else{
        //             printf("Não-Seguro: (%d, %d)\n", i, j);
        //         }
        //     }
        // }

        printf("Para onde você deseja se mover? \n");
        scanf(" %c", &mov);

        // if(mov == 's' && map.grid[i][j].seguro && !agent.onde->row != TAM_SALA-1){
        //     mov = 'd';
        //     movProx = '*';
        // }

        // if(movProx == 's' && !map.grid[i][j].seguro){
        //     mov = movProx;
        // }

        // //se a 
        // if(movProx == 'd' && !map.grid[i][j].seguro){
        //     mov = 'a';
        //     movProx = 's';
        // }

        // //inicial, quando o agente está em 0,0
        // //sempre ele vai descer
        // if(map.grid[i][j].seguro && movProx == '*'){
        //     mov = 's';
        // }
        // //se o proximo mov for diferente de *, significa que houve alguma instrução pré-preparada
        // else if(movProx != '*'){
        //     mov = movProx;
        // }
        // //caso contrário, sobe um e marca a próxima intrução para a lateral a fim de mapear o 'ao redor'
        // else{
        //     mov = 'w';
        //     movProx = 'd';
        // }
        

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
        //sleep(3);
    }

    printf("Score final: %d \n", agent.score);

    return 0;
}
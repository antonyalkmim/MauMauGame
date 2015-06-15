#include <stdio.h>
#include "MauMau.h"

int main()
{

    MauMau game;
    int iaux,numPartidas;
    char naipe_aux,valor_aux,caux;
    Card card_aux;

    scanf("%i",&numPartidas); //ler numero de partidas

    scanf("%i",&iaux); //le numero de jogadores
    game.setNumJogadores(iaux); //registra o numero de jogadores

    //le as 104 cartas
    scanf("%c",&caux);//le a quebra de linha

    for(int i=0;i<numPartidas; i++){

        game.zeraJogo(); //reinicia o jogo, limpa o monte, lixo e as maos dos jogadores

        //le o novo baralho da rodada
        for(int j=0; j<104; j++){

            scanf("%c %c",&valor_aux,&naipe_aux);
            card_aux.setNaipe(naipe_aux);
            card_aux.setValor(valor_aux);
            game.insertCard(card_aux);

            scanf("%c",&caux);//le o espaco entre as cartas
        }

        game.distribuiCartas(); //distribui 5 cartas para cada jogador
        //game.run(); //executa o jogo
        game.run_com_saida(); //executa o jogo com as saidas do passo a passo

        //vencedor da rodada
        printf("Vencedor partida %i:Jogador %i\n",i+1,game.getVencedor().getIdPlayer());
    }


}


#include "List.h"
#include "Stack.h"
#include <stdlib.h>
#include "Card.h"
#include "Player.h"



#ifndef MAUMAU_H
#define MAUMAU_H

class MauMau{

    public:
    //private:
        int numJogadores;
        Stack<Card> monte;
        Stack<Card> lixo;
        List<Player> jogadores;
        char sentido;//'N' = Next e 'P' = Prev
        Player vencedor;

    public:
        MauMau(){
            this->sentido = 'N';
        }

        void zeraJogo(){

            //limpa o monte
            this->monte.clear();

            //limpa o lixo
            this->lixo.clear();

            //limpa as maos dos jogadores
            this->jogadores.Iterator = this->jogadores.begin();
            do{
                this->jogadores.getPosition()->cards.clear();
                this->jogadores.IteratorToNext();
            }while(this->jogadores.Iterator != this->jogadores.begin());

        }

        void setNumJogadores(int n){
            Player p;
            if(n <= 1 || n >=11)
            {
                printf("Numero de jogadores invalido!\n");
                exit(1);
            }
            this->numJogadores = n;
            for(int i=0;i<n;i++){
               // printf("%i\n",i);
                p.setIdPlayer(i);
                jogadores.Insert(p);
            }

        }

        bool insertCard(Card c){
            if(this->monte.push(c))
                return true;
            return false;
        }

        void distribuiCartas(){
            Card c;

            jogadores.Iterator = jogadores.begin();
            do{
                for(int i=0;i<5;i++){
                    this->monte.pop(&c);
                    jogadores.getPosition()->insertCard(c);
                }

                jogadores.IteratorToNext();
            }while(jogadores.Iterator!=jogadores.begin());

        }

        void mostrarCartasJogadores(){
            jogadores.Iterator = jogadores.begin();
            do{
                Player *p = jogadores.getPosition();

                printf("Cartas Jogador [%i]:\n",p->getIdPlayer());
                p->mostraCartas(); //mostra as cartas do jogador p
                printf("\n");

                jogadores.IteratorToNext();
            }while(jogadores.Iterator != jogadores.begin());
        }

        Player getVencedor(){
            return this->vencedor;
        }

        /*
         * EXECUTA O JOGO
         */
        void run(){

            //inicia rodada
            //jogador 0 joga 1 carta (sempre a maior carta)

            /*
             * Quando monte estiver vazio:
             * desempilha e guarda o topo do lixo em P
             * cria novo monte desempilhando cada carta do lixo e empilhando no monte
             * empilha P no lixo
            */

            //executa acoes referente ao tipo da carta jogada pelo jogador

            bool terminou = false; //flag que indicara se algum jogador esta sem cartas
            Card cardLixo,cardJogador,cardAcao,cardMonte,cardAux;


            this->jogadores.Iterator = this->jogadores.begin();//inicia a rodada com o jogador 1


            //primeiro jogador faz a primeira jogada
            this->jogarCarta(&cardJogador);
            this->lixo.push(cardJogador);
            this->executaAcaoCard(&cardJogador);

            this->proximoJogador();

            do{
                //executa o resto da rodada

                this->lixo.pop(&cardLixo);//retira o topo do lixo
                this->lixo.push(cardLixo); //devolve o topo do lixo

                //tenta retirar da mao do jogador
                if(this->jogarCarta(&cardLixo,&cardJogador)){
                    //aqui jogador tem a carta e ela esta armazenada em cardJogador
                    this->lixo.push(cardJogador); //joga a carta do jogador no lixo
                    cardAcao = cardJogador; //carta que executa as acoes no jogo
                }else{
                    this->comprarCarta(1);

                    //se a carta comprada puder ser jogada
                    if(this->jogarCarta(&cardLixo,&cardJogador)){
                        this->lixo.push(cardJogador);
                        cardAcao = cardJogador; //carta que executa as acoes no jogo
                    }else{
                        cardAcao.setValor('K'); //determina a carta de acao como uma carta neutra pra nao interferir nas acoes do jogo
                    }
                }

                if(jogadores.getPosition()->cards.isEmpty())
                {
                    terminou = true; //determina se houve ganhador, se jogador ficou sem cartas
                    this->vencedor = *jogadores.getPosition();
                }else{
                    //executa as acoes do jogo
                    executaAcaoCard(&cardAcao);

                    //apos a rodada, passa para o proximo jogador
                    this->proximoJogador();
                }

            }while(!terminou);

            /*
             *Quando uma rodada acaba o jogador que estiver com mais pontos sai da partida
             */
            this->tiraJogadorMaisPontos(); //tira da partida o jogador com mais pontos

        }


        /*
         * EXECUTA O JOGO IMPRIMINDO PASSO A PASSO
         */
        void run_com_saida(){

            //inicia rodada
            //jogador 0 joga 1 carta (sempre a maior carta)

            /*
             * Quando monte estiver vazio:
             * desempilha e guarda o topo do lixo em P
             * cria novo monte desempilhando cada carta do lixo e empilhando no monte
             * empilha P no lixo
            */

            //executa acoes referente ao tipo da carta jogada pelo jogador

            bool terminou = false; //flag que indicara se algum jogador esta sem cartas
            Card cardLixo,cardJogador,cardAcao,cardMonte,cardAux;

            //do{
                this->jogadores.Iterator = this->jogadores.begin();//inicia a rodada com o primeiro jogador

                printf("\n--------------\n");
                printf("ID Jogador: %i ",this->jogadores.getPosition()->getIdPlayer());
                this->jogadores.getPosition()->mostraCartas();

                //primeiro jogador faz a primeira jogada
                this->jogarCarta(&cardJogador);
                this->lixo.push(cardJogador);
                this->executaAcaoCard(&cardJogador);


                printf("\ncarta jogada: %c%c\n",cardJogador.getValor(),cardJogador.getNaipe());
                printf("\n--------------\n");


                this->proximoJogador();

                printf("\n");
                do{
                    //executa o resto da rodada

                    this->lixo.pop(&cardLixo);//retira o topo do lixo
                    this->lixo.push(cardLixo); //devolve o topo do lixo

                    printf("\n--------------\n");
                    printf("carta lixo: %c%c\n",cardLixo.getValor(),cardLixo.getNaipe());
                    printf("ID Jogador: %i ",this->jogadores.getPosition()->getIdPlayer());
                    this->jogadores.getPosition()->mostraCartas();

                    //tenta retirar da mao do jogador
                    if(this->jogarCarta(&cardLixo,&cardJogador)){
                        //aqui jogador tem a carta e ela esta armazenada em cardJogador
                        this->lixo.push(cardJogador); //joga a carta do jogador no lixo
                        cardAcao = cardJogador; //carta que executa as acoes no jogo
                    }else{
                        //printf("teve que comprar carta\n");
                        printf("\ntopo_monte:%c%c\n",this->monte.top->A.getValor(),this->monte.top->A.getNaipe());
                        this->comprarCarta(1);

                        //se a carta comprada puder ser jogada
                        if(this->jogarCarta(&cardLixo,&cardJogador)){
                            this->lixo.push(cardJogador);
                            cardAcao = cardJogador; //carta que executa as acoes no jogo
                        }else{
                            printf("\n");
                            cardAcao.setValor('K'); //determina a carta de acao como uma carta neutra pra nao interferir nas acoes do jogo
                        }
                    }

                    if(jogadores.getPosition()->cards.isEmpty())
                    {
                        terminou = true; //determina se houve ganhador, se jogador ficou sem cartas
                        this->vencedor = *jogadores.getPosition();
                    }

                    //terminou = jogadores.getPosition()->cards.isEmpty() ? true : false; // determina se o jogador ficou sem cartas

                    //this->jogadores.getPosition()->mostraCartas();
                    printf("\ncarta jogada: %c%c\n",cardAcao.getValor(),cardAcao.getNaipe());
                    printf("\n--------------\n");

                    //executa as acoes do jogo
                    executaAcaoCard(&cardAcao);



                    //apos a rodada, passa para o proximo jogador
                    this->proximoJogador();
                }while(!terminou);
                terminou = false; // ao comecar outra rodada ele seta a flag pra falso denovo

                /*
                 *Quando uma rodada acaba o jogador que estiver com mais pontos sai da partida
                 */
                this->tiraJogadorMaisPontos(); //tira da partida o jogador com mais pontos

        }


    private:
        void criaNovoMonte(){

            Card a,b;
            this->lixo.pop(&b); //armazena o topo do lixo

            while(!this->lixo.isEmpty()){
                this->lixo.pop(&a); //tira do lixo
                this->monte.push(a); //coloca no monte
            }

            this->lixo.push(b); //armazena o antigo topo do lixo devolta
        }

        void proximoJogador(){
            if(this->sentido=='E'){
                this->jogadores.IteratorToNext();
            }else{
                this->jogadores.IteratorToBack();
            }
        }

        void jogadorAnterior(){
            if(this->sentido=='E'){
                this->jogadores.IteratorToBack();
            }else{
                this->jogadores.IteratorToNext();
            }
        }

        void executaAcaoCard(Card *cardAcao){
            switch(cardAcao->getValor()){
                case 'A':
                        this->proximoJogador();
                        break;

                case 'G'://7
                        this->proximoJogador();
                        this->comprarCarta(2);
                        this->jogadorAnterior();
                        break;

                case 'I'://9
                    this->jogadorAnterior();
                    this->comprarCarta(3);
                    this->proximoJogador();

                case 'Q':
                    this->sentido = this->sentido == 'E' ? 'D' : 'E';
                    break;
            }
        }

        void comprarCarta(int n){
            Card a;

            for(int i=0;i<n;i++){
                this->monte.pop(&a);
                this->jogadores.getPosition()->cards.Insert(a);

                if(this->monte.isEmpty()){
                    this->criaNovoMonte();
                }
            }
        }

        bool jogarCarta(Card *cardLixo,Card *cardJogador){

            if(this->jogadores.getPosition()->cards.DeleteCard((int) cardLixo->getValor(),'v',cardJogador)){
                //retirou a carta pelo valor
                //printf("retirou por valor\n");
                return true;
            }else{

                if(this->jogadores.getPosition()->cards.DeleteCard((int) cardLixo->getNaipe(),'n',cardJogador)){
                    //retirou a carta pelo naipe
                    //printf("retirou por naipe\n");
                    return true;
                }
            }

            return false;
        }

        //joga carta quando e inicio de rodada e o monte esta vazio
        bool jogarCarta(Card *cardJogador){

            if(this->jogadores.getPosition()->cards.DeleteMaiorCarta(cardJogador)){
                //retirou maior carta
                return true;
            }

        }


        void tiraJogadorMaisPontos(){

            Player *P;
            int count = 0;
            int count_max = 0;
            int idMax = 0;

            this->jogadores.Iterator = this->jogadores.begin();

            do{
                P = this->jogadores.getPosition(); //pega o jogador que o iterator esta apontando
                P->cards.Iterator = P->cards.begin();

                do{
                    if(!P->cards.isEmpty()){
                        count += (int) P->cards.getPosition()->getValor();
                        P->cards.IteratorToNext();
                    }
                }while(P->cards.Iterator != P->cards.begin());

                if(count>count_max){
                    idMax = P->getIdPlayer();
                    count_max = count;
                }

                count = 0;
                this->jogadores.IteratorToNext();
            }while(this->jogadores.Iterator != this->jogadores.begin());

            //printf("jogador max:%i\n",idMax); //id do jogador que teve mais cartas na mao

            //tira o jogador com mais pontos, o ID dele esta armazenado com idMax
            this->jogadores.DeletePlayer(idMax);

        }

};

#endif // MAUMAU_H

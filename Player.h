#include "Card.h"
#include "List.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player{
    private:
        int idPlayer;

    public:
        List<Card> cards;

    public:
        Player(){}


        void setIdPlayer(int id){
            this->idPlayer = id;
        }

        int getIdPlayer(){
            return this->idPlayer;
        }

        bool insertCard(Card c){
            cards.Insert(c);
        }

        void mostraCartas(){
            this->cards.Iterator = this->cards.begin();
            do{

                char n = this->cards.getPosition()->getNaipe();
                char v = this->cards.getPosition()->getValor();
                printf("%c%c ",v,n);

                this->cards.IteratorToNext();
            }while(this->cards.Iterator != this->cards.begin());
        }


};

#endif // PLAYER_H

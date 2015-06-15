#ifndef CARD_H
#define CARD_H

class Card{
    public:
        char naipe;
        char valor;
        char type;

    public:
        Card(char n,char v){
            this->naipe = n;
            this->valor = v;
        }

        Card(){}

        void setNaipe(char n){
            this->naipe = n;
        }

        void setValor(char v){
            this->valor = v;
            switch(v){
                case 'Q': this->type = 'Q'; break;
                case 'A': this->type = 'A'; break;
                case 'G': this->type = 'G'; break;
                case 'I': this->type = 'J'; break;
                default: this->type = 'N'; break;
            }
        }

        char getNaipe(){
            return this->naipe;
        }

        char getValor(){
            return this->valor;
        }



};

#endif // CARD_H

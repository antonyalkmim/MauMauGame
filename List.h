#include <stdio.h>
#include "Node.h"

#ifndef LIST_H
#define LIST_H

template <class T>
class List{

    public:
        Node<T> *head;
        Node<T> *tail;
        Node<T> *Iterator;

        List(){
            head = NULL;
            Iterator = NULL;
        }


        bool Insert(T x){

            Node<T> *P = Node<T>::montaNo(x);
            if(!P) return false;

            //caso a lista estiver vazia ele insere no head
            if(!head)
            {
                head = P;
                head->next = head;
                head->prev = head;

                tail = head; //inicia o head e o tail na mesma posicao
                return true;
            }

            //insere sempre no tail
            P->prev = this->tail;
            P->next = this->head;
            this->head->prev = P;
            this->tail->next = P;
            tail = P;
            return true;

            /*
            //insere na frente do head
            P->prev = this->head;
            P->next = this->head->next;
            this->head->next->prev = P;
            this->head->next = P;

            this->tail = this->head->prev; //aponta o tail para o ultimo que no caso que o anterior ao head
            return true;
            */
        }

        bool DeleteCard(int key,char modo, T *x)
        {
            Node<T> *P; //ponteiro para armazenar o endereco onde vamos remover
            Node<T> *aux; //ponteiro para auxiliar na remocao do elemento no meio da lista

            //nao deleta nada caso a lista estiver vazia
            if(!head) return false;

            P = this->SearchICard(key,modo); //procura carta

            //se a busca nos retornar null quer dizer que o elemento nao existe na lista
            if(!P) return false;

            if(P==head){
                if(P==tail){
                    tail = NULL;
                    head = NULL;
                }else{
                    head = head->next;
                    tail->next = head;
                }
            }else{
                if(P==tail){
                    tail = tail->prev;
                    head->prev = tail;
                }
            }

            if(P==Iterator)
                Iterator = Iterator->prev;

            P->next->prev = P->prev;
            P->prev->next = P->next;

            *x = Node<T>::desmontaNo(P);
            return true;
        }

        bool DeleteMaiorCarta(T *x)
        {
            Node<T> *P; //ponteiro para armazenar o endereco onde vamos remover
            Node<T> *aux; //ponteiro para auxiliar na remocao do elemento no meio da lista

            //nao deleta nada caso a lista estiver vazia
            if(!head) return false;

            P = this->SearchIMaiorCard(); //procura carta

            //se a busca nos retornar null quer dizer que o elemento nao existe na lista
            if(!P) return false;

            if(P==head){
                if(P==tail){
                    tail = NULL;
                    head = NULL;
                }else{
                    head = head->next;
                    tail->next = head;
                }
            }else{
                if(P==tail){
                    tail = tail->prev;
                    head->prev = tail;
                }
            }

            if(P==Iterator)
                Iterator = Iterator->prev;

            P->next->prev = P->prev;
            P->prev->next = P->next;

            *x = Node<T>::desmontaNo(P);
            return true;
        }


        bool DeletePlayer(int key)
        {
            Node<T> *P; //ponteiro para armazenar o endereco onde vamos remover
            //Node<T> *aux; //ponteiro para auxiliar na remocao do elemento no meio da lista

            //nao deleta nada caso a lista estiver vazia
            if(!head) return false;

            P = this->SearchIPlayer(key); //procura jogador

            //se a busca nos retornar null quer dizer que o elemento nao existe na lista
            if(!P) return false;

            if(P==head){

                if(P==tail){
                    tail = NULL;
                    head = NULL;
                }else{
                    head = head->next;
                    tail->next = head;
                }
            }else{
                if(P==tail){
                    tail = tail->prev;
                    head->prev = tail;
                }
            }

            if(P==Iterator)
                Iterator = Iterator->prev;

            P->next->prev = P->prev;
            P->prev->next = P->next;

            //printf("id jogador delete: %i\n",P->A.getIdPlayer());

            //tem que saber o porque isso daki esta fazendo travar o PC
            Node<T>::desmontaNo(P);

            return true;
        }

        bool DeleteIterator(T *x){

            Node<T>* P = Iterator;

            if(!P)
                return false;

            if(P==head){
                if(P==tail){
                    tail = NULL;
                    head = NULL;
                }else{
                    head = head->next;
                    tail->next = head;
                }
            }else{
                if(P==tail){
                    tail = tail->prev;
                    head->prev = tail;
                }
            }

            P->next->prev = P->prev;
            P->prev->next = P->next;

            *x = Node<T>::desmontaNo(P);
            return true;

        }


        bool Search(int key, T *x)
        {
            for(Node<T> *P = head; P != NULL; P = P->next){
                if(P->A.id == key){
                    *x = P->A;
                    return true;
                }
            }
            return false; //nao achou o elemento
        }

        bool SearchPlayer(int key, T *x)
        {
            for(Node<T> *P = head; P != NULL; P = P->next){
                if(P->A.getIdPlayer() == key){
                    *x = P->A;
                    return true;
                }
            }
            return false; //nao achou o elemento
        }

        void mostrar(){
            Node<T> *P = head;

            do{
                printf("%i\n",P->A.getIdPlayer());
                P = P->next;
            }while(P!=head);

        }

        void mostrar(bool DIREITA){
            Node<T> *P = head;
            if(P)
            {
                printf("%i\n", P->A.getIdPlayer()); //mostra o que esta no head
                if(DIREITA)
                {//imprima a lista andando para a esquerda
                    while(P->prev != head)
                    {
                        P = P->prev;
                        printf("%i\n", P->A.getIdPlayer());
                    }
                }
                else
                {
                    //imprime a lista andando para a direita
                    while(P->next != head)
                    {
                        P = P->next;
                        printf("%i\n", P->A.getIdPlayer());
                    }
                }
            }
        }

        //verifica se a lista esta vazia
        bool isEmpty(){
            return (head==NULL);
        }

        //retorna o dado contido na posicao em que o Iterator se encontra
        T *getPosition(){
            return &(Iterator->A);
        }

        //inicio da lista
        Node<T>* begin(){
            return head;
        }

        //final da lista
        Node<T>* end(){
            return tail;
        }

        //iterator vai para a proxima posicao
        bool IteratorToNext(){
            if(Iterator)
                Iterator = Iterator->next;
            return Iterator;
        }

        //iterator vai para a posicao anterior
        bool IteratorToBack(){
            if(Iterator)
                Iterator = Iterator->prev;
            return Iterator;
        }

        //consertar metodo
        void clear(){
            Node<T> *P = head;
            Node<T> *Q;

            if(P){
                do{
                    Node<T>::desmontaNo(P);
                    P = P->next;
                }while(P != head);
            }

            head = NULL;
        }


    private:
        Node<T>* SearchI(int key)
        {
            Node<T> *P = head;

            if(P->A.id == key)
                return P;

            P = P->next;
            while(P->A.id != key && P->next != head)
                P = P->next;

            return P;
        }

        //procura maior carta
        Node<T>* SearchIMaiorCard()
        {
            Node<T> *P = head;
            Node<T> *max;

            max = P;

            while(P->next != head){
                P = P->next;

                if((int) P->A.getValor() > (int)max->A.getValor()){
                    max = P;
                }else{
                    if((int) P->A.getValor() == (int) max->A.getValor()){
                        if((int) P->A.getNaipe() < (int) max->A.getNaipe()){
                            max = P;
                        }
                    }
                }
            }

            return max;

        }


        //procura cartas
        //modo [v=valor|n=naipe]
        Node<T>* SearchICard(int key,char modo)
        {
            Node<T> *P = head;
            Node<T> *max;

            //procura carta
            if(modo == 'v'){
                max = NULL;

                if((int) P->A.getValor() == key){
                    max = P;
                }

                //acha o primeiro
                P = P->next;
                while((int) P->A.getValor() != key && P->next != head){
                    P = P->next;
                }

                //verifica se o loop parou porque encontrou uma carta
                if((int) P->A.getValor() == key){
                    if(max != NULL){
                        //verifica qual tem o naipe preferencial
                        if((int) P->A.getNaipe() < (int) max->A.getNaipe())
                            max = P;
                    }else{
                        max = P;
                    }
                }


                //se nao chegou ao final, verifica se existe outra carta com o mesmo valor
                while(P->next != head){
                    P = P->next;

                    if((int) P->A.getValor() == key){
                        if(max != NULL){
                            if((int) P->A.getNaipe() < (int)max->A.getNaipe())
                                max = P;
                        }else{
                            max = P;
                        }
                    }
                }

                P = max; // a carta certa vai estar no P


            }else{
                max = NULL;//determina a carta com o maior valor encontrado que pode ser jogada
                if((int) P->A.getNaipe() == key){
                    max = P;
                }

                //acha o primeiro
                P = P->next;
                while((int) P->A.getNaipe() != key && P->next != head){
                    P = P->next;
                }

                //verifica se encontrou uma carta
                if((int) P->A.getNaipe() == key){
                    if(max != NULL){
                        if((int) P->A.getValor() > (int) max->A.getValor())
                            max = P;
                    }else{
                        max = P;
                    }
                }

                if(P->next==head)//se chegou no final retorna o max que encontrou compativel com a key
                    return max;


                while(P->next != head){
                    P = P->next;

                    if((int) P->A.getNaipe() == key){
                        if(max != NULL){
                            if((int) P->A.getValor() > (int)max->A.getValor())
                                max = P;
                        }else{
                            max = P;
                        }
                    }
                }

                P = max; // a carta certa vai estar no P
            }

            return P;
        }

        //procura jogadores
        Node<T>* SearchIPlayer(int key){

            Node<T> *P = head;

            if(P->A.getIdPlayer() == key)
                return P;

            P = P->next;
            while(P->A.getIdPlayer() != key && P->next != head)
                P = P->next;

            return P;
        }


};

#endif // LIST_H

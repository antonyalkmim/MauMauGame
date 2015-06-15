#include "Node.h"

#ifndef STACK_H
#define STACK_H

#include <stdio.h>

template <class T>
class Stack
{
    public:
        Node<T> *top;

    public:
        Stack()
        {
            top = NULL;
        }

        bool push(T A)
        {
            Node<T> *p = Node<T>::montaNo(A);

            if(!p)
                return p;

            p->next = top;
            top=p;

            return true;
        }

        bool pop(T *A)
        {
            if(!top)
                return false;

            Node<T> *p = top->next;
            *A = Node<T>::desmontaNo(top);

            top = p;
            return true;
        }


        bool isEmpty(){
            return (top == NULL);
        }

        void listar(){
            Node<T> *P = this->top;
            while(P){
                printf("%c%c ",P->A.getValor(),P->A.getNaipe());
                P = P->next;
            }
        }

        void clear(){
            T aux;

            while(!this->isEmpty())
                this->pop(&aux);
        }

};

#endif // STACK_H

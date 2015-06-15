#ifndef NODE_H
#define NODE_H

template <class T>
class Node
{
    public:
        T A;
        int id;
        Node *next;
        Node *prev;

    public:
        static Node *montaNo(T X)
        {
            Node *p;
            p = new Node;
            if(!p) return p;
            p->A = X;
            p->next = NULL;
            p->prev = NULL;

            return p;
        }

        static T desmontaNo(Node *P)
        {
            T x = P->A;
            delete P;
            return x;
        }
};

#endif // NODE_H

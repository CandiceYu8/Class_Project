#ifndef CIR_LINK_H
#define CIR_LINK_H

typedef struct Node
{
    int data;
    struct Node *next;
    Node()
    {
        next = NULL;
    }
}NODE;

class Cir_Link
{
    public:
        Cir_Link();
        virtual ~Cir_Link();
        void Delete_Node();
        void Print_Node();
    private:
        NODE *head;
        NODE *tail;
        int n;
        int m;
};

#endif // CIR_LINK_H

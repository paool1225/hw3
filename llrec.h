#ifndef LLREC_H
#define LLREC_H
#include <cstdlib>

/**
 * Node struct for both problems
 */

struct Node
{
    int val;
    Node *next;

    Node(int v, Node* n) : val(v), next(n) {}
};


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);

template <typename Comp>
Node* llfilter(Node* head, Comp pred);


template <typename Comp>
Node* llfilter(Node* head, Comp pred)
{
    Node* n;
    
    if(head == NULL){
        return head;
    }
    Node* temp = head->next;
    if(!pred(head->val)){
        n = head;
        n->next = llfilter(temp, pred);
        return n;
    }
    else{
        n = llfilter(temp, pred);
        return n;
    }
}

#endif
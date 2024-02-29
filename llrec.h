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

/**
 * Divides the list into two lists based on the pivot value.
 * All nodes with values less than the pivot will be moved to the 'smaller' list,
 * and all nodes with values greater or equal to the pivot will be moved to the 'larger' list.
 * @param head Reference to the original list's head.
 * @param smaller Reference to the head of the resulting 'smaller' list.
 * @param larger Reference to the head of the resulting 'larger' list.
 * @param pivot The pivot value for division.
 */

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);
/**
 * Filters elements of the linked list based on a predicate and returns a new list.
 * The original list is not modified.
 * @param head Pointer to the head of the list to be filtered.
 * @param pred Predicate function that returns true for elements to be included.
 * @return Pointer to the head of the filtered list.
 */
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
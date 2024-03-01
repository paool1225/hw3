#include "llrec.h"

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
    if (!head) {
        smaller = larger = nullptr; 
        return;
    }

    Node* pivotNode = head; 
    head = head->next; 
    pivotNode->next = nullptr; 

    if (pivotNode->val <= pivot) {
        pivotNode->next = smaller; 
        smaller = pivotNode;
        llpivot(head, smaller->next, larger, pivot);
    } else {
        pivotNode->next = larger; 
        larger = pivotNode;
        llpivot(head, smaller, larger->next, pivot);
    }
}

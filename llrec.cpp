#include "llrec.h"

// llpivot Implementation
void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    Node* nextNode = head->next;
    if (head->val <= pivot) {
        smaller = head;
        llpivot(nextNode, smaller->next, larger, pivot);
        smaller->next = NULL; 
    } else {
        larger = head;
        llpivot(nextNode, smaller, larger->next, pivot);
        larger->next = NULL; 
    }

    head->next = NULL;
}

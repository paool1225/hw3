#include "llrec.h"


void appendToSmallerOrLarger(Node*& list, Node* node) {
    if (list == nullptr) {
        list = node;  
    } else if (list->next == nullptr) {
        list->next = node;  
    } else {
        appendToSmallerOrLarger(list->next, node);  
    }
}

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
    if (head == nullptr) {
        return; 
    }

    Node* nextNode = head->next;  
    head->next = nullptr;  

    if (head->val <= pivot) {
        appendToSmallerOrLarger(smaller, head);  
    } else {
        appendToSmallerOrLarger(larger, head);  
    }

    llpivot(nextNode, smaller, larger, pivot);  
}

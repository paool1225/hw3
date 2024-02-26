#include "llrec.h"

// Helper function to append nodes recursively
void appendToSmallerOrLarger(Node*& list, Node* node) {
    if (list == nullptr) {
        list = node;  // If the list is empty, make `node` the head
    } else if (list->next == nullptr) {
        list->next = node;  // If we're at the end of the list, append `node`
    } else {
        appendToSmallerOrLarger(list->next, node);  // Recursively find the end of the list
    }
}

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
    if (head == nullptr) {
        return;  // Base case: if head is nullptr, do nothing
    }

    Node* nextNode = head->next;  // Save the next node
    head->next = nullptr;  // Detach the current node from the list

    if (head->val <= pivot) {
        appendToSmallerOrLarger(smaller, head);  // Append to the smaller list
    } else {
        appendToSmallerOrLarger(larger, head);  // Append to the larger list
    }

    llpivot(nextNode, smaller, larger, pivot);  // Recursive call with the next node
}

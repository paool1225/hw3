#ifndef LLREC_H
#define LLREC_H

#include <cstddef> 

/**
 * Node struct for both problems
 */
struct Node {
    int val;
    Node *next;

    Node(int v, Node* n = nullptr) : val(v), next(n) {}
};

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);

template <typename Comp>
Node* llfilter(Node* head, Comp pred);

template <typename Comp>
Node* llfilter(Node* head, Comp pred) {
    if (head == nullptr) {
        return nullptr;
    }
    Node* filteredRest = llfilter(head->next, pred);
    if (pred(head->val)) {
        delete head;
        return filteredRest;
    } else {
        head->next = filteredRest;
        return head;
    }
}

#endif

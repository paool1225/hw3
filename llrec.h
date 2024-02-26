#ifndef LLREC_H
#define LLREC_H

// Ensure NULL is properly defined
#include <cstddef> // For std::nullptr_t

/**
 * Node struct for both problems
 */
struct Node {
    int val;
    Node *next;

    // Constructor
    Node(int v, Node* n = nullptr) : val(v), next(n) {}
};

// Function prototypes
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);

template <typename Comp>
Node* llfilter(Node* head, Comp pred);

// Implementation of llfilter in the header due to template requirement
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

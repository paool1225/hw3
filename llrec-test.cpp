#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

Node* readList(const char* filename);
void print(Node* head);
void dealloc(Node* head);

Node* readList(const char* filename) {
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if(!(ifile >> v)) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while(ifile >> v) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head) {
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head) {
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

struct IsOdd {
    bool operator()(int value) {
        return value % 2 != 0;
    }
};

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test llpivot
    Node* smaller = nullptr;
    Node* larger = nullptr;
    int pivot = 5;
    llpivot(head, smaller, larger, pivot);
    cout << "Smaller than or equal to " << pivot << ": ";
    print(smaller);
    cout << "Larger than " << pivot << ": ";
    print(larger);

    // Deallocate smaller and larger lists
    dealloc(smaller);
    dealloc(larger);

    // Re-read list for llfilter test
    head = readList(argv[1]);
    Node* filtered = llfilter(head, IsOdd());
    cout << "After filtering odd numbers: ";
    print(filtered);

    // Deallocate filtered list
    dealloc(filtered);

    return 0;
}

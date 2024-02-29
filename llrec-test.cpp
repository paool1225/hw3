#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

// Function prototypes for clarity
Node* readList(const char* filename);
void print(Node* head);
void dealloc(Node* head);

// Reads a list of integers from a file and creates a linked list
Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}
// Prints the values in the linked list
void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}
// Deallocates the memory used by the linked list
void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}


// Struct to check if an integer is odd
struct isOdd
{ 
    bool operator()(const int& val)
    {
        if (val % 2 == 1)
        {
            return true;
        }
        
        return false;
    }
};

// Struct to check if an integer is divisible by three
struct isDivisByThree
{ 
    bool operator()(const int& val)
    {
        if (val % 3 == 0)
        {
            return true;
        }
        
        return false;
    }
};


// Struct to check if an integer is less than ten
struct isLessThanTen
{ 
    bool operator()(const int& val)
    {
        if (val < 10)
        {
            return true;
        }
        
        return false;
    }
};

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }



    Node* head = readList(argv[1]);
    cout << "Original list: " << endl;
    print(head);

    
    isOdd c1;
    isDivisByThree c2;
    isLessThanTen c3;

    Node* g = llfilter(head, c1);
    cout << "Filtered if odd number list: " << endl;
    print(g);
    dealloc(head);

    head = readList(argv[1]);
    cout << "Original list: " << endl;
    print(head);

    Node* h = llfilter(head, c2);
    cout << "Filter if divisible by three list: " << endl;
    print(h);
    dealloc(head);

    head = readList(argv[1]);
    cout << "Original list: " << endl;
    print(head);

    Node* i = llfilter(head, c3);
    cout << "Filter if less than ten list: " << endl;
    print(i);
    dealloc(head);



    
    return 0;

}
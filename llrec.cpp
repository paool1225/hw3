#include "llrec.h"

//*llpivot Implementation//
void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot){
	smaller = NULL;
	larger = NULL;
	    if(head == NULL){
	return;
	}


	Node* temp = head->next;

	if(head->val <= pivot){
		smaller = head;
		smaller->next = NULL;
		head = NULL;
		llpivot(temp, smaller->next, larger, pivot);
	}
	else{
	    larger = head;
		larger->next = NULL;
		head = NULL;
		llpivot(temp, smaller, larger->next, pivot);
	}
}
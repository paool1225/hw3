#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};
//structure for operating events by time//
typedef struct EventLess {
         
         bool operator()(Event* e1, Event* e2) {
					return (e1->time < e2->time);
				
                }
} EventLess;
	
#endif

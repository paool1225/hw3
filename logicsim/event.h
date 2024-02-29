#ifndef EVENT_H
#define EVENT_H
#include "wire.h"
#include <cstdint> 

struct Event {
    uint64_t time; 
    Wire* wire;    
    char state;    
};

struct EventLess {
    bool operator()(const Event* lhs, const Event* rhs) const {
        if (lhs->time == rhs->time) {
            return lhs->wire->getId() > rhs->wire->getId(); // Prioritize wire with smaller ID
        }
        return lhs->time > rhs->time; // Prioritize earlier time
    }
};


#endif 

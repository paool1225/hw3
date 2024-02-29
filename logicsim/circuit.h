#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <vector>
//included heal.h from hw3 file//
#include "../heap.h"
#include "event.h"
#include "gate.h"

class Circuit 
{
	public:
		Circuit();
		~Circuit();
		void test();
		bool advance(std::ostream&);
		void run(std::ostream&);
    bool parse(const char*);
    void startUml(std::ostream&);
    void endUml(std::ostream&);
		
	private:
		uint64_t m_current_time;
        std::vector<Gate*> m_gates;
        std::vector<Wire*> m_wires;
        Heap<Event*, EventLess> m_pq; 

};

#endif
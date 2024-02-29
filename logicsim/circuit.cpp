#include <vector>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../heap.h" 
#include "wire.h"
#include "gate.h"
#include "circuit.h"
#include "event.h"

Circuit::Circuit() : m_current_time(0) {}

Circuit::~Circuit() {
    for (auto i : m_wires) {
        delete i;
    }
    for (auto i : m_gates) {
        delete i;
    }
}

void Circuit::test() {
    // Initial test setup, you may need to adjust based on the test circuit
    m_wires.push_back(new Wire(0, "input A"));
    m_wires.push_back(new Wire(1, "input B"));
    m_wires.push_back(new Wire(2, "output"));

    Gate* g = new And2Gate(m_wires[0], m_wires[1], m_wires[2]);
    m_gates.push_back(g);

    // Example events to start the simulation
    m_pq.push(new Event {0, m_wires[0], '0'});
    m_pq.push(new Event {0, m_wires[1], '1'});
    m_pq.push(new Event {4, m_wires[0], '1'});
    m_pq.push(new Event {6, m_wires[1], '0'});
}

bool Circuit::parse(const char* fname) {
    std::ifstream inFile(fname);
    if (!inFile) {
        std::cerr << "Failed to open file: " << fname << std::endl;
        return false;
    }

    std::string line;
    while (getline(inFile, line)) {
        if (line == "WIRES") {
            // Handle wire definitions
            int n;
            inFile >> n;
            std::string dummyLine;
            getline(inFile, dummyLine); // To consume the newline character after reading n
            for (int i = 0; i < n; ++i) {
                getline(inFile, line);
                std::istringstream wireStream(line);
                int id;
                std::string name;
                char delimiter;
                wireStream >> id >> delimiter; // Assuming a comma ',' or some delimiter is used
                std::getline(wireStream, name);
                m_wires.push_back(new Wire(id, name));
            }
        } else if (line == "GATES") {
            // Handle gate definitions
            int n;
            inFile >> n;
            std::string dummyLine;
            getline(inFile, dummyLine); // To consume the newline character after reading n
            for (int i = 0; i < n; ++i) {
                getline(inFile, line);
                std::istringstream gateStream(line);
                std::string gateType;
                int input1, input2, output;
                char delimiter;

                gateStream >> gateType;

                if (gateType == "AND2" || gateType == "OR2") {
                    gateStream >> input1 >> delimiter >> input2 >> delimiter >> output;
                    if (gateType == "AND2") {
                        m_gates.push_back(new And2Gate(m_wires[input1], m_wires[input2], m_wires[output]));
                    } else if (gateType == "OR2") {
                        m_gates.push_back(new Or2Gate(m_wires[input1], m_wires[input2], m_wires[output]));
                    }
                } else if (gateType == "NOT") {
                    gateStream >> input1 >> delimiter >> output;
                    m_gates.push_back(new NotGate(m_wires[input1], m_wires[output]));
                }
                // Add additional gate types as needed
            }
        } else if (line == "INJECT") {
            // Handle event injections
            int n;
            inFile >> n;
            std::string dummyLine;
            getline(inFile, dummyLine); // Consume the line
            for (int i = 0; i < n; ++i) {
                getline(inFile, line);
                std::istringstream eventStream(line);
                int time, wireId;
                char state, delimiter;
                eventStream >> time >> delimiter >> wireId >> delimiter >> state;
                m_pq.push(new Event{static_cast<uint64_t>(time), m_wires[wireId], state});
            }
        }
    }
    return true;
}



bool Circuit::advance(std::ostream& os) {
    if (m_pq.empty()) return false;

    m_current_time = m_pq.top()->time;
    bool initialPrinted = false; // Flag to track if initial wire definitions and timestamp header are printed
    bool stateChanged = false;   // Flag to track if any wire state has changed

    // Process events at the current timestamp
    while (!m_pq.empty() && m_pq.top()->time == m_current_time) {
        Event* e = m_pq.top();
        m_pq.pop();

        // Log the change immediately
        std::string changeLog = e->wire->setState(e->state, m_current_time);
        if (!changeLog.empty()) {
            stateChanged = true; // Set the flag indicating a state change
        }

        delete e;
    }

    // Start the UML diagram if there were state changes or at the initial timestamp
    if (stateChanged || !initialPrinted) {
        startUml(os);
        os << "@" << m_current_time << std::endl;
        initialPrinted = true;
    }

    // Print wire states if there were state changes or at the initial timestamp
    if (stateChanged) {
        for (auto w : m_wires) {
            if (!w->getName().empty()) {
                os << "W" << w->getId() << " is ";
                if (w->getState() == 'X') {
                    os << "X" << std::endl;
                } else {
                    os << (w->getState() == '0' ? "low" : "high") << std::endl;
                }
            }
        }
    }

    // Update gates and push new events
    for (auto& gate : m_gates) {
        Event* e = gate->update(m_current_time);
        if (e != nullptr) {
            m_pq.push(e);
        }
    }

    // End the UML diagram if it was started
    if (initialPrinted) {
        endUml(os);
    }

    // Return true if there were state changes or at the initial timestamp
    return stateChanged || !initialPrinted;
}




void Circuit::run(std::ostream& os) {
    while (advance(os)) {}
}

void Circuit::startUml(std::ostream& os) {
    os << "@startuml" << std::endl;
    for (auto w : m_wires) {
        if (!w->getName().empty()) {
            os << "binary \"" << w->getName() << "\" as W" << w->getId() << std::endl;
        }
    }
    os << std::endl << "@0" << std::endl;
    for (auto w : m_wires) {
        if (!w->getName().empty()) {
            os << "W" << w->getId() << " is {low,high}" << std::endl;
        }
    }
    os << std::endl;
}

void Circuit::endUml(std::ostream& os) {
    os << "@enduml" << std::endl;
}

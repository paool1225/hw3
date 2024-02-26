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
            // Handle gate definitions, similar approach for parsing
        } else if (line == "INJECT") {
            // Handle event injections, ensuring events are queued correctly
        }
    }
    return true;
}


bool Circuit::advance(std::ostream& os) {
    if (m_pq.empty()) return false;

    m_current_time = m_pq.top()->time;
    std::stringstream ss;
    ss << "@" << m_current_time << std::endl;
    bool updated = false;

    while (!m_pq.empty() && m_pq.top()->time == m_current_time) {
        Event* e = m_pq.top();
        m_pq.pop();

        std::string changeLog = e->wire->setState(e->state, m_current_time);
        if (!changeLog.empty()) {
            ss << changeLog << std::endl;
            updated = true;
        }
        delete e;
    }

    if (updated) {
        os << ss.str();
    }

    for (auto& gate : m_gates) {
        Event* e = gate->update(m_current_time);
        if (e != nullptr) {
            m_pq.push(e);
        }
    }

    return true;
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

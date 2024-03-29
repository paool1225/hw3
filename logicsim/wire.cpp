#include <set>
#include <iostream>
#include <string>
#include <sstream>

#include "wire.h"

Wire::Wire(int id, std::string name) : m_state('X'), m_name(name), m_id(id){}

//Returns the current state of the wire
const char& Wire::getState() const
{
    return m_state;
}
//Gets the Name of the Wire
std::string Wire::getName() const
{
    return m_name;
}
//Gets the ID for the wire
int Wire::getId() const
{
    return m_id;
}
//Sets the state of the wire
std::string Wire::setState(char s, uint64_t current_time) {
    std::stringstream ss("");
    
    std::set<char> valid_states {'0','1','X'};
    //Checks if the given state is valid
    if(valid_states.find(s) != valid_states.end()) {
        if(m_state != s && m_name != "") {
            std::string uml_state("");
            if(s == '0') uml_state = "low";
            if(s == '1') uml_state = "high";
            if(s == 'X') uml_state = "{low,high}";
            ss << "W" << m_id << " is " << uml_state << std::endl;
        }
            
        m_state = s;
    }
    return ss.str();
}

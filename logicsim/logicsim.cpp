#include <iostream>
#include <sstream>
#include <string>

#include "circuit.h"

using namespace std;

int main(int argc, char* argv[]) {
    Circuit C;
    
    if (argc == 2) { // Check if exactly one additional argument is provided
        stringstream ss; // Move the stringstream declaration inside the if block
        if (C.parse(argv[1])) {
            C.startUml(ss);
            C.run(ss);
            C.endUml(ss);
            cout << ss.str() << endl;
        }
    } else {
        cout << "Please provide a circuit file to simulate." << endl;
        return 1;
    }
    
    return 0;
}

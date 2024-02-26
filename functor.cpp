#include <iostream>
#include <string>
#include <stdexcept>

struct AlphaStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return lhs < rhs;
    }
};

struct LengthStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return lhs.size() < rhs.size();
    }
};

template <class Comparator>
void DoStringCompare(const std::string& s1, const std::string& s2, Comparator comp) {
    std::cout << "Comparison result: " << comp(s1, s2) << std::endl;
}

int main() {
    std::string s1 = "Blue";
    std::string s2 = "Red";

    AlphaStrComp comp1;
    LengthStrComp comp2;

    std::cout << "Comparing \"" << s1 << "\" and \"" << s2 << "\" using AlphaStrComp:" << std::endl;
    DoStringCompare(s1, s2, comp1);

    std::cout << "Comparing \"" << s1 << "\" and \"" << s2 << "\" using LengthStrComp:" << std::endl;
    DoStringCompare(s1, s2, comp2);

    return 0;
}

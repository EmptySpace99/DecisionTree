#include "string-utility.h"

void removeBrackets(string& s)
{
    size_t found1 = s.find_first_of("(");
    size_t found2 = s.find_first_of(")");

    while (found1!=string::npos){
        s.erase(found1,1);
        found1 = s.find_first_of("(");
    }

    while (found2!=string::npos){
        s.erase(found2,1);
        found2 = s.find_first_of(")");
    }
}

void removeCommas(string& s)
{
    size_t found = s.find_first_of(",");

    while (found!=string::npos){
        s.erase(found,1);
        found = s.find_first_of(",");
    }
}

void removeBlanksandOther(string& s)
{
    size_t found = s.find_first_of(" ");

    while (found!=string::npos){
        s.erase(found,1);
        found = s.find_first_of(" ");
    }
    removeBrackets(s);
    removeCommas(s);
}

int str2int(const string &s) {// convert string in number
    istringstream itmp(s);
    int n;
    itmp >> n;
    return n;
}

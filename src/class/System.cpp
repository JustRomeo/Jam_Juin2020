#include <fstream>
#include <iostream>
#include "System.hpp"
#include "Exception.hpp"

System::System() {}
System::~System() {}

vector<string> System::openfile(string filepath) {
    string line;
    ifstream file;
    vector<string> load;

    file.open(filepath);
    if (!file.is_open())
        throw (Exception("Can't open file to load"));
    while (getline(file, line))
        load.push_back(line);
    file.close();
    line.clear();
    return (load);
}
#ifndef REFLECTANCETABLE_H
#define REFLECTANCETABLE_H

#include <stdio.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>


using namespace std;
class ReflectanceTable
{

public:
    std::map<string, map<string, vector<float> > > lookup_table;
    void init_table();
    const std::map<string, map<string, vector<float> > > get_table();
    const vector<float> get_comp(string material, string comp);
};
#endif // REFLECTANCETABLE_H

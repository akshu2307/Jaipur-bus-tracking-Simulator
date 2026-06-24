#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include "Location.h"
using namespace std;

class Route {
public:
    Location* from;
    Location* to;

    string busNo;
    float time;
    float cost;

    Route(Location* f, Location* t, string b, float ti, float c)
    {
        from = f;
        to = t;
        busNo = b;
        time = ti;
        cost = c;
    }
};

#endif

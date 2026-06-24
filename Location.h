#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
using namespace std;

class Route;

class Location {
public:
    string name;
    float lat, lon;

    vector<Route*> routes;

    bool visited;
    Location* previous;
    float dist;

    Location(string n = "", float la = 0, float lo = 0)
    {
        name = n;
        lat = la;
        lon = lo;

        visited = false;
        previous = NULL;
        dist = 1e9;
    }

    void reset()
    {
        visited = false;
        previous = NULL;
        dist = 1e9;
    }
};

#endif
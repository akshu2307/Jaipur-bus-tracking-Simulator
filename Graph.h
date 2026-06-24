#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include "Location.h"
#include "Route.h"
using namespace std;

class Compare {
public:
    bool operator()(Location* a, Location* b)
    {
        return a->dist > b->dist;
    }
};

class Graph {
public:
    vector<Location*> cities;
    vector<Route*> routes;
    unordered_map<string, Location*> mp;

    Graph(string cityFile, string routeFile)
    {
        loadCities(cityFile);
        loadRoutes(routeFile);
    }

  void loadCities(string file)
{
    ifstream fin(file);

    if (!fin)
    {
        cout << "Cannot open file: " << file << endl;
        return;
    }

    string line;

    while (getline(fin, line))
    {
        stringstream ss(line);

        string name, latStr, lonStr;

        getline(ss, name, ',');
        getline(ss, latStr, ',');
        getline(ss, lonStr, ',');

        Location* loc = new Location(
            name,
            stof(latStr),
            stof(lonStr)
        );

        cities.push_back(loc);
        mp[name] = loc;
    }

    cout << "Cities loaded: " << cities.size() << endl;
}

   void loadRoutes(string file)
{
    ifstream fin(file);

    if (!fin)
    {
        cout << "Cannot open file: " << file << endl;
        return;
    }

    string line;

    while (getline(fin, line))
    {
        stringstream ss(line);

        string from, to, timeStr, costStr, bus;

        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, timeStr, ',');
        getline(ss, costStr, ',');
        getline(ss, bus, ',');

        if (!mp.count(from) || !mp.count(to))
            continue;

        Route* r = new Route(
            mp[from],
            mp[to],
            bus,
            stof(timeStr),
            stof(costStr)
        );

        mp[from]->routes.push_back(r);
        routes.push_back(r);
    }

    cout << "Routes loaded: " << routes.size() << endl;
}

    float geoDistance(Location* a, Location* b)
    {
        const float R = 6371;

        float dLat = (b->lat - a->lat) * M_PI / 180.0;
        float dLon = (b->lon - a->lon) * M_PI / 180.0;

        float lat1 = a->lat * M_PI / 180.0;
        float lat2 = b->lat * M_PI / 180.0;

        float x = sin(dLat/2)*sin(dLat/2) +
                  sin(dLon/2)*sin(dLon/2)*cos(lat1)*cos(lat2);

        float c = 2 * atan2(sqrt(x), sqrt(1-x));

        return R * c;
    }

    float getWeight(Route* r, int mode)
    {
        if (mode == 1) return r->cost;              // cheapest
        if (mode == 2) return geoDistance(r->from, r->to); // geo
        return r->time;                             // fastest
    }

    Location* getCity(string name)
    {
        if (mp.count(name)) return mp[name];
        return NULL;
    }

    void dijkstra(string start, int mode)
{
    for (auto c : cities)
        c->reset();

    Location* src = getCity(start);

    if (src == nullptr)
    {
        cout << "ERROR: Source city not found: " << start << endl;
        return;
    }

    src->dist = 0;

    priority_queue<Location*, vector<Location*>, Compare> pq;
    pq.push(src);

    while (!pq.empty())
    {
        Location* curr = pq.top();
        pq.pop();

        for (auto r : curr->routes)
        {
            if (r == nullptr || r->to == nullptr)
                continue;

            Location* nxt = r->to;
            float w = getWeight(r, mode);

            if (curr->dist + w < nxt->dist)
            {
                nxt->dist = curr->dist + w;
                nxt->previous = curr;
                pq.push(nxt);
            }
        }
    }
}

vector<Location*> getPath(string dest)
{
    vector<Location*> path;

    Location* end = getCity(dest);

    if (end == nullptr)
    {
        cout << "ERROR: Destination city not found: "
             << dest << endl;
        return path;
    }

    while (end != nullptr)
    {
        path.push_back(end);
        end = end->previous;
    }

    reverse(path.begin(), path.end());
    return path;
    }
};

#endif
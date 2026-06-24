#include <iostream>
#include <vector>
#include <filesystem>
#include "Graph.h"

using namespace std;

int main()
{
    Graph g("cities.csv", "routes.csv");

    if (g.cities.empty())
    {
        cout << "No cities loaded!" << endl;
        return 0;
    }

    while (true)
    {
        cout << "\n========== AVAILABLE CITIES ==========\n";

        for (int i = 0; i < g.cities.size(); i++)
        {
            cout << i + 1 << ". "
                 << g.cities[i]->name << endl;
        }

        int srcIndex, destIndex;

        cout << "\nEnter Source City Number: ";
        cin >> srcIndex;

        cout << "Enter Destination City Number: ";
        cin >> destIndex;

        if (srcIndex < 1 || srcIndex > g.cities.size() ||
            destIndex < 1 || destIndex > g.cities.size())
        {
            cout << "\nInvalid city selection!\n";
            continue;
        }

        string src = g.cities[srcIndex - 1]->name;
        string dest = g.cities[destIndex - 1]->name;

        int mode;

        cout << "\n1. Fastest Route";
        cout << "\n2. Cheapest Route";
        cout << "\n3. Geo Shortest Route";
        cout << "\nChoose Option: ";
        cin >> mode;

        if (mode < 1 || mode > 3)
        {
            cout << "\nInvalid option!\n";
            continue;
        }

        g.dijkstra(src, mode - 1);

        vector<Location*> path = g.getPath(dest);

        if (path.empty())
        {
            cout << "\nNo route found!\n";
            continue;
        }

        cout << "\n========== ROUTE ==========\n";

        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i]->name;

            if (i != path.size() - 1)
            {
                for (auto r : path[i]->routes)
                {
                    if (r->to == path[i + 1])
                    {
                        cout << " --[" << r->busNo << "]--> ";
                        break;
                    }
                }
            }
        }

        cout << "\n";

        if (mode == 1)
            cout << "\nTotal Time: "
                 << path.back()->dist
                 << " minutes\n";

        else if (mode == 2)
            cout << "\nTotal Cost: Rs "
                 << path.back()->dist
                 << "\n";

        else
            cout << "\nTotal Distance: "
                 << path.back()->dist
                 << " km\n";

        char again;

        cout << "\nSearch another route? (y/n): ";
        cin >> again;

        if (again == 'n' || again == 'N')
            break;
    }

    cout << "\nThank you for using Travel Planner!\n";

    return 0;
}

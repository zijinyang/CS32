#include "tp.h"
#include "fm.h"
#include <list>
#include <queue>
#include <unordered_map>
#include <set>
#include <algorithm>

#include <iostream>

using namespace std;

static const FlightSegment nullfs("", 0, "", "", 0, 0);

void TravelPlanner::add_preferred_airline(string airline)
{
    m_preferred_airlines.insert(airline); 
}

//for A* algorithm
struct Node
{
    Node(const FlightSegment& fs) : parent(nullptr), f(0), h(0), g(0), fs(fs){}
    Node(Node* parent, string name, const FlightSegment& fs) : parent(parent), name(name), fs(fs) {}

    // Node(Node* parent, string name, int flightNumber,double g, double h, double f) : parent(parent), name(name), f(f), h(h), g(g) {}
    Node* parent;
    string name;
    FlightSegment fs;
    // int flightNumber; //connection from parent to this node
    double f, h, g; 
};

struct CompareNode
{
    bool operator()(Node* lhs, Node* rhs)
    {
        return lhs->f > rhs->f;
    }
};

// bool operator==(const Node& lhs, const Node& rhs)
// {
//     return lhs.name == rhs.name;
// }

bool TravelPlanner::plan_travel(string source_airport, string destination_airport, int start_time, Itinerary& itinerary) const
{
    //open and closed lists
    priority_queue<Node*, vector<Node*>, CompareNode> open; // min heap
    unordered_map<string, Node*> open_map; //track if airport is in open 
    unordered_map<string, Node*> closed;

    list<Node*> toDelete;

    //initialize start node
    Node* start = new Node(nullfs);
    start->name = source_airport;
    start->g = 0;
    get_airport_db().get_distance(source_airport, destination_airport, start->h);
    start->f = start->g + start->h;

    open.push(start);
    open_map[start->name] = start;
    toDelete.push_back(start);

    bool found = false;

    while(!open.empty())
    {
        Node* current = open.top();

        if(current->name == destination_airport)
        {
            while(current->parent != nullptr)
            {
                itinerary.flights.push_back(current->fs);
                current = current->parent;
            }
            const FlightSegment& last = *itinerary.flights.begin();
            if(last.departure_time + last.duration_sec - start_time > get_max_duration())
            {
                itinerary.flights.clear();
                found = false;
            }else
            {
                found = true; 
                reverse(itinerary.flights.begin(),itinerary.flights.end());
                itinerary.total_duration = last.departure_time + last.duration_sec - start_time;
                itinerary.source_airport = source_airport;
                itinerary.destination_airport = destination_airport;
            }
            break;
        }

        // Check if this node is outdated:
        if (open_map.find(current->name) != open_map.end() && open_map[current->name] != current) {
            continue;
        }

        open.pop();
        // delete open_map[current->name];
        open_map.erase(current->name);

        closed[current->name] = current;

        //get all possible starting flights
        vector<FlightSegment> flights;
        vector<FlightSegment> temp_flights;
        int next_start_time = current->parent == nullptr ? start_time : current->fs.departure_time + current->fs.duration_sec + get_min_connection_time(); // get correct starting time 
        temp_flights = get_flight_manager().find_flights(current->name, next_start_time, next_start_time + get_max_layover());

        //only get flights from preferred airlines
        if(m_preferred_airlines.empty())
            flights = temp_flights;
        else
        {
            for(FlightSegment fs : temp_flights)
            {
                if(m_preferred_airlines.find(fs.airline) != m_preferred_airlines.end())
                {
                    flights.push_back(fs);
                }
            }
        }


        //get all neighbors
        for(FlightSegment &fs : flights)
        {
            if(closed.find(fs.destination_airport) != closed.end()) //already evaluated 
            {
                continue;
            }
            
            double tentative_g = current->g + fs.duration_sec;
            
            // double tentative_g = fs.duration_sec + fs.departure_time - start_time;
            if((open_map.find(fs.destination_airport) == open_map.end()) || tentative_g < open_map[fs.destination_airport]->g) //not in open
            {
                Node* neighbor = new Node(
                    current,
                    fs.destination_airport,
                    fs
                );
                toDelete.push_back(neighbor);
                neighbor->g = tentative_g;
                get_airport_db().get_distance(neighbor->name, destination_airport, neighbor->h);
                neighbor->f = neighbor->g + neighbor->h;

                open.push(neighbor);
                open_map[fs.destination_airport] = neighbor;
            }
        }
    }

    for(Node* n : toDelete){
        delete n;
    }

    if(!found)
        return false;
    else
        return true;
};


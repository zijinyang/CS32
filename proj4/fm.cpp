#include "fm.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

bool operator<(const FlightSegment& lhs, const FlightSegment& rhs)
{
    if(lhs.departure_time < rhs.departure_time)
        return true;
    if(lhs.departure_time == rhs.departure_time)
    {
        if(lhs.flight_no < rhs.flight_no)
            return true;
    }
    return false;
}

bool operator>(const FlightSegment& lhs, const FlightSegment& rhs)
{
    if(lhs.departure_time > rhs.departure_time)
        return true;
    if(lhs.departure_time == rhs.departure_time)
    {
        if(lhs.flight_no > rhs.flight_no)
            return true;
    }
    return false; 
}


bool operator==(const FlightSegment& lhs, const FlightSegment& rhs)
{
    return lhs.departure_time == rhs.departure_time && lhs.flight_no == rhs.flight_no;
}

bool FlightManager::load_flight_data(std::string filename)
{
    // Clear existing data to prevent memory leaks
    m_flights.clear();

    ifstream file(filename);
    if (!file)
        return false;
    
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> tokens;
        string token;

        while (getline(ss, token, ','))
        {
            tokens.push_back(token);
        }

        if (tokens.size() != 7) // Ensure the line has exactly 7 tokens
            continue;

        string name = tokens[0];
        int number = stoi(tokens[1]);
        string source = tokens[2];
        string destination = tokens[3];
        int departure = stoi(tokens[4]);
        int arrival = stoi(tokens[5]);
        int duration = stoi(tokens[6]);

        FlightSegment seg(name, number, source, destination, departure, duration);
        m_flights[source].insert(seg);
    }
    return true;
}

vector<FlightSegment> FlightManager::find_flights(string source_airport, int start_time, int end_time) const
{
    vector<FlightSegment> flights;
    auto i = m_flights.find(source_airport); 
    if(i == m_flights.end())
        return flights;
    typename BSTSet<FlightSegment>::SetIterator it = i->second.find_first_not_smaller(FlightSegment("", 0, "", "", start_time, 0));
    const  FlightSegment *next = it.get_and_advance();
    while( next != nullptr ) 
    {
        if(next->departure_time >= end_time)
        {
            break;
        }
        flights.push_back(*next);
        next =  it.get_and_advance();
    }
    return flights;
}
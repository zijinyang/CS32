#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "bstset.h"
#include "provided.h"

class FlightManager : public FlightManagerBase {
private:
    struct FlightKey {
        int departure_time;
        FlightSegment flight;

        bool operator<(const FlightKey& other) const {
            return departure_time < other.departure_time;
        }

        bool operator<=(const FlightKey& other) const {
            return departure_time <= other.departure_time;
        }
    };

    std::map<std::string, BSTSet<FlightKey>> flights_by_airport;

public:
    bool load_flight_data(std::string filename) override {
        std::ifstream file(filename);
        if (!file) return false;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string airline, src, dest, flight_num_str, dep_str, arr_str, dur_str;
            int flight_num, dep_time, arr_time, duration;

            std::getline(ss, airline, ',');
            std::getline(ss, flight_num_str, ',');
            std::getline(ss, src, ',');
            std::getline(ss, dest, ',');
            std::getline(ss, dep_str, ',');
            std::getline(ss, arr_str, ',');
            std::getline(ss, dur_str, ',');

            flight_num = std::stoi(flight_num_str);
            dep_time = std::stoi(dep_str);
            arr_time = std::stoi(arr_str);
            duration = std::stoi(dur_str);

            FlightSegment flight = { airline, flight_num, src, dest, dep_time, duration };
            flights_by_airport[src].insert({ dep_time, flight });
        }

        return true;
    }

    std::vector<FlightSegment> find_flights(std::string source_airport, int start_time, int end_time) const override {
        std::vector<FlightSegment> result;
        auto it = flights_by_airport.find(source_airport);
        if (it == flights_by_airport.end()) return result;

        auto flight_it = it->second.find_first_not_smaller(FlightKey{ start_time, FlightSegment("", 0, "", "", 0, 0) });
        const FlightKey* p;

        while ((p = flight_it.get_and_advance()) != nullptr) {
            if (p->departure_time > end_time) break;  // **Allow flights exactly at end_time**

            if (p->departure_time >= start_time) {  // **Ensure we don't exclude exact departures**
                result.push_back(p->flight);
            }
        }

        return result;
    }
};

#endif // FLIGHTMANAGER_H

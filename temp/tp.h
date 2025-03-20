#ifndef TRAVELPLANNER_H
#define TRAVELPLANNER_H

#include <queue>
#include <unordered_map>
#include <iostream>
#include <climits>
#include "provided.h"
#include "fm.h"

class TravelPlanner : public TravelPlannerBase {
private:
    const FlightManagerBase& fm;
    const AirportDB& adb;
    std::vector<std::string> preferred_airlines;

    struct FlightState {
        std::vector<FlightSegment> path;
        int total_duration;
        int arrival_time;
        std::string airport;

        bool operator>(const FlightState& other) const {
            return total_duration > other.total_duration;
        }
    };

public:
    TravelPlanner(const FlightManagerBase& flight_manager, const AirportDB& airport_db)
        : TravelPlannerBase(flight_manager, airport_db), fm(flight_manager), adb(airport_db) {}

    void add_preferred_airline(std::string airline) override {
        preferred_airlines.push_back(airline);
    }

    bool plan_travel(std::string source, std::string destination, int start_time, Itinerary& itinerary) const override {
        std::priority_queue<FlightState, std::vector<FlightState>, std::greater<>> pq;
        std::unordered_map<std::string, int> best_time;
        pq.push({ {}, 0, start_time, source });

        while (!pq.empty()) {
            FlightState current = pq.top();
            pq.pop();

            if (current.airport == destination) {
                itinerary.source_airport = source;
                itinerary.destination_airport = destination;
                itinerary.total_duration = current.total_duration;
                itinerary.flights = current.path;
                return true;
            }

            int min_connection_time = 3600;
            int min_departure = current.arrival_time + min_connection_time;

            auto flights = fm.find_flights(current.airport, min_departure, INT_MAX);

            for (const auto& flight : flights) {
                int new_duration = current.total_duration + (flight.departure_time - current.arrival_time) + flight.duration_sec;

                if (best_time.find(flight.destination_airport) == best_time.end() || new_duration < best_time[flight.destination_airport]) {
                    best_time[flight.destination_airport] = new_duration;
                    pq.push({ current.path, new_duration, flight.departure_time + flight.duration_sec, flight.destination_airport });
                }
            }
        }

        return false;
    }
};

#endif // TRAVELPLANNER_H
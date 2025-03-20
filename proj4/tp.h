#ifndef TRAVELPLANNER_INCLUDED
#define TRAVELPLANNER_INCLUDED

#include <unordered_set>
#include "fm.h"

class TravelPlanner : public TravelPlannerBase
{
    public:
        TravelPlanner(const FlightManagerBase& flight_manager, const AirportDB& airport_db)
        : TravelPlannerBase(flight_manager, airport_db)
        {}

        virtual ~TravelPlanner() {}
        
        void add_preferred_airline(std::string airline);

        virtual bool plan_travel(std::string source_airport, std::string destination_airport,
                                 int start_time, Itinerary& itinerary) const;
    private:
        std::unordered_set<std::string> m_preferred_airlines;
};

#endif // TRAVELPLANNER_INCLUDED
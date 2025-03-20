#ifndef fm_Included
#define fm_Included

#include <string>
#include <vector>
#include <unordered_map>
#include "provided.h"
#include "bstset.h"

bool operator<(const FlightSegment& lhs, const FlightSegment& rhs);
bool operator>(const FlightSegment& lhs, const FlightSegment& rhs);
bool operator==(const FlightSegment& lhs, const FlightSegment& rhs);

class FlightManager : public FlightManagerBase
{
  public:
    FlightManager() {}
    virtual ~FlightManager() {};

    virtual bool load_flight_data(std::string filename);
    virtual std::vector<FlightSegment> find_flights(std::string source_airport, int start_time, int end_time) const;

  private:
    std::unordered_map<std::string, BSTSet<FlightSegment>> m_flights;
};

#endif // fm_Included
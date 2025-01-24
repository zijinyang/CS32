#ifndef TurnoutListIncluded
#define TurnoutListIncluded

#include "Sequence.h"
#include <limits>

const unsigned long NO_TURNOUTS = std::numeric_limits<unsigned long>::max();

class TurnoutList
{
  public:
    TurnoutList();       // Create an empty turnout list.

    bool add(unsigned long turnout);
      // If the turnout is valid (a value from 0 to 1800) and the turnout list
      // has room for` it, add it to the turnout list and return true.
      // Otherwise, leave the turnout list unchanged and return false.

    bool remove(unsigned long turnout);
      // Remove one instance of the specified turnout from the turnout list.
      // Return true if a turnout was removed; otherwise false.

    int size() const;  // Return the number of turnouts in the list.

    unsigned long minimum() const;
      // Return the smallest turnout in the turnout list.  If the list is
      // empty, return NO_TURNOUTS.

    unsigned long maximum() const;
      // Return the largest turnout in the turnout list.  If the list is
      // empty, return NO_TURNOUTS.

  private:
    // Some of your code goes here.
    Sequence m_turnouts;
};
#endif //TurnoutListIncluded
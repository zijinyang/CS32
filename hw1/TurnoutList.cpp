#include "TurnoutList.h"
using namespace std;

TurnoutList::TurnoutList(){
}

bool TurnoutList::add(unsigned long turnout){
    if(turnout < 0 || turnout > 1800)
        return false;
    if(!m_turnouts.insert(m_turnouts.size(), turnout))
        return false;

    return true;
}

bool TurnoutList::remove(unsigned long turnout){
    if(turnout < 0 || turnout > 1800)
        return false;

    if(!m_turnouts.erase(m_turnouts.find(turnout))){
        return false;
    }

    return true;
}

int TurnoutList::size() const{
    return m_turnouts.size();
}

unsigned long TurnoutList::maximum() const{
    if(m_turnouts.empty())
        return NO_TURNOUTS;
    int maximum = 0;
    for(int i = 0; i < m_turnouts.size(); i++){
        unsigned long turnout;
        m_turnouts.get(i, turnout);
        if(turnout > maximum)
            maximum = turnout;
    }
    return maximum;
}

unsigned long TurnoutList::minimum() const{
    if(m_turnouts.empty())
        return NO_TURNOUTS;
    int minimum  = 1800;
    for(int i = 0; i < m_turnouts.size(); i++){
        unsigned long turnout;
        m_turnouts.get(i, turnout);
        if(turnout < minimum)
            minimum = turnout;
    }
    return minimum;
}
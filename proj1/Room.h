#ifndef Room_Included
#define Room_Included 

#include "History.h"
#include "globals.h"

class Player;

class Bee;

class Room
{
  public:
        // Constructor/destructor
    Room(int nRows, int nCols);
    ~Room();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    History& history();
    int     beeCount() const;
    int     numBeesAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

        // Mutators
    bool addBee(int r, int c);
    bool addPlayer(int r, int c);
    bool swatBeeAt(int r, int c, int dir);
    bool moveBees();

  private:
    int     m_rows;
    int     m_cols;
    History m_history;
    Player* m_player;
    Bee*    m_bees[MAXBEES];
    int     m_nBees;
};

#endif //Room_Included 
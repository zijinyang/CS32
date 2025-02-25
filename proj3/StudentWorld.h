#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld(){cleanUp();};
  virtual int init();
  virtual int move();
  virtual void cleanUp();

  void addActor(Actor* a){m_actorList.push_back(a);};

  Level* getLev(){return &lev;};
  
  void attackAllAt(int x, int y);

  void attackAllEnemiesAt(int x, int y);

  void burnAllAt(int x, int y);

  void attackPlayer(int x, int y);
  void freezePlayer(){m_player->freeze();};

  bool playerIsAt(int x, int y);
  
  void incrBurps(int amt){m_player->incrBurps(amt);};

  int numBurps(){return m_player->numBurps();};

  Player* getPlayer();

private:
  std::vector<Actor*> m_actorList;
  Level lev;
  Player* m_player;
};

#endif // STUDENTWORLD_H_

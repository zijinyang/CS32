#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

GameWorld *createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp
StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), lev(assetPath)
{
}

//attacks all actors at a given location
void StudentWorld::attackAllAt(int x, int y)
{
    vector<Actor*>::iterator i;
    for(i = m_actorList.begin(); i != m_actorList.end(); i++)
    {
        Actor* a = *i;
        if(a->isAt(x,y))
            a->isAttacked();
    }
}

//attacks actors that can be burnt at a given location
//No longer used
void StudentWorld::burnAllAt(int x, int y)
{
    vector<Actor*>::iterator i;
    for(i = m_actorList.begin(); i != m_actorList.end(); i++)
    {
        Actor* a = *i;
        if(a->isAt(x,y) && a->canBurn())
            a->isAttacked();
    }
}

//attacks all enemies at a given location
void StudentWorld::attackAllEnemiesAt(int x, int y)
{
    vector<Actor*>::iterator i;
    for(i = m_actorList.begin(); i != m_actorList.end(); i++)
    {
        Actor* a = *i;
        if(a->isAt(x,y) && a->isEnemy())
            a->isAttacked();
    }
}

//attacks the player
void StudentWorld::attackPlayer(int x, int y)
{
    if(m_player->isAt(x,y))
        m_player->isAttacked();
} 

//checks if the player is at a given location
bool StudentWorld::playerIsAt(int x, int y)
{
    return (m_player->isAt(x,y));
}

Player* StudentWorld::getPlayer()
{
    return m_player;
}

int StudentWorld::init()
{
    // getLevel() converstion to filepath
    ostringstream oss;
    oss << "level" << setw(2) << setfill('0') << getLevel() << ".txt";
    Level::LoadResult result = lev.loadLevel(oss.str());

    // check validity of loaded level/file
    if (getLevel() < 0 || result == Level::load_fail_bad_format){
        return GWSTATUS_LEVEL_ERROR;
    }
    if (getLevel() > MAX_LEVELS || result == Level::load_fail_file_not_found){
        return GWSTATUS_PLAYER_WON;
    }

    // construct actors based on level layout
    for (int c = 0; c < VIEW_WIDTH; c++)
    {
        for (int r = 0; r < VIEW_HEIGHT; r++)
        {
            Level::MazeEntry me = lev.getContentsOf(c, r);
            switch (me)
            {
            case Level::floor:
                m_actorList.push_back(new Floor(c, r, this));
                break;
            case Level::ladder:
                m_actorList.push_back(new Ladder(c, r, this));
                break;
            case Level::left_kong:
                m_actorList.push_back(new Kong(c, r, GraphObject::left, this));
                break;
            case Level::right_kong:
                m_actorList.push_back(new Kong(c, r, GraphObject::right, this));
                break;
            case Level::fireball:
                m_actorList.push_back(new Fireball(c, r, this));
                break;
            case Level::koopa:
                m_actorList.push_back(new Koopa(c, r, this));
                break;
            case Level::bonfire:
                m_actorList.push_back(new Bonfire(c, r, this));
                break;
            case Level::extra_life:
                m_actorList.push_back(new ExtraLife(c, r, this));
                break;
            case Level::garlic:
                m_actorList.push_back(new Garlic(c, r, this));
                break;
            case Level::player:
                m_player = new Player(c,r, this); 
                break;
            case Level::empty:
                break;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //calling doSomething for all actors
    m_player->doSomething();
    vector<Actor*>::iterator i;
    for(i = m_actorList.begin(); i != m_actorList.end(); i++)
    {
        Actor* a = *i;
        a->doSomething();
        if(!m_player->isAlive())
        {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        if(m_player->hasWon())
            return GWSTATUS_FINISHED_LEVEL;
    }
    
    //removing dead actors
    for(i = m_actorList.begin(); i != m_actorList.end();)
    {
        if(!(*i)->isAlive()){
            delete (*i);
            i = m_actorList.erase(i);
        }else{
            i++;
        }
    }

    //updating game status text
    ostringstream oss;
    oss << "Score: " << setw(7) << setfill('0') << getScore() << "  Level: " << setw(2) << getLevel() << "  Lives: " << setw(2) << getLives() << "  Burps: " << setw(2) << numBurps();
    setGameStatText(oss.str());

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    //deleting all actors
    vector<Actor*>::iterator i;
    for(i = m_actorList.begin(); i != m_actorList.end();)
    {
        delete (*i);
        i = m_actorList.erase(i);
    }

    //deleting player, ensuring that is cleanup is called twice the player is not deleted twice
    if(m_player != nullptr){
        delete m_player;
        m_player = nullptr;
    }
}

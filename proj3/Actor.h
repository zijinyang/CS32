#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Level.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
    public:
        Actor(int imageID, int x, int y, StudentWorld* gw): GraphObject(imageID, x, y ,0, 1.0), m_gw(gw), m_isAlive(true){};
        Actor(int imageID, int x, int y, int direction, StudentWorld* gw): GraphObject(imageID, x, y, direction, 1.0), m_gw(gw), m_isAlive(true){};
        virtual void doSomething(){};
        virtual void isAttacked(){};

        StudentWorld* getGameWorld(){return m_gw;};

        bool canMoveTo(int newX, int newY);
        bool canMoveTo(int dir); //overlaod allow for checking based on direction
                                 //
        void moveTo(int x, int y){GraphObject::moveTo(x,y);}; //prevent moveTo in base from being hidden
        void moveTo(int dir); //overload allow for directional move
                              //
        Level::MazeEntry getTileAt(int x, int y);
        Level::MazeEntry getTileAt(int dir);

        bool isAt(int x, int y);
        
        bool isAlive(){return m_isAlive;};
        void setDead(){m_isAlive = false;};

        virtual bool isEnemy(){return false;};
        virtual bool canBurn(){return false;};
    private:
        StudentWorld* m_gw;
        bool m_isAlive;
};

class Player : public Actor
{
    public:
        Player(int x, int y, StudentWorld* gw): Actor(IID_PLAYER, x ,y, GraphObject::right, gw){};
        virtual void doSomething();
        void isAttacked();
        void freeze();
        
        void incrBurps(int amt){m_numBurps += amt;};
        int numBurps(){return m_numBurps;};

        void setWon(){m_hasWon = true;};
        bool hasWon(){return m_hasWon;};
    private:
        bool m_isJumping = false;
        int m_jumpTick = 0; // 0 => not in jump animation

        bool m_isFrozen = false;
        int m_freezeCounter = 0;
        int m_numBurps = 0;

        bool m_hasWon = false;
};

class Floor: public Actor
{
    public:
        Floor(int x, int y, StudentWorld* gw): Actor(IID_FLOOR, x ,y, gw){};
};

class Ladder: public Actor
{
    public:
        Ladder(int x, int y, StudentWorld* gw): Actor(IID_LADDER, x ,y, gw){};
};

class Burp: public Actor
{
    public:
        Burp(int x, int y, int direction, StudentWorld* gw): Actor(IID_BURP, x ,y, direction, gw), m_duration(5){};
        virtual void doSomething();
    private:
        int m_duration;
};

class Bonfire: public Actor
{
    public:
        Bonfire(int x, int y, StudentWorld* gw): Actor(IID_BONFIRE, x, y, gw){};
        virtual void doSomething();
};

// declaration of goodie and classes derived from goodie (ExtraLife, Garlic)
class Goodie: public Actor
{
    public:
        Goodie(int imageID, int x, int y, StudentWorld* gw): Actor(imageID, x ,y, gw){};
        virtual void doSomething();
        virtual void causeEffect(){};
        virtual int getPoints(){return 1000;};
    private:
};

class ExtraLife: public Goodie
{
    public:
        ExtraLife(int x, int y, StudentWorld* gw): Goodie(IID_EXTRA_LIFE_GOODIE, x, y, gw){};
        virtual void causeEffect();
        virtual int getPoints(){return 50;};
};

class Garlic: public Goodie
{
    public:
        Garlic(int x, int y, StudentWorld* gw): Goodie(IID_GARLIC_GOODIE, x ,y, gw){};
        virtual void causeEffect();
        virtual int getPoints(){return 25;};
};

// declaration of Enemy and classes derived from Enemy (Fireball, Koopa, Barrel, Kong) 
class Enemy: public Actor
{
    public:
        Enemy(int imageID, int x, int y, StudentWorld* gw) : Actor(imageID, x, y, 0, gw)
        {
            int direction = (randInt(0,1) == 0) ? GraphObject::right : GraphObject::left;
            setDirection(direction);
        };
        Enemy(int imageID, int x, int y, int direction,StudentWorld* gw): Actor(imageID, x ,y, direction, gw){};
          
        virtual bool isEnemy(){return true;};
        virtual void isAttacked();
        virtual void dropGoodie(){};

        bool canDoSomething(); 
        void walk();
        void switchDirection();
        
        void set_doSomethingThreshold(int threshold){doSomethingThreshold = threshold;};
    private:
        int doSomethingThreshold = 10;
        int m_doSomethingCounter = 0; // Counter for doSomething calls
};

class Fireball: public Enemy
{
    public:
        Fireball(int x, int y, StudentWorld* gw) : Enemy(IID_FIREBALL, x, y, gw){};
        virtual void doSomething();
        virtual void dropGoodie();
    private:
        int m_isClimbing = none;
};

class Koopa: public Enemy
{
    public:
        Koopa(int x, int y, StudentWorld* gw) : Enemy(IID_KOOPA, x ,y, gw), m_freezeCooldown(0){};
        virtual void dropGoodie();
        virtual void doSomething();
    private:
        int m_freezeCooldown;
};

class Barrel: public Enemy
{
    public:
        Barrel(int x, int y, int direction, StudentWorld* gw) : Enemy(IID_BARREL, x, y, direction, gw){};
        virtual bool canBurn(){return true;};
        virtual void doSomething();
    private:
        bool m_isFalling = false;
};

class Kong: public Enemy
{
    public:
        Kong(int x, int y, int direction, StudentWorld* gw) : Enemy(IID_KONG, x, y, direction, gw){set_doSomethingThreshold(5);};
        virtual void doSomething();
        bool canThrowBarrel();
    private:
        bool m_flee = false;
        int m_barrel_counter = 0;
};

#endif // ACTOR_H_
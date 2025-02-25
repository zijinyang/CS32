#include "Actor.h"
#include "StudentWorld.h"
#include "Level.h"

using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
bool Actor::canMoveTo(int x, int y)
{
   return m_gw->getLev()->getContentsOf(x, y) != Level::floor;
}

bool Actor::canMoveTo(int dir)
{
   int newX, newY;
   getPositionInThisDirection(dir, 1, newX, newY);
   return canMoveTo(newX, newY);
}

void Actor::moveTo(int dir)
{
   int newX, newY;
   getPositionInThisDirection(dir, 1, newX, newY);
   moveTo(newX, newY);
}

Level::MazeEntry Actor::getTileAt(int x, int y)
{
   return getGameWorld()->getLev()->getContentsOf(x, y);
}

Level::MazeEntry Actor::getTileAt(int dir)
{
   int newX, newY;
   getPositionInThisDirection(dir, 1, newX, newY);
   return getTileAt(newX, newY);
}

bool Actor::isAt(int x, int y)
{
   return getX() == x && getY() == y;
}

void Player::doSomething()
{
   if (!isAlive())
      return;

   // in jumping animation movement logic
   if (m_isJumping) // isjumping
   {
      if (m_jumpTick < 0 || m_jumpTick > 4) // no longer jumping
      {
         m_isJumping = false;
      }
      else if (m_jumpTick < 3 && canMoveTo(getDirection())) // in the air moving horizontally
      {
         if (canMoveTo(getDirection()))
            moveTo(getDirection());
         else
            m_isJumping = false;

         if (getTileAt(GraphObject::none) == Level::ladder)
            m_isJumping = false;
      }
      else
      {
         if (canMoveTo(down))
            moveTo(GraphObject::down);
         m_isJumping = false;
      }
      m_jumpTick++;
      return;
   }

   // freezing logic
   if (m_isFrozen)
   {
      if (m_freezeCounter <= 0)
         m_isFrozen = false;
      else
         m_freezeCounter--;
      return;
   }

   // Falling Logic
   Level::MazeEntry me = getTileAt(GraphObject::down); // gets the type of object below
   if (me != Level::floor && me != Level::ladder)      // TODO: may bug when enemy right below
   {
      moveTo(GraphObject::down);
      return;
   }

   // keypress logic
   int ch;
   if (getGameWorld()->getKey(ch))
   {
      // user hit a key this tick!
      switch (ch)
      {
      case KEY_PRESS_LEFT:
         setDirection(GraphObject::left);
         if (canMoveTo(getDirection()))
            moveTo(getDirection());
         break;
      case KEY_PRESS_RIGHT:
         setDirection(GraphObject::right);
         if (canMoveTo(getDirection()))
            moveTo(getDirection());
         break;
      case KEY_PRESS_UP:
         if (getTileAt(GraphObject::none) == Level::ladder)
         {
            if (canMoveTo(GraphObject::up))
               moveTo(GraphObject::up);
         }
         break;
      case KEY_PRESS_DOWN:
         if (getTileAt(GraphObject::none) == Level::ladder || getTileAt(GraphObject::down) == Level::ladder)
         {
            if (canMoveTo(GraphObject::down))
               moveTo(GraphObject::down);
         }
         break;
      case KEY_PRESS_SPACE:
         if (!m_isJumping && (getTileAt(GraphObject::down) == Level::floor || getTileAt(GraphObject::down) == Level::ladder || getTileAt(GraphObject::none) == Level::ladder))
         {
            getGameWorld()->playSound(SOUND_JUMP);
            if (canMoveTo(GraphObject::up))
            {
               m_isJumping = true;
               m_jumpTick = 0;
               moveTo(up);
            }
         }
         break;
      case KEY_PRESS_TAB:
         if (m_numBurps > 0)
         {
            getGameWorld()->playSound(SOUND_BURP);
            int newX, newY;
            getPositionInThisDirection(getDirection(), 1, newX, newY);
            getGameWorld()->addActor(new Burp(newX, newY, getDirection(), getGameWorld()));
            m_numBurps--;
         }
         break;
      }
   }
}

void Player::isAttacked()
{
   getGameWorld()->playSound(SOUND_PLAYER_DIE);
   setDead();
}

void Player::freeze()
{
   m_isFrozen = true;
   m_freezeCounter = 50;
}

void Burp::doSomething()
{
   if (!isAlive())
      return;

   m_duration--;

   if (m_duration <= 0)
   {
      setDead();
      return;
   }

   getGameWorld()->attackAllEnemiesAt(getX(), getY());
}

void Bonfire::doSomething()
{
   getGameWorld()->burnAllAt(getX(), getY());
   getGameWorld()->attackPlayer(getX(), getY());
}

void Goodie::doSomething()
{
   if (!isAlive())
   {
      return;
   }
   if (getGameWorld()->playerIsAt(getX(), getY()))
   {
      getGameWorld()->increaseScore(getPoints());
      setDead();
      getGameWorld()->playSound(SOUND_GOT_GOODIE);
      causeEffect();
   }
}

void ExtraLife::causeEffect()
{
   getGameWorld()->incLives();
}

void Garlic::causeEffect()
{
   getGameWorld()->incrBurps(5);
}

bool Enemy::canDoSomething()
{
   m_doSomethingCounter++;
   if (m_doSomethingCounter == doSomethingThreshold)
   {
      m_doSomethingCounter = 0;
      return true;
   }
   return false;
}

void Enemy::walk()
{
   int belowX, belowY;
   getPositionInThisDirection(getDirection(), 1, belowX, belowY);
   belowY--;
   if (!canMoveTo(getDirection()) || (getTileAt(belowX, belowY) != Level::floor && getTileAt(belowX, belowY) != Level::ladder))
   {
      switchDirection();
   }else{
      moveTo(getDirection());
   }
}

void Enemy::isAttacked()
{
   setDead();
   getGameWorld()->playSound(SOUND_ENEMY_DIE);
   getGameWorld()->increaseScore(100);
   if(randInt(0,2) == 0){
      dropGoodie();
   }
}

void Enemy::switchDirection()
{
    setDirection(getDirection() == GraphObject::left ? GraphObject::right : GraphObject::left);
}

void Fireball::doSomething()
{
   if (!isAlive())
      return;

   if (getGameWorld()->playerIsAt(getX(), getY()))
   {
      getGameWorld()->attackPlayer(getX(), getY());
      return;
   }

   if (canDoSomething())
   {
      if (getTileAt(none) == Level::ladder && canMoveTo(up) && m_isClimbing != down)
      {
         if (randInt(0, 2) == 0 || m_isClimbing == up)
         {
            m_isClimbing = up;
            if (canMoveTo(up))
               moveTo(up);
         }
      }
      else if (getTileAt(down) == Level::ladder && canMoveTo(down) && m_isClimbing != up)
      {
         if (randInt(0, 2) == 0 || m_isClimbing == down)
         {
            m_isClimbing = down;
            if (canMoveTo(down))
               moveTo(down);
         }
      }else if(m_isClimbing != none){
         m_isClimbing = none;
      }

      if(m_isClimbing == none){
         walk();
      }
      
      if (getGameWorld()->playerIsAt(getX(), getY()))
      {
         getGameWorld()->attackPlayer(getX(), getY());
         return;
      }
   }
}

void Fireball::dropGoodie()
{
   getGameWorld()->addActor(new Garlic(getX(), getY(), getGameWorld()));
}

void Koopa::dropGoodie()
{
   getGameWorld()->addActor(new ExtraLife(getX(), getY(), getGameWorld()));
}

void Koopa::doSomething()
{
   if (!isAlive())
      return;
   
   if (getGameWorld()->playerIsAt(getX(), getY()) && m_freezeCooldown == 0)
   {
      getGameWorld()->freezePlayer();
      m_freezeCooldown = 50;
      return;
   }

   if(m_freezeCooldown > 0){
      m_freezeCooldown--;
   }
   
   if (canDoSomething())
   {
      walk();
      if (getGameWorld()->playerIsAt(getX(), getY()) && m_freezeCooldown == 0)
      {
         getGameWorld()->freezePlayer();
         m_freezeCooldown = 50;
         return;
      }
   }
}

void Barrel::doSomething()
{
   if (!isAlive())
      return;

   if (getGameWorld()->playerIsAt(getX(), getY()))
   {
      getGameWorld()->attackPlayer(getX(), getY());
      return;
   }
   
   if(getTileAt(down) != Level::floor){
      m_isFalling = true;
      moveTo(down);
      return;
   }

   if(m_isFalling){
      m_isFalling = false;
      switchDirection();
   }

   if (canDoSomething())
   {
      int belowX, belowY;
      getPositionInThisDirection(getDirection(), 1, belowX, belowY);
      belowY--;
      if (!canMoveTo(getDirection()))
      {
         switchDirection();
      }else{
         moveTo(getDirection());
      }
      if(getGameWorld()->playerIsAt(getX(), getY()))
      {
         getGameWorld()->attackPlayer(getX(), getY());
         return;
      }
   }
   
}

bool Kong::canThrowBarrel()
{
   int N = (200 - 50 * getGameWorld()->getLevel() > 50) ? 200 - 50 * getGameWorld()->getLevel() : 50;
   m_barrel_counter++;
   if (m_barrel_counter >= N)
   {
      m_barrel_counter = 0;
      return true;
   }
   return false;
}

void Kong::doSomething()
{
   if (!isAlive())
      return;

   increaseAnimationNumber();

   int distance_squared = (getX() - getGameWorld()->getPlayer()->getX()) * (getX() - getGameWorld()->getPlayer()->getX()) + (getY() - getGameWorld()->getPlayer()->getY()) * (getY() - getGameWorld()->getPlayer()->getY());
   if(distance_squared <= 4){
      m_flee = true;
   }

   if(!m_flee && canThrowBarrel())
   {
      int newX, newY;
      getPositionInThisDirection(getDirection(), 1, newX, newY);
      getGameWorld()->addActor(new Barrel(newX, newY, getDirection(), getGameWorld()));
   }

   if (m_flee)
   {
      if(canDoSomething()){
         if(getY() == VIEW_HEIGHT)
         {
            getGameWorld()->increaseScore(1000);
            getGameWorld()->playSound(SOUND_FINISHED_LEVEL);
            getGameWorld()->getPlayer()->setWon();
         }else
         {
            moveTo(up);
         }
      }
   }
} 
#ifndef ACTIONS_H
#define ACTIONS_H

# include "mob.h"

class Action {
public:
  virtual ~Action() {}
  virtual void execute(Mob &m) = 0;
};

class MoveAction : public Action {
private:
  int deltaX;
  int deltaY;

public:
  MoveAction(int dx, int dy) {
    deltaX = dx;
    deltaY = dy;
  }

  virtual void execute(Mob &mob) {
    mob.move(deltaX, deltaY);
  }
};

class MoveLeft : public MoveAction {
public:
  MoveLeft() : MoveAction(-1, 0) {
  }
};


class MoveRight : public MoveAction {
public:
  MoveRight() : MoveAction(1, 0) {}

};


class MoveUp : public MoveAction {
public:
  MoveUp() : MoveAction(0, -1) {}
};


class MoveDown : public MoveAction {
public:
  MoveDown() : MoveAction(0, 1) {}

};


#endif

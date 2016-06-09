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
  MoveAction(int dy, int dx) {
    deltaX = dx;
    deltaY = dy;
  }

  virtual void execute(Mob &mob) {
    mob.move(deltaY, deltaX);
  }
};

class MoveLeft : public MoveAction {
public:
  MoveLeft() : MoveAction(0, -1) {
  }
};


class MoveRight : public MoveAction {
public:
  MoveRight() : MoveAction(0, 1) {}

};


class MoveUp : public MoveAction {
public:
  MoveUp() : MoveAction(-1, 0) {}
};


class MoveDown : public MoveAction {
public:
  MoveDown() : MoveAction(1, 0) {}

};


#endif

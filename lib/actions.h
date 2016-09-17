#ifndef ACTIONS_H
#define ACTIONS_H

# include "mob.h"
# include "view.h"

class Action {
public:
  virtual ~Action() {}
  virtual void execute(Mob &m) = 0;

  // is this something that happens on the map,
  // as opposed to displaying a menu or a control thing
  bool isMapAction;

  std::string outputMessage;
};

class MoveAction : public Action {
private:
  int deltaX;
  int deltaY;

public:


  MoveAction(int dy, int dx) {
    deltaX = dx;
    deltaY = dy;
    isMapAction = true;
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


class MenuAction : public Action {
public:
  MenuAction() {
    isMapAction = false;
  }

  virtual std::string formatMenu() = 0;

};

class InventoryAction : public MenuAction {
private:
  std::vector<Item> inventory;

public:
  virtual void execute(Mob &mob) {
    inventory = mob.getInventory();
    std::cerr << "inventory " << inventory.size() << std::endl;
  }

  virtual std::string formatMenu() {
    std::string str = "";
    for(Item i : inventory) {
          str += i.name;
    }
    std::cerr << str << std::endl;

    return str;
  }
};

class ItemAction : public Action {

public:
  int itemNumber;
  ItemAction(int i) : itemNumber(i) {
    isMapAction = true;
  }

  virtual void execute(Mob &mob) {
    std::vector<Item> inventory = mob.getInventory();
    if(inventory.size() > itemNumber) {
      outputMessage = "Using " + inventory[itemNumber].name + '\n';
    }
    else {
      std::cerr << "no inventory entry for index " << itemNumber << std::endl;
    }
  }

};



#endif

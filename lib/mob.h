#ifndef MOB_H
#define MOB_H

#include <algorithm>
#include <vector>
#include "items.h"
#include "territory.h"

#include <curses.h>
/*
  A mobile object (mob) in the game

*/
class Mob {
private:
  int x;
  int y;
  char symbol;
  std::vector<Item> inventory;
  std::mt19937 randomGenerator;

public:
  Mob(int y_, int x_, char symbol_) : y(y_), x(x_), symbol(symbol_) {
  }


  // move BY dy, dx
  void move(int dy, int dx) {
    x += dx;
    y += dy;
  }



  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  int getSymbol() {
    return symbol;
  }

  void pos(int y_new, int x_new) {
    x = x_new;
    y = y_new;
  }

  void addItem(Item i)
  {
    inventory.push_back(Item(i));
  }

  void interact(TerritoryType territory)
  {

    std::cerr << "territory " << territory << '\n';
    if (territory == TerritoryType::Food) {
      std::cerr << "I FOUND FOOD YAY \n";

      int diceRoll = randomGenerator() % foodTypes.size();

      FoodItem foundFood = foodTypes[diceRoll];

      addItem(foundFood);

      std::string message = "Found a delicious " + foundFood.name;
      mvprintw(0, 0, message.c_str());
    }
  }

};


#endif

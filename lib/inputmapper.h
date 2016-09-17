#ifndef INPUTMAPPER_H
#define INPUTMAPPER_H

#include "actions.h"
#include <map>
#include <ncurses.h>


class InputMapper {
private:

  std::map<char, Action*> KeyBindings;


public:

  InputMapper() {
    KeyBindings = {
     {KEY_UP, new MoveUp()},
     {KEY_DOWN, new MoveDown()},
     {KEY_LEFT, new MoveLeft()},
     {KEY_RIGHT, new MoveRight()},
     {105, new InventoryAction()}
   };

   for (char i = 97; i < 105; i++) {
     KeyBindings[i] = new ItemAction(i - 97);
   }
  }

  Action* mapInput(char key) {
    Action *action;
    std::cerr << "KEY PRESSED \n";
    if(KeyBindings.count(key) == 0) {
      action = NULL;
    }
    else {
      action = KeyBindings[key];
    }
    return action;
  }
};

#endif

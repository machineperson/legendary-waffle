#ifndef INPUTMAPPER_H
#define INPUTMAPPER_H

#include "actions.h"
#include <map>
#include <ncurses.h>


class InputMapper {
private:

  std::map<char, Action*> KeyBindings = {
    {KEY_UP, new MoveUp()},
    {KEY_DOWN, new MoveDown()},
    {KEY_LEFT, new MoveLeft()},
    {KEY_RIGHT, new MoveRight()}
  };

public:
  Action* mapInput(char key) {
    Action *action;
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

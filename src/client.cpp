#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "client.h"
#include "inputmapper.h"
#include <ncurses.h>
#include "mob.h"
#include "actions.h"
#include "view.h"


void erase (int y, int x) {
  mvaddch(y, x, ' ');
}


void game_loop(Mob player) {
  InputMapper mapper;

  mvaddch(player.getY(), player.getX(), player.getSymbol());

  while(true) {
    int input = getch();
    if (input == KEY_EXIT) {
      return;
    }

    Action* action = mapper.mapInput(input);
    if (action) {
      erase(player.getY(), player.getX());
      action->execute(player);
      mvaddch(player.getY(), player.getX(), player.getSymbol());
      refresh();
    }

  }
}

bool printWelcomeMessage(Screen &scr) {

    scr.printMessage("Greetings, comrade! You are a raccoon. Your ultimate goals are to bring about the destruction of capitalism and find the ultimate waffle of legends.\n Your immediate goal is to scavenge for food because you are hungry. Good luck! \n Press any key to start the game.");

    int input = getch();
    return input != KEY_EXIT;
    

}

int main (int argc, char *argv[]) {

  int x = 1;
  int y = 15;

  Screen scr;
  printWelcomeMessage(scr);

  clear();
  Mob player = Mob(x, y, '@');
  clear();
  game_loop(player);


}

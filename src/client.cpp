#include <stdio.h>
#include <string>
#include <iostream>

#include "client.h"
#include "inputmapper.h"
#include <ncurses.h>
#include "mob.h"
#include "actions.h"


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
      action->execute(player);
      mvaddch(player.getY(), player.getX(), player.getSymbol());
      refresh();
    }
    
  }
}



int main (int argc, char *argv[]) {

  // initialise ncurses
  initscr();
  clear();
  noecho();
 	cbreak();
 	keypad(stdscr, TRUE);
 	curs_set(0);
  bool quit = false;
  int x = 1;
  int y = 15;


  Mob player = Mob(x, y, '@');
  clear();

  while (!quit) {
    game_loop(player);

  }


}

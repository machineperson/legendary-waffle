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


void game_loop(Frame &game_map, Frame &viewport, Mob player) {
  InputMapper mapper;

  game_map.add(player);
  viewport.center(player);
  viewport.refresh();
  while(true) {
    int input = getch();
    if (input == KEY_EXIT) {
      return;
    }

    Action* action = mapper.mapInput(input);
    if (action) {
      erase(player.getY(), player.getX());
      action->execute(player);
      game_map.add(player);
      viewport.center(player);
      viewport.refresh();

    }

  }
}

bool printWelcomeMessage(Screen &scr) {

    scr.printMessage("Greetings, comrade! You are a raccoon. Your ultimate goals are to bring about the destruction of capitalism and find the ultimate waffle of legends.\n Your immediate goal is to scavenge for food because you are hungry. Good luck! \n Press any key to start the game.");

    int input = getch();
    return input != KEY_EXIT;


}

int main (int argc, char *argv[]) {

  Screen scr;
  printWelcomeMessage(scr);

  Frame game_map(2*scr.getHeight(), 2*scr.getWidth(), 0, 0);
  Frame viewport(game_map, scr.getHeight(), scr.getWidth(), 0, 0);

  clear();
  Mob player = Mob(game_map.getHeight()/2, game_map.getWidth()/2, '@');
//  game_map.fillWindow();
  game_loop(game_map, viewport, player);


}

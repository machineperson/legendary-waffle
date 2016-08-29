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

void printWelcomeMessage(Screen &scr) {

    scr.printMessage("Greetings, comrade! You are a raccoon. Your ultimate goals are to bring about the destruction of capitalism and find the ultimate waffle of legends.\n Your immediate goal is to scavenge for food because you are hungry. Good luck! \n Press any key to start the game.");

}


void game_loop(Screen &scr, Frame &game_map, Frame &viewport, Mob player) {
  InputMapper mapper;
  printWelcomeMessage(scr);

  int i = 0;


  char currentTerritory = '0';


  while(true) {
    std::cerr << "wait \n";

    int input = getch();
    if (input == KEY_EXIT) {
      return;
    }

    std::cerr << "input " << input <<"  \n";

    int xPreMove = player.getX();
    int yPreMove = player.getY();

    Action* action = mapper.mapInput(input);
    if (action) {
      game_map.erase(player);
      action->execute(player);
      std::cerr << "refreshing " << i++ <<"\n";
    }

    currentTerritory = game_map.add(player);
    int xPostMove = player.getX();
    int yPostMove = player.getY();
    // 1. can the player move there?
    if (!canMoveInto[static_cast<TerritoryType>(currentTerritory)]) {
      std::cerr << "cannot move into this territory"<< '\n';
      std::cerr << "player was at  " << yPreMove << ", " << xPreMove << '\n';
      std::cerr << "player was moving to  " << yPostMove << ", " << xPostMove << '\n';

      // move the player back to their original position
      player.pos(yPreMove, xPreMove);
      // put the original territory back
      game_map.add(currentTerritory, yPostMove, xPostMove);

      game_map.add(player);
    }

    else if (!isRemovable[static_cast<TerritoryType>(currentTerritory)]) {
      std::cerr << "putting back territory " << currentTerritory << '\n';
      game_map.add(currentTerritory, yPreMove, xPreMove);
    }
    else {
      player.interact(static_cast<TerritoryType>(currentTerritory));
    }
    std::cerr << "current territory: " << currentTerritory << '\n';
    viewport.center(player);
    viewport.refresh();



  }
}

int main (int argc, char *argv[]) {

  Screen scr;
  Frame game_map(2*scr.getHeight(), 2*scr.getWidth(), 0, 0);
  Frame viewport(game_map, scr.getHeight(), scr.getWidth(), 0, 0);

  Mob player = Mob(game_map.getHeight()/2, game_map.getWidth()/2, '@');
  game_map.populateRandom();
  game_loop(scr, game_map, viewport, player);


}

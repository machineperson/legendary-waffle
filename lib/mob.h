#ifndef MOB_H
#define MOB_H

/*
  A mobile object (mob) in the game

*/
class Mob {
private:
  int x;
  int y;
  char symbol;



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
};


#endif
